#include "D3DRenderer.h"
#include "DX11Device.h"
#include "Camera.h"
#include "Box.h"
#include "Grid.h"
#include "Text.h"

D3DRenderer::D3DRenderer()
	: m_appPaused(false), m_dx11Device(nullptr)
	, m_hWnd(nullptr), m_hInst(nullptr), m_screenWidth(0), m_screenHeight(0)
	, m_maximized(false), m_minimized(false), m_camera(nullptr), m_text(nullptr)
{

}

D3DRenderer::~D3DRenderer()
{
	m_objects.clear();
	delete m_camera;
	delete m_dx11Device;
}

bool D3DRenderer::Initialize(int hWnd, int hInstance, int screenWidth, int screenHeight)
{
	m_hWnd = (HWND)hWnd;
	m_hInst = (HINSTANCE)hInstance;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_dx11Device = new DX11Device();
	m_dx11Device->Create(m_hWnd, m_screenWidth, m_screenHeight);
	m_dx11Device->CreateVertexShader();
	m_dx11Device->CreatePixelShader();
	m_dx11Device->CreateConstantBuffer();
	m_dx11Device->CreateRenderStates();
	m_dx11Device->CreateInputLayout();

	m_camera = new Camera();
	m_camera->LookAt(XMFLOAT3(0.0f, 26.0f, 0.0f), XMFLOAT3(0, 0, 0), XMFLOAT3(0.f, 0.0f, 1));
	//m_camera->LookAt(XMFLOAT3(8.0f, 18.0f, -8.0f), XMFLOAT3(0, 0, 0), XMFLOAT3(0, 1.0f, 0));

	m_text = new Text;
	m_text->Create(m_dx11Device->GetDevice(), m_dx11Device->GetSolidRS(), m_dx11Device->GetNormalDSS());

	OnResize();


	return true;
}

void D3DRenderer::Update(float dTime)
{
	m_camera->UpdateViewMatrix();

	for (auto& obj : m_objects)
	{
		obj->SetViewMatrix(m_camera->View());
		obj->SetProjMatrix(m_camera->Proj());

		obj->Update();
	}
}

void D3DRenderer::BeginRender()
{
	m_dx11Device->BeginRender();
}

void D3DRenderer::Render()
{
	// 어떻게 할까

	for (auto& obj : m_objects)
	{
		m_dx11Device->SetPrimitive(obj->GetPrimitive());
		m_dx11Device->SetBuffers(obj->GetVertexBuffer(), obj->GetIndexBuffer());
		m_dx11Device->SetIndexCount(obj->GetIndexCount());
		m_dx11Device->SetRS(obj->GetRS());

		// 각각 가지고 있는 상태로 그려야되서 옮김
		m_dx11Device->ConstantBufferUpdate(obj->GetWVP());

		m_dx11Device->RenderingPipeline();
		m_dx11Device->Render();
	}

}

void D3DRenderer::LateRender()
{
	
}

void D3DRenderer::EndRender()
{
	m_dx11Device->EndRender();
}

void D3DRenderer::Finalize()
{

}

void D3DRenderer::OnResize()
{
	m_dx11Device->OnResize(m_screenWidth, m_screenHeight);
	m_camera->SetLens(0.25f * 3.1415926535f, static_cast<float>(m_screenWidth) / m_screenHeight, 1.0f, 1000.0f);

}

bool D3DRenderer::IsValidDevice()
{
	return (m_dx11Device->GetDevice() != nullptr);
}

void D3DRenderer::SetClientSize(int screenWidth, int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
}

void D3DRenderer::SetWinMinMax(bool isMinimized, bool isMaxmized)
{
	m_minimized = isMinimized;
	m_maximized = isMaxmized;
}

void D3DRenderer::AddBox(std::string name, int nowRS)
{
	m_camera->UpdateViewMatrix();
	IObject* box = new Box();

	box->SetName(name);
	box->SetScale(0.5f);
	box->SetColor(1.f, 1.f, 1.f, 1.f);
	box->SetRenderState(nowRS);
	box->Initialize(m_dx11Device->GetDevice());

	box->SetViewMatrix(m_camera->View());
	box->SetProjMatrix(m_camera->Proj());

	XMMATRIX position = XMMatrixIdentity();
	XMFLOAT4X4 world;
	XMStoreFloat4x4(&world, position);
	box->SetWorldMatrix(XMLoadFloat4x4(&world));

	box->Update();
	m_objects.emplace_back(box);
}

