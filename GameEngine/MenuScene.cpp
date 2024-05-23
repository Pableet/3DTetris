#include "MenuScene.h"
#include "Renderer.h"
#include "Transform.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TetrisMechanism.h"

void MenuScene::Awake()
{

}

void MenuScene::Start()
{

}

void MenuScene::FixedUpdate()
{

}

void MenuScene::Update(float dTime)
{
	if (!m_isPressStart && InputManager::GetInstance()->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Enter))
	{
		m_isPressStart = true;
	}

	if (m_showSelect && m_selectedLevel > 1 &&
		InputManager::GetInstance()->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Left))
	{
		m_selectedLevel--;
		m_arrowPos -= 100;
	}

	if (m_showSelect && m_selectedLevel < 6 &&
		InputManager::GetInstance()->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Right))
	{

		m_selectedLevel++;
		m_arrowPos += 100;
	}

	if (m_isPressStart && !m_showSelect &&
		(InputManager::GetInstance()->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Left)
			|| InputManager::GetInstance()->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Right)))
	{
		m_showSelect = true;
		m_selectedLevel = 1;
		m_arrowPos = 320; 
	}

	if (m_showSelect && InputManager::GetInstance()->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Enter))
	{
		m_objectManager->FindObjectFromName("Main")->GetComponent<TetrisMechanism>()->SetLevel(m_selectedLevel);
		m_sceneManager->SetCurrentScene(1);
	}

}

void MenuScene::LateUpdate(float dTime)
{

}

void MenuScene::Render()
{
	if (!m_isPressStart)
	{
		m_objectManager->FindObjectFromName("PressEnter")->GetComponent<Renderer>()->AddText(500, 400, 1, 1, 1, 1, L"Press Enter To Start");
	}

	if (m_isPressStart)
	{
		m_objectManager->FindObjectFromName("SelectLevel")->GetComponent<Renderer>()->AddText(530, 300, 1, 1, 1, 1, L"Select the Level");
		m_objectManager->FindObjectFromName("Levels")->GetComponent<Renderer>()->AddText(350, 450, 1, 1, 1, 1,
			L"1           2           3           4           5           6");
		if (m_showSelect)
		{
			m_objectManager->FindObjectFromName("Levels")->GetComponent<Renderer>()->AddText(m_arrowPos, 450, 1, 1, 1, 1, L"->");
		}
	}

	// 	m_objectManager->FindObjectFromName("Score")->GetComponent<Renderer>()->AddText(120, 100, 1, 1, 1, 1, L"LEVEL");
	// 	m_objectManager->FindObjectFromName("Score")->GetComponent<Renderer>()->AddText(150, 150, 1, 1, 1, 1, L"%d");
}

void MenuScene::Release()
{

}

void MenuScene::EditScene()
{
	m_objectManager->CreateObject("PressEnter");
	m_objectManager->FindObjectFromName("PressEnter")->AddComponent<Renderer>();
	m_objects.push_back(m_objectManager->FindObjectFromName("PressEnter"));

	m_objectManager->CreateObject("SelectLevel");
	m_objectManager->FindObjectFromName("SelectLevel")->AddComponent<Renderer>();
	m_objects.push_back(m_objectManager->FindObjectFromName("SelectLevel"));

	m_objectManager->CreateObject("Levels");
	m_objectManager->FindObjectFromName("Levels")->AddComponent<Renderer>();
	m_objects.push_back(m_objectManager->FindObjectFromName("Levels"));

	m_objectManager->CreateObject("Arrow");
	m_objectManager->FindObjectFromName("Arrow")->AddComponent<Renderer>();
	m_objects.push_back(m_objectManager->FindObjectFromName("Arrow"));
}
