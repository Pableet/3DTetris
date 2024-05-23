#include "GameScene.h"
#include "Renderer.h"
#include "Transform.h"
#include "Tetromino.h"
#include "TetrisMechanism.h"
#include "InputManager.h"
#include "SceneManager.h"

void GameScene::Awake()
{

}

void GameScene::Start()
{

	// 	m_objectManager->FindObjectFromName("testblock")->GetComponent<Renderer>()->AddBox();
	// 	m_objectManager->FindObjectFromName("testblock2")->GetComponent<Renderer>()->AddBox();
	m_objectManager->FindObjectFromName("Floor")->GetComponent<Renderer>()->AddGrid(7, 7);
	m_objectManager->FindObjectFromName("Wall_L")->GetComponent<Renderer>()->AddGrid(7, 16);
	m_objectManager->FindObjectFromName("Wall_R")->GetComponent<Renderer>()->AddGrid(7, 16);
	m_objectManager->FindObjectFromName("Wall_U")->GetComponent<Renderer>()->AddGrid(7, 16);
	m_objectManager->FindObjectFromName("Wall_D")->GetComponent<Renderer>()->AddGrid(7, 16);



	// 	m_objectManager->FindObjectFromName("testblock")->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);
	// 	m_objectManager->FindObjectFromName("testblock")->GetComponent<Renderer>()->SetRS(1);
	// 	m_objectManager->FindObjectFromName("testblock")->GetComponent<Transform>()->Translate({ 0.5f,6.5f,0.5f });
	// 	m_objectManager->FindObjectFromName("testblock2")->GetComponent<Renderer>()->SetBoxColor(0.f, 0.f, 0.f, 1.f);
	// 
	// 	m_objectManager->FindObjectFromName("testblock")->GetComponent<Renderer>()->SetRectSize(0.49f);
	// 	m_objectManager->FindObjectFromName("testblock2")->GetComponent<Renderer>()->SetRectSize(0.5f);
	// 
	// 	m_objectManager->SetParentByGameObject(m_objectManager->FindObjectFromName("testblock2"), m_objectManager->FindObjectFromName("testblock"));



	m_objectManager->FindObjectFromName("Wall_L")->GetComponent<Transform>()->Rotate({ 90.f,0.f,90.f });
	m_objectManager->FindObjectFromName("Wall_R")->GetComponent<Transform>()->Rotate({ 90.f,0.f,90.f });
	m_objectManager->FindObjectFromName("Wall_U")->GetComponent<Transform>()->Rotate({ 90.f,0.f,0.f });
	m_objectManager->FindObjectFromName("Wall_D")->GetComponent<Transform>()->Rotate({ 90.f,0.f,0.f });

	m_objectManager->FindObjectFromName("Floor")->GetComponent<Transform>()->Translate({ 0.5f,0.5f,0.5f });
	m_objectManager->FindObjectFromName("Wall_L")->GetComponent<Transform>()->Translate({ -3.5f,12.5f,0.5f });
	m_objectManager->FindObjectFromName("Wall_R")->GetComponent<Transform>()->Translate({ 3.5f,12.5f,0.5f });
	m_objectManager->FindObjectFromName("Wall_U")->GetComponent<Transform>()->Translate({ 0.5f,12.5f,3.5f });
	m_objectManager->FindObjectFromName("Wall_D")->GetComponent<Transform>()->Translate({ 0.5f,12.5f,-3.5f });

	for (auto& e : m_objects)
	{
		e->Start();
	}
}

void GameScene::FixedUpdate()
{
	if (!m_objectManager->FindObjectFromName("Main")->GetComponent<TetrisMechanism>()->GetIsGameEnd())
	{
		for (auto& e : m_objects)
		{
			e->FixedUpdate();
		}
	}
}

void GameScene::Update(float dTime)
{
	if (!m_objectManager->FindObjectFromName("Main")->GetComponent<TetrisMechanism>()->GetIsGameEnd())
	{
		for (auto& e : m_objects)
		{
			e->Update(dTime);
		}
	}
}

void GameScene::LateUpdate(float dTime)
{
	if (!m_objectManager->FindObjectFromName("Main")->GetComponent<TetrisMechanism>()->GetIsGameEnd())
	{
		for (auto& e : m_objects)
		{
			e->LateUpdate(dTime);
		}
	}
}

