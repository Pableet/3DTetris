#include "TestScene.h"
#include "Renderer.h"
#include "Transform.h"
#include "Tetromino.h"
#include "TetrisMechanism.h"

void TestScene::Awake()
{

}

void TestScene::Start()
{
	
// 	m_objectManager->FindObjectFromName("testblock")->GetComponent<Renderer>()->AddBox();
// 	m_objectManager->FindObjectFromName("testblock2")->GetComponent<Renderer>()->AddBox();
	m_objectManager->FindObjectFromName("testfloor")->GetComponent<Renderer>()->AddGrid(7, 7);
	m_objectManager->FindObjectFromName("testwall_L")->GetComponent<Renderer>()->AddGrid(7, 16);
	m_objectManager->FindObjectFromName("testwall_R")->GetComponent<Renderer>()->AddGrid(7, 16);
	m_objectManager->FindObjectFromName("testwall_U")->GetComponent<Renderer>()->AddGrid(7, 16);
	m_objectManager->FindObjectFromName("testwall_D")->GetComponent<Renderer>()->AddGrid(7, 16);

	

// 	m_objectManager->FindObjectFromName("testblock")->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);
// 	m_objectManager->FindObjectFromName("testblock")->GetComponent<Renderer>()->SetRS(1);
// 	m_objectManager->FindObjectFromName("testblock")->GetComponent<Transform>()->Translate({ 0.5f,6.5f,0.5f });
// 	m_objectManager->FindObjectFromName("testblock2")->GetComponent<Renderer>()->SetBoxColor(0.f, 0.f, 0.f, 1.f);
// 
// 	m_objectManager->FindObjectFromName("testblock")->GetComponent<Renderer>()->SetRectSize(0.49f);
// 	m_objectManager->FindObjectFromName("testblock2")->GetComponent<Renderer>()->SetRectSize(0.5f);
// 
// 	m_objectManager->SetParentByGameObject(m_objectManager->FindObjectFromName("testblock2"), m_objectManager->FindObjectFromName("testblock"));



	m_objectManager->FindObjectFromName("testwall_L")->GetComponent<Transform>()->Rotate({ 90.f,0.f,90.f });
	m_objectManager->FindObjectFromName("testwall_R")->GetComponent<Transform>()->Rotate({ 90.f,0.f,90.f });
	m_objectManager->FindObjectFromName("testwall_U")->GetComponent<Transform>()->Rotate({ 90.f,0.f,0.f });
	m_objectManager->FindObjectFromName("testwall_D")->GetComponent<Transform>()->Rotate({ 90.f,0.f,0.f });

	m_objectManager->FindObjectFromName("testfloor")->GetComponent<Transform>()->Translate({ 0.5f,0.5f,0.5f });
	m_objectManager->FindObjectFromName("testwall_L")->GetComponent<Transform>()->Translate({ -3.5f,12.5f,0.5f });
	m_objectManager->FindObjectFromName("testwall_R")->GetComponent<Transform>()->Translate({ 3.5f,12.5f,0.5f });
	m_objectManager->FindObjectFromName("testwall_U")->GetComponent<Transform>()->Translate({ 0.5f,12.5f,3.5f });
	m_objectManager->FindObjectFromName("testwall_D")->GetComponent<Transform>()->Translate({ 0.5f,12.5f,-3.5f });

	for (auto& e : m_objects)
	{
		e->Start();
	}
}

void TestScene::FixedUpdate()
{
	for (auto& e : m_objects)
	{
		e->FixedUpdate();
	}
}

void TestScene::Update(float dTime)
{
	for (auto& e : m_objects)
	{
		e->Update(dTime);
	}
}

void TestScene::LateUpdate(float dTime)
{
	for (auto& e : m_objects)
	{
		e->LateUpdate(dTime);
	}
}

void TestScene::Render()
{
	m_objectManager->FindObjectFromName("testscore")->GetComponent<Renderer>()->AddText(1050, 100, 1, 1, 1, 1, L"SCORE");
	m_objectManager->FindObjectFromName("testscore")->GetComponent<Renderer>()->AddText(1070, 150, 1, 1, 1, 1, L"%d"
		, m_objectManager->FindObjectFromName("testmain")->GetComponent<TetrisMechanism>()->GetScore());

	m_objectManager->FindObjectFromName("testscore")->GetComponent<Renderer>()->AddText(120, 100, 1, 1, 1, 1, L"LEVEL");
	m_objectManager->FindObjectFromName("testscore")->GetComponent<Renderer>()->AddText(150, 150, 1, 1, 1, 1, L"%d"
		, m_objectManager->FindObjectFromName("testmain")->GetComponent<TetrisMechanism>()->GetLevel());
}

void TestScene::Release()
{
	for (auto& e : m_objects)
	{
		m_objectManager->DeleteObjectFromManager(e);
	}
	m_objectManager->DestroyObjects();
	m_objects.clear();
}

void TestScene::EditScene()
{
// 	m_objectManager->CreateObject("testblock");
// 	m_objectManager->FindObjectFromName("testblock")->AddComponent<Renderer, Tetromino>();
// 
// 	m_objectManager->CreateObject("testblock2");
// 	m_objectManager->FindObjectFromName("testblock2")->AddComponent<Renderer, Tetromino>();

	m_objectManager->CreateObject("testmain");
	m_objectManager->FindObjectFromName("testmain")->AddComponent<TetrisMechanism>();
	m_objectManager->FindObjectFromName("testmain")->GetComponent<TetrisMechanism>()->SetObjectManager(m_objectManager);

	m_objectManager->CreateObject("testfloor");
	m_objectManager->FindObjectFromName("testfloor")->AddComponent<Renderer>();

	m_objectManager->CreateObject("testwall_L");
	m_objectManager->FindObjectFromName("testwall_L")->AddComponent<Renderer>();

	m_objectManager->CreateObject("testwall_R");
	m_objectManager->FindObjectFromName("testwall_R")->AddComponent<Renderer>();

	m_objectManager->CreateObject("testwall_U");
	m_objectManager->FindObjectFromName("testwall_U")->AddComponent<Renderer>();

	m_objectManager->CreateObject("testwall_D");
	m_objectManager->FindObjectFromName("testwall_D")->AddComponent<Renderer>();

	m_objectManager->CreateObject("testscore");
	m_objectManager->FindObjectFromName("testscore")->AddComponent<Renderer>();

	m_objects.push_back(m_objectManager->FindObjectFromName("testmain"));
// 	m_objects.push_back(m_objectManager->FindObjectFromName("testblock"));
// 	m_objects.push_back(m_objectManager->FindObjectFromName("testblock2"));
	m_objects.push_back(m_objectManager->FindObjectFromName("testfloor"));
	m_objects.push_back(m_objectManager->FindObjectFromName("testwall_L"));
	m_objects.push_back(m_objectManager->FindObjectFromName("testwall_R"));
	m_objects.push_back(m_objectManager->FindObjectFromName("testwall_U"));
	m_objects.push_back(m_objectManager->FindObjectFromName("testwall_D"));
	m_objects.push_back(m_objectManager->FindObjectFromName("testscore"));
}
