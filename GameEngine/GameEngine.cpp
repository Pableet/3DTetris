#include "GameEngine.h"
#include "../Graphics/I3DRenderer.h"
#include "Component.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "InputManager.h"

GameEngine::GameEngine(HWND hWNd, HINSTANCE hInst, int screenWidth, int screenHeight)
	: m_hWnd(hWNd), m_hInst(hInst), m_screenWidth(screenWidth), m_screenHeight(screenHeight)
	, m_dTime(0.f), m_renderer(nullptr), m_fixTime(0.f), m_objectManager(nullptr)
	, m_sceneManager(nullptr)
{

}

GameEngine::~GameEngine()
{
	delete m_sceneManager;
	delete m_objectManager;
}

void GameEngine::Initialize()
{
	m_objectManager = new ObjectManager;
	m_sceneManager = new SceneManager;
	m_sceneManager->SetObjectManager(m_objectManager);

	Component::SetRenderer(m_renderer);
	m_sceneManager->Awake();
	m_sceneManager->Start(); 

	InputManager::GetInstance()->Initialize(m_hWnd);
}

void GameEngine::Update(float dTime)
{
	InputManager::GetInstance()->Update();

	m_dTime = dTime;

	m_fixTime += dTime;
	if (m_fixTime > 0.01f)
	{
		m_sceneManager->FixedUpdate();
		m_fixTime = 0.f;
	}
	m_sceneManager->Update(m_dTime);
	m_sceneManager->LateUpdate(m_dTime);
}

void GameEngine::Render()
{
	m_renderer->BeginRender();
	m_renderer->Render();
	m_renderer->LateRender();
	m_sceneManager->Render();
	m_renderer->EndRender();

}

void GameEngine::Release()
{
	m_sceneManager->Release();

	InputManager::GetInstance()->Release();
}
