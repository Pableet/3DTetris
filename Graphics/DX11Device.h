#pragma once
#include "DX11Define.h"


using namespace Microsoft::WRL;

class DX11Device
{
public:
	DX11Device();
	~DX11Device();

public:
	HRESULT Create(HWND hWnd, int screenWidth, int screenHeight);
	void OnResize(int screenWidth, int screenHeight);
	HRESULT CreateVertexShader();
	HRESULT CreatePixelShader();
	HRESULT CreateConstantBuffer();
	void CreateRenderStates();
	void CreateInputLayout();

	void ConstantBufferUpdate(XMMATRIX worldViewProj);

	void SetPrimitive(D3D_PRIMITIVE_TOPOLOGY primitive) { m_primitive = primitive; }
	void SetRS(int nowRS) { m_nowRS = nowRS; }
	void SetBuffers(ID3D11Buffer* vb, ID3D11Buffer* ib) { m_vb = vb; m_ib = ib; }
	void SetIndexCount(UINT indexCount) { m_indexCount = indexCount; }
	void RenderingPipeline();
	void BeginRender();
	void Render();
	void EndRender();

	// 상수 버퍼 구조체
	struct SConstBuffer
	{
		DirectX::XMMATRIX WVPTM;
	};



	ID3D11Device* GetDevice() const { return m_d3dDevice.Get(); }
	ID3D11DeviceContext* GetDeviceContext() const { return m_deviceContext.Get(); }
	IDXGISwapChain* GetSwapChain() const { return m_swapChain.Get(); }

	ID3D11RenderTargetView* GetRenderTargetView() const { return m_renderTargetView.Get(); }
	ID3D11DepthStencilView* GetDepthStencilView() const { return m_depthStencilView.Get(); }

	ID3D11RasterizerState* GetSolidRS() const { return m_solidRS.Get(); }
	ID3D11DepthStencilState* GetNormalDSS() const { return NormalDSS.Get(); }

private:
	ComPtr<ID3D11Device> m_d3dDevice;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	ComPtr<IDXGISwapChain> m_swapChain;
	ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	D3D11_VIEWPORT m_screenViewport;

	ComPtr<ID3D11VertexShader> m_vertexShader;
	ComPtr<ID3D11PixelShader> m_pixelShader;

	ID3D11Buffer* m_vb;
	ID3D11Buffer* m_ib;
	ComPtr<ID3D11Buffer> m_constantBuffer;
	ComPtr <ID3D11InputLayout> m_inputLayout;
	ComPtr <ID3D11RasterizerState> m_solidRS;
	ComPtr <ID3D11RasterizerState> m_wireframeRS;

	ComPtr <ID3D11DepthStencilState> NormalDSS;

	int m_nowRS;

	UINT m_creationFlags;
	D3D_FEATURE_LEVEL m_featureLevel;
	D3D_DRIVER_TYPE m_d3dDriverType;

	std::vector<uint8_t> m_vsByteCode;

	UINT m_indexCount;

	int m_screenWidth;
	int m_screenHeight;

	D3D_PRIMITIVE_TOPOLOGY m_primitive;
};