void D3DRenderer::AddBox(int id, int nowRS)
{
	m_camera->UpdateViewMatrix();
	IObject* box = new Box();

	box->SetID(id);
	box->SetScale(0.5f);
	box->SetColor(1.f, 1.f, 1.f, 1.f);
	box->SetRenderState(nowRS);
	box->Initialize(m_dx11Device->GetDevice());

	box->SetViewMatrix(m_camera->View());
	box->SetProjMatrix(m_camera->Proj());

	XMMATRIX position = XMMatrixIdentity();
	XMFLOAT4X4 world;
	XMStoreFloat4x4(&world, position);
	box->SetWorldMatrix(XMLoadFloat4x4(&world));

	box->Update();
	m_objects.emplace_back(box);
}

void D3DRenderer::SetBoxColor(std::string name, float r, float g, float b, float a)
{
	for (auto& e : m_objects)
	{
		if (e->GetName() == name)
		{
			e->SetColor(r, g, b, a);
			e->Initialize(m_dx11Device->GetDevice());
		}
	}
}

void D3DRenderer::SetBoxColor(int id, float r, float g, float b, float a)
{
	for (auto& e : m_objects)
	{
		if (e->GetID() == id)
		{
			e->SetColor(r, g, b, a);
			e->Initialize(m_dx11Device->GetDevice());
		}
	}
}

void D3DRenderer::AddGrid(std::string name, int gridSize_x, int gridSize_y)
{
	m_camera->UpdateViewMatrix();
	IObject* grid = new Grid;

	grid->SetName(name);
	grid->SetGridXY(gridSize_x, gridSize_y);
	grid->Initialize(m_dx11Device->GetDevice());

	grid->SetViewMatrix(m_camera->View());
	grid->SetProjMatrix(m_camera->Proj());

	XMMATRIX position = XMMatrixIdentity();
	XMFLOAT4X4 world;
	XMStoreFloat4x4(&world, position);
	grid->SetWorldMatrix(XMLoadFloat4x4(&world));

	grid->Update();
	m_objects.emplace_back(grid);
}

void D3DRenderer::SetRenderState(std::string name, int nowRS)
{
	for (auto& e : m_objects)
	{
		if (e->GetName() == name)
		{
			e->SetRenderState(nowRS);
		}
	}
}

void D3DRenderer::SetRenderState(int id, int nowRS)
{
	for (auto& e : m_objects)
	{
		if (e->GetID() == id)
		{
			e->SetRenderState(nowRS);
		}
	}
}

void D3DRenderer::SetRectSize(std::string name, float scale)
{
	for (auto& e : m_objects)
	{
		if (e->GetName() == name)
		{
			e->SetScale(scale);
			e->Initialize(m_dx11Device->GetDevice());
		}
	}
}

void D3DRenderer::SetRectSize(int id, float scale)
{
	for (auto& e : m_objects)
	{
		if (e->GetID() == id)
		{
			e->SetScale(scale);
			e->Initialize(m_dx11Device->GetDevice());
		}
	}
}

void D3DRenderer::Rotate(std::string name, float x, float y, float z)
{
	for (auto& e : m_objects)
	{
		if (e->GetName() == name)
		{
			e->SetRotation(x, y, z);
		}
	}
}

void D3DRenderer::TransformObjectFromName(std::string name, const XMMATRIX& world)
{
	for (auto& e : m_objects)
	{
		if (e->GetName() == name)
		{
			e->SetWorldMatrix(world);
		}
	}
}

void D3DRenderer::TransformObjectFromID(int id, const XMMATRIX& world)
{
	for (auto& e : m_objects)
	{
		if (e->GetID() == id)
		{
			e->SetWorldMatrix(world);
		}
	}
}

void D3DRenderer::DeleteObject(int id)
{
	for (auto& e : m_objects)
	{
		if (e->GetID() == id)
		{
			m_objects.erase(remove(m_objects.begin(), m_objects.end(), e), m_objects.end());
		}
	}
}

void D3DRenderer::DeleteObject(std::string name)
{
	for (auto& e : m_objects)
	{
		if (e->GetName() == name)
		{
			m_objects.erase(remove(m_objects.begin(), m_objects.end(), e), m_objects.end());
		}
	}
}

void D3DRenderer::DrawColoredText(int x, int y, float r, float g, float b, float a, int id, const wchar_t* text)
{
	m_text->DrawColorText(x, y, { r,g,b,a }, text);
}