void GameScene::Render()
{
	m_objectManager->FindObjectFromName("Score")->GetComponent<Renderer>()->AddText(1050, 100, 1, 1, 1, 1, L"SCORE");
	m_objectManager->FindObjectFromName("Score")->GetComponent<Renderer>()->AddText(1070, 150, 1, 1, 1, 1, L"%d"
		, m_objectManager->FindObjectFromName("Main")->GetComponent<TetrisMechanism>()->GetScore());

	m_objectManager->FindObjectFromName("Score")->GetComponent<Renderer>()->AddText(120, 100, 1, 1, 1, 1, L"LEVEL");
	m_objectManager->FindObjectFromName("Score")->GetComponent<Renderer>()->AddText(150, 150, 1, 1, 1, 1, L"%d"
		, m_objectManager->FindObjectFromName("Main")->GetComponent<TetrisMechanism>()->GetLevel());

	m_objectManager->FindObjectFromName("Pit")->GetComponent<Renderer>()->AddText(1100, 350, 1, 1, 1, 1, L"PIT");

	if (m_objectManager->FindObjectFromName("Main")->GetComponent<TetrisMechanism>()->GetIsGameEnd())
	{
		m_objectManager->FindObjectFromName("GameOver")->GetComponent<Renderer>()->AddText(550, 350, 1, 1, 1, 1, L"Game Over");
		if (InputManager::GetInstance()->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Enter))
		{
			PostQuitMessage(0);
		}
	}
}

void GameScene::Release()
{
	for (auto& e : m_objects)
	{
		m_objectManager->DeleteObjectFromManager(e);
	}
	m_objectManager->DestroyObjects();
	m_objects.clear();
}

void GameScene::EditScene()
{
	// 	m_objectManager->CreateObject("testblock");
	// 	m_objectManager->FindObjectFromName("testblock")->AddComponent<Renderer, Tetromino>();
	// 
	// 	m_objectManager->CreateObject("testblock2");
	// 	m_objectManager->FindObjectFromName("testblock2")->AddComponent<Renderer, Tetromino>();

	m_objectManager->CreateObject("Main");
	m_objectManager->FindObjectFromName("Main")->AddComponent<TetrisMechanism>();
	m_objectManager->FindObjectFromName("Main")->GetComponent<TetrisMechanism>()->SetObjectManager(m_objectManager);

	m_objectManager->CreateObject("Floor");
	m_objectManager->FindObjectFromName("Floor")->AddComponent<Renderer>();

	m_objectManager->CreateObject("Wall_L");
	m_objectManager->FindObjectFromName("Wall_L")->AddComponent<Renderer>();

	m_objectManager->CreateObject("Wall_R");
	m_objectManager->FindObjectFromName("Wall_R")->AddComponent<Renderer>();

	m_objectManager->CreateObject("Wall_U");
	m_objectManager->FindObjectFromName("Wall_U")->AddComponent<Renderer>();

	m_objectManager->CreateObject("Wall_D");
	m_objectManager->FindObjectFromName("Wall_D")->AddComponent<Renderer>();

	m_objectManager->CreateObject("Score");
	m_objectManager->FindObjectFromName("Score")->AddComponent<Renderer>();

	m_objectManager->CreateObject("Pit");
	m_objectManager->FindObjectFromName("Pit")->AddComponent<Renderer>();

	m_objectManager->CreateObject("GameOver");
	m_objectManager->FindObjectFromName("GameOver")->AddComponent<Renderer>();

	m_objects.push_back(m_objectManager->FindObjectFromName("Main"));
	// 	m_objects.push_back(m_objectManager->FindObjectFromName("testblock"));
	// 	m_objects.push_back(m_objectManager->FindObjectFromName("testblock2"));
	m_objects.push_back(m_objectManager->FindObjectFromName("Floor"));
	m_objects.push_back(m_objectManager->FindObjectFromName("Wall_L"));
	m_objects.push_back(m_objectManager->FindObjectFromName("Wall_R"));
	m_objects.push_back(m_objectManager->FindObjectFromName("Wall_U"));
	m_objects.push_back(m_objectManager->FindObjectFromName("Wall_D"));
	m_objects.push_back(m_objectManager->FindObjectFromName("Score"));
	m_objects.push_back(m_objectManager->FindObjectFromName("Pit"));
	m_objects.push_back(m_objectManager->FindObjectFromName("GameOver"));
}
