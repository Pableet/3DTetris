#include "DX11Device.h"
#include "ReadData.h"
#include "DirectXColors.h"


DX11Device::DX11Device()
	: m_creationFlags(0), m_d3dDriverType(D3D_DRIVER_TYPE_HARDWARE)
	, m_featureLevel(D3D_FEATURE_LEVEL_11_0), m_vb(nullptr), m_ib(nullptr)
	, m_indexCount(0), m_primitive(D3D_PRIMITIVE_TOPOLOGY_UNDEFINED)
	, m_screenWidth(0), m_screenHeight(0), m_screenViewport(), m_nowRS(0)
{

}

DX11Device::~DX11Device()
{
	m_vsByteCode.clear();
	delete m_ib;
	delete m_vb;
	delete& m_screenViewport;
}

HRESULT DX11Device::Create(HWND hWnd, int screenWidth, int screenHeight)
{
	m_creationFlags = 0;
#ifdef _DEBUG
	m_creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	m_featureLevel = D3D_FEATURE_LEVEL_11_0;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;


	m_d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = screenWidth;
	sd.BufferDesc.Height = screenHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;



	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		0, m_d3dDriverType, 0, m_creationFlags, 0, 0, D3D11_SDK_VERSION, &sd,
		m_swapChain.GetAddressOf(), m_d3dDevice.GetAddressOf(), &m_featureLevel, m_deviceContext.GetAddressOf());




	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return hr;
	}

	if (m_featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return hr;
	}

	return hr;
}

void DX11Device::OnResize(int screenWidth, int screenHeight)
{
	// 이것들은 꼭 있어야 한다.
	assert(m_deviceContext);
	assert(m_d3dDevice);
	assert(m_swapChain);

	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	/// 없애야 할 버퍼에 대한 참조를 가지고 있으므로 예전 뷰를 릴리즈한다.
	/// 또한 예전 뎁스-스텐실 버퍼도 릴리즈한다.

	m_renderTargetView.Reset();
	m_depthStencilView.Reset();
	m_depthStencilBuffer.Reset();


	// Resize the swap chain and recreate the render target view.
	/// 스왑체인의 크기를 변경하고 렌더타겟 뷰를 다시 생성한다.

	HR(m_swapChain->ResizeBuffers(1, screenWidth, screenHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	HR(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	if (backBuffer)
	{
		HR(m_d3dDevice->CreateRenderTargetView(backBuffer, 0, m_renderTargetView.GetAddressOf()));
		ReleaseCOM(backBuffer);
	}


	// Create the depth/stencil buffer and view.
	/// 뎁스-스텐실 버퍼와 뷰를 생성한다.

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = screenWidth;
	depthStencilDesc.Height = screenHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;		// No MSAA
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc, 0, m_depthStencilBuffer.GetAddressOf()));
	if (m_depthStencilBuffer != nullptr)
		HR(m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer.Get(), 0, m_depthStencilView.GetAddressOf()));


	// Bind the render target view and depth/stencil view to the pipeline.
	/// 렌더타겟뷰, 뎁스/스탠실뷰를 파이프라인에 바인딩한다.
	m_deviceContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());


	// Set the viewport transform.
	/// 뷰포트 변환을 셋팅한다.
	m_screenViewport.TopLeftX = 0;
	m_screenViewport.TopLeftY = 0;
	m_screenViewport.Width = static_cast<float>(screenWidth);
	m_screenViewport.Height = static_cast<float>(screenHeight);
	m_screenViewport.MinDepth = 0.0f;
	m_screenViewport.MaxDepth = 1.0f;

	// Bind an array of viewports to the rasterizer stage of the pipeline.
	/// 뷰포트 배열을 파이프라인의 래스터라이즈 스테이지에 바인딩한다.
	m_deviceContext->RSSetViewports(1, &m_screenViewport);
}

HRESULT DX11Device::CreateVertexShader()
{
	auto _vertexShaderBytecode = DX::ReadData(L"VertexShader.cso");

	m_vsByteCode = _vertexShaderBytecode;

	return m_d3dDevice->CreateVertexShader(
		_vertexShaderBytecode.data(),
		_vertexShaderBytecode.size(),
		nullptr,
		&m_vertexShader);
}

