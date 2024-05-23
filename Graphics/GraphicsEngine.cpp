#include "GraphicsEngine.h"
#include "I3DRenderer.h"


GraphicsEngine::GraphicsEngine(int hWnd, int hInstance, int screenWidth, int screenHeight)
{
	//m_renderer = new D3DRenderer;
	m_renderer = I3DRenderer::CreateRenderer();
	m_renderer->Initialize(hWnd, hInstance, screenWidth, screenHeight);
	m_renderer->OnResize();
// 	m_renderer->AddBox({ 0.f,0.f,0.f }, { 1.f,1.f,1.f,1.f }, 0);
// 	m_renderer->AddGrid({ 0.f,0.f,0.f }, { 7, 16 });
// 	m_renderer->AddBox({ 2.f,0.f,0.f }, { 1.f,1.f,1.f,1.f }, 0);
// 	m_renderer->AddBox({ 4.f,0.f,0.f }, { 1.f,1.f,1.f,1.f }, 0);
}

GraphicsEngine::~GraphicsEngine()
{
	delete m_renderer;
}

void GraphicsEngine::Update(float deltaTime)
{
	m_renderer->Update(deltaTime);
}

void GraphicsEngine::Render()
{
	m_renderer->BeginRender();
	m_renderer->Render();
	m_renderer->EndRender();
}

void GraphicsEngine::Finalize()
{
	m_renderer->Finalize();
}

void GraphicsEngine::OnResize()
{
	m_renderer->OnResize();
}

bool GraphicsEngine::IsValidDevice()
{
	return m_renderer->IsValidDevice();
}

void GraphicsEngine::SetClientSize(int screenWidth, int screenHeight)
{
	m_renderer->SetClientSize(screenWidth, screenHeight);
}

void GraphicsEngine::SetWinMinMax(bool isMinimized, bool isMaxmized)
{
	m_renderer->SetWinMinMax(isMinimized, isMaxmized);
}
