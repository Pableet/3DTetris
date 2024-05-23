#include "SceneManager.h"
#include "TestScene.h"
#include "MenuScene.h"
#include "GameScene.h"

SceneManager::SceneManager()
	: m_currentScene(nullptr), m_objectManager(nullptr)
{
	IScene* scene = new TestScene();
	IScene* menuScene = new MenuScene();
	IScene* gameScene = new GameScene();
	//AddScene(scene);
	AddScene(menuScene);
	AddScene(gameScene);

	menuScene->SetSceneManager(this);
	gameScene->SetSceneManager(this);

	SetCurrentScene(0);
}

SceneManager::~SceneManager()
{
	m_scenes.clear();
}

void SceneManager::Awake()
{
	for (auto& e : m_scenes)
	{
		e->SetObjectManager(m_objectManager);
		e->EditScene();
		e->Awake();
	}
}

void SceneManager::Start()
{
	m_currentScene->Start();
}

void SceneManager::FixedUpdate()
{
	m_currentScene->FixedUpdate();
}

void SceneManager::Update(float dTime)
{
	m_currentScene->Update(dTime);
}

void SceneManager::LateUpdate(float dTime)
{
	m_currentScene->LateUpdate(dTime);
}

void SceneManager::Render()
{
	m_currentScene->Render();
}

void SceneManager::Release()
{
	for (auto& e : m_scenes)
	{
		e->Release();
	}
}

void SceneManager::AddScene(IScene* scene)
{
	m_scenes.push_back(scene);
}

void SceneManager::SetCurrentScene(int index)
{
	m_currentScene = m_scenes[index];
	Start();
}