HRESULT DX11Device::CreatePixelShader()
{
	auto _pixelShaderBytecode = DX::ReadData(L"PixelShader.cso");

	return m_d3dDevice->CreatePixelShader(
		_pixelShaderBytecode.data(),
		_pixelShaderBytecode.size(),
		nullptr,
		&m_pixelShader);
}

HRESULT DX11Device::CreateConstantBuffer()
{
	CD3D11_BUFFER_DESC _desc;
	ZeroMemory(&_desc, sizeof(_desc));

	_desc.ByteWidth = sizeof(SConstBuffer);
	_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;


	// This call allocates a device resource for the vertex buffer and copies
	// in the data.
	HRESULT hr = m_d3dDevice->CreateBuffer(&_desc, nullptr, m_constantBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(0, L"CreateConstantBuffer Failed.", 0, 0);
	}

	return hr;
}

void DX11Device::CreateRenderStates()
{
	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;

	HR(m_d3dDevice->CreateRasterizerState(&wireframeDesc, m_wireframeRS.GetAddressOf()));

	// Render State 중 Rasterizer State
	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
	solidDesc.FrontCounterClockwise = false;
	solidDesc.DepthClipEnable = true;

	HR(m_d3dDevice->CreateRasterizerState(&solidDesc, m_solidRS.GetAddressOf()));

	// 폰트용 DSS
	D3D11_DEPTH_STENCIL_DESC equalsDesc;
	ZeroMemory(&equalsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	equalsDesc.DepthEnable = true;
	equalsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	equalsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	HR(m_d3dDevice->CreateDepthStencilState(&equalsDesc, NormalDSS.GetAddressOf()));
}

void DX11Device::CreateInputLayout()
{
	// Create the vertex input layout.
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	HR(m_d3dDevice->CreateInputLayout(vertexDesc, 2,
		m_vsByteCode.data(),
		m_vsByteCode.size(),
		m_inputLayout.GetAddressOf()));
}

void DX11Device::ConstantBufferUpdate(XMMATRIX worldViewProj)
{
	// 상수 버퍼 업데이트
	SConstBuffer _constBuffer;
	_constBuffer.WVPTM = XMMatrixTranspose(worldViewProj);
	m_deviceContext->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &_constBuffer, 0, 0);
}

void DX11Device::RenderingPipeline()
{
	m_deviceContext->IASetInputLayout(m_inputLayout.Get());
	m_deviceContext->IASetPrimitiveTopology(m_primitive);
	if (m_nowRS == 0)
		m_deviceContext->RSSetState(m_wireframeRS.Get());
	else if (m_nowRS == 1)
		m_deviceContext->RSSetState(m_solidRS.Get());
			

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
	m_deviceContext->IASetIndexBuffer(m_ib, DXGI_FORMAT_R32_UINT, 0);

	// Set the vertex shader.
	m_deviceContext->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0
	);

	// Set the pixel shader.
	m_deviceContext->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
	);

	// Set the vertex shader constant buffer data.
	m_deviceContext->VSSetConstantBuffers(
		0,  // register 0
		1,  // one constant buffer
		m_constantBuffer.GetAddressOf()
	);

	m_deviceContext->PSSetConstantBuffers(
		0,  // register 0
		1,  // one constant buffer
		m_constantBuffer.GetAddressOf()
	);
}

void DX11Device::BeginRender()
{
	assert(m_deviceContext);

	// 랜더타겟 뷰를 클리어한다.
	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), reinterpret_cast<const float*>(&DirectX::Colors::Black));

	// 뎁스스탠실 뷰를 클리어한다.
	m_deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_deviceContext->OMSetDepthStencilState(NormalDSS.Get(), 0);
}

void DX11Device::Render()
{
	m_deviceContext->DrawIndexed(
		m_indexCount,
		0,  // start with index 0
		0   // start with vertex 0
	);
}

void DX11Device::EndRender()
{
	assert(m_swapChain);

	// 프리젠트 꼭 해줘야 한다.
	HR(m_swapChain->Present(0, 0));
}

