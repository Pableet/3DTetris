#include "TetrisMechanism.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "Tetromino.h"
#include "RandomNumber.h"
#include "Controller.h"
#include "InputManager.h"

TetrisMechanism::~TetrisMechanism()
{
	m_pitBlocks.clear();
	m_blocks.clear();
	delete m_randomInt;
}

void TetrisMechanism::Start()
{
	m_randomInt = new RandomNumber();
	m_isGameEnded = false;
}

void TetrisMechanism::FixedUpdate()
{
	for (auto& e : m_blocks)
	{
		e->FixedUpdate();
	}
}

void TetrisMechanism::Update(float dTime)
{
	if (!m_isUsingBlock)
	{
		for (auto& e : m_nowBlocks)
		{
			float fx = e->GetComponent<Transform>()->GetWorldPosition().x;
			float fy = e->GetComponent<Transform>()->GetWorldPosition().y;
			float fz = e->GetComponent<Transform>()->GetWorldPosition().z;

			int x = m_randomInt->GetActualInt(fx) + 3;
			int y = -m_randomInt->GetActualInt(fy) + 16;
			int z = -m_randomInt->GetActualInt(fz) + 3;

			if (m_floor[z][x] < m_randomInt->GetActualInt(fy))
			{
				m_floor[z][x] = m_randomInt->GetActualInt(fy);
			}
			m_frontWall[y][x]++;
			m_leftWall[y][z]++;

			m_usedBlocks.push_back(std::make_pair(e, m_randomInt->GetActualInt(e->GetComponent<Transform>()->GetWorldPosition().y)));
			m_objectManager->SetParentByGameObject(e, nullptr);
		}
		m_nowBlocks.clear();
		int randomNum = m_randomInt->GetRandomInt(0, 7);
		switch (randomNum)
		{
		case 0:
			Create_R_2x2();
			break;

		case 1:
			Create_S_3x2();
			break;

		case 2:
			Create_L_3x2();
			break;

		case 3:
			Create_T_3x2();
			break;

		case 4:
			Create_O_1x1();
			break;

		case 5:
			Create_I_3x1();
			break;

		case 6:
			Create_I_2x1();
			break;

		case 7:
			Create_V_2x2();
			break;
		}
		// 테스트용 7칸짜리 1자블럭
		//Create_I_7x1();
		//Create_I_3x1();
	}
	for (auto& e : m_nowBlocks)
	{
		int fx = m_randomInt->GetActualInt(e->GetComponent<Transform>()->GetWorldPosition().x);
		int fy = m_randomInt->GetActualInt(e->GetComponent<Transform>()->GetWorldPosition().y);
		int fz = m_randomInt->GetActualInt(e->GetComponent<Transform>()->GetWorldPosition().z);


		int x = fx + 3;
		int y = -fy + 16;
		int z = -fz + 3;

		if (x >= 0 && z >= 0)
		{
			if (fy <= m_floor[z + 1][x])
			{
				for (auto& d : m_usedBlocks)
				{
					if (d.second == fy && m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().z) == fz - 1
						&& m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().x) == fx)
					{
						e->GetComponent<Tetromino>()->SetOnDown(true);
					}
				}
			}
			else
			{
				e->GetComponent<Tetromino>()->SetOnDown(false);
			}

			if (fy <= m_floor[z - 1][x])
			{
				for (auto& d : m_usedBlocks)
				{
					if (d.second == fy && m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().z) == fz + 1
						&& m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().x) == fx)
					{
						e->GetComponent<Tetromino>()->SetOnUp(true);
					}
				}
			}
			else
			{
				e->GetComponent<Tetromino>()->SetOnUp(false);
			}

			if (fy <= m_floor[z][x + 1])
			{
				for (auto& d : m_usedBlocks)
				{
					if (d.second == fy && m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().x) == fx + 1
						&& m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().z) == fz)
					{
						e->GetComponent<Tetromino>()->SetOnRight(true);
					}
				}
			}
			else
			{
				e->GetComponent<Tetromino>()->SetOnRight(false);
			}

			if (fy <= m_floor[z][x - 1])
			{
				for (auto& d : m_usedBlocks)
				{
					if (d.second == fy && m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().x) == fx - 1
						&& m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().z) == fz)
					{
						e->GetComponent<Tetromino>()->SetOnLeft(true);
					}
				}
			}
			else
			{
				e->GetComponent<Tetromino>()->SetOnLeft(false);
			}

			if (fy - 1 == 0)
			{
				e->GetComponent<Tetromino>()->SetIsOnFloor(true);
			}

			if (m_usedBlocks.size() != 0)
			{
				for (auto& d : m_usedBlocks)
				{
					int x1 = m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().x);
					int y1 = m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().y);
					int z1 = m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().z);

					if (m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().x) == fx
						&& d.second == fy - 1
						&& m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().z) == fz)
					{
						e->GetComponent<Tetromino>()->SetIsOnFloor(true);
						break;
					}
					else if (m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().x) == fx
						&& d.second != fy - 1
						&& m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().z) == fz)
					{
						e->GetComponent<Tetromino>()->SetIsOnFloor(false);
					}
					else if ((m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().x) != fx
						|| m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().z) != fz)
						&& d.second == fy - 1)
					{
						e->GetComponent<Tetromino>()->SetIsOnFloor(false);
					}

					if (m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().x) == fx
						&& d.second > fy - 1
						&& m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().z) == fz)
					{
						if (m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().x) == fx
							&& fy - 1 == 0
							&& m_randomInt->GetActualInt(d.first->GetComponent<Transform>()->GetWorldPosition().z) == fz)
						{
							e->GetComponent<Tetromino>()->SetIsOnFloor(true);
							break;
						}
					}
				}
			}
		}

		int disabledCount = 0;
		for (auto e : m_nowBlocks)
		{
			if (e->GetComponent<Tetromino>()->GetIsOnFloor())
			{
				disabledCount++;
			}
		}
		if (disabledCount != 0)
		{
			for (auto e : m_nowBlocks)
			{
				e->GetComponent<Tetromino>()->SetIsOnFloor(true);
			}
		}
		else
		{
			for (auto e : m_nowBlocks)
			{
				e->GetComponent<Tetromino>()->SetIsOnFloor(false);
			}
		}

		if (x >= 0 && z >= 0)
		{
			e->GetComponent<Tetromino>()->SetBlockHeight(m_floor[z][x]);
		}

	}

	{
		int deleteCount = 0;
		int deleted = 0;
		while (1)
		{
			if (deleteCount == 17 && deleted != 0)
			{
				deleteCount = 0;
				deleted = 0;
			}
			else if (deleteCount == 17 && deleted == 0)
			{
				break;
			}
			if (GetUsedBlockCount(deleteCount) == 49)
			{
				m_deleted++;
				deleted++;
				for (auto& e : m_usedBlocks)
				{
					if (e.second == deleteCount)
					{
						m_deleteBlocks.push_back(e);
						m_blocks.erase(remove(m_blocks.begin(), m_blocks.end(), e.first), m_blocks.end());
					}

					if (e.second > deleteCount)
					{
						e.second--;
						e.first->GetComponent<Transform>()->TranslateY(-1);
						e.first->GetComponent<Tetromino>()->UpdateColor();
					}
				}
				DeleteBlocks();
			}
			deleteCount++;
		}
		if (m_deleted == 1)
		{
			m_score += 100 * m_level;
			m_deleted = 0;
		}
		else if (m_deleted == 2)
		{
			m_score += 300 * m_level;
			m_deleted = 0;
		}
		else if (m_deleted == 3)
		{
			m_score += 500 * m_level;
			m_deleted = 0;
		}

		if (m_score > 999999)
		{
			m_score = 999999;
		}
	}

	for (auto& e : m_blocks)
	{
		e->Update(dTime);
	}

}

void TetrisMechanism::LateUpdate(float dTime)
{
	for (auto& e : m_nowBlocks)
	{
		if (!e->GetParent())
		{
			if (!e->GetComponent<Controller>()->GetIsSpin() && InputManager::GetInstance()->m_Keyboard.IsKeydown('F') && !m_isExchanged)
			{
				Pit();
				m_isExchanged = true;
			}
		}
	}


	for (auto& e : m_blocks)
	{
		e->LateUpdate(dTime);

	}

	int usingBlocks = 0;
	for (auto& e : m_nowBlocks)
	{
		if (!e->GetComponent<Tetromino>()->GetDisabled())
		{
			usingBlocks++;
		}
	}
	if (usingBlocks != m_nowBlocks.size())
	{
		m_isUsingBlock = false;
		m_isExchanged = false;

	}
	else
	{
		m_isUsingBlock = true;
	}
	if (m_nowBlocks.size() == 0 && m_isUsingBlock)
	{
		m_isUsingBlock = false;
	}


	/// 2d ui로 바꾸자 못생겼다
	for (auto& e : m_pitBlocks)
	{
		if (!e->GetParent())
		{
			e->GetComponent<Transform>()->SetPosition({ 5.f,17.f,-2.f });
		}
		e->LateUpdate(dTime);
	}
	for (int i = 0; i < 7; i++)
	{
		for (int k = 0; k < 7; k++)
		{
			if (m_floor[i][k] >= 17)
			{
				m_isGameEnded = true;
			}
		}
	}
	if (m_isGameEnded)
	{
		//PostQuitMessage(0);
	}

}

void TetrisMechanism::Create_R_2x2()
{
	GameObject* object = m_objectManager->CreateUnnamedObject();
	object->AddComponent<Renderer, Tetromino, Controller>();
	object->GetComponent<Renderer>()->AddBox();
	object->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object2 = m_objectManager->CreateUnnamedObject();
	object2->AddComponent<Renderer, Tetromino>();
	object2->GetComponent<Renderer>()->AddBox();
	object2->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object3 = m_objectManager->CreateUnnamedObject();
	object3->AddComponent<Renderer, Tetromino>();
	object3->GetComponent<Renderer>()->AddBox();
	object3->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object4 = m_objectManager->CreateUnnamedObject();
	object4->AddComponent<Renderer, Tetromino>();
	object4->GetComponent<Renderer>()->AddBox();
	object4->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	m_objectManager->SetParentByGameObject(object2, object);
	m_objectManager->SetParentByGameObject(object3, object);
	m_objectManager->SetParentByGameObject(object4, object);

	object->GetComponent<Transform>()->Translate({ 0,17,0 });
	object2->GetComponent<Transform>()->Translate({ -1,0,0 });
	object3->GetComponent<Transform>()->Translate({ 0,0,-1 });
	object4->GetComponent<Transform>()->Translate({ -1,0,-1 });

	object->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object2->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object3->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object4->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);

	object->GetComponent<Tetromino>()->SetLevel(m_level);
	object2->GetComponent<Tetromino>()->SetLevel(m_level);
	object3->GetComponent<Tetromino>()->SetLevel(m_level);
	object4->GetComponent<Tetromino>()->SetLevel(m_level);

	object->Start();
	object2->Start();
	object3->Start();
	object4->Start();

	m_blocks.push_back(object);
	m_blocks.push_back(object2);
	m_blocks.push_back(object3);
	m_blocks.push_back(object4);

	m_nowBlocks.push_back(object);
	m_nowBlocks.push_back(object2);
	m_nowBlocks.push_back(object3);
	m_nowBlocks.push_back(object4);

}

void TetrisMechanism::Create_S_3x2()
{
	GameObject* object = m_objectManager->CreateUnnamedObject();
	object->AddComponent<Renderer, Tetromino, Controller>();
	object->GetComponent<Renderer>()->AddBox();
	object->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object2 = m_objectManager->CreateUnnamedObject();
	object2->AddComponent<Renderer, Tetromino>();
	object2->GetComponent<Renderer>()->AddBox();
	object2->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object3 = m_objectManager->CreateUnnamedObject();
	object3->AddComponent<Renderer, Tetromino>();
	object3->GetComponent<Renderer>()->AddBox();
	object3->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object4 = m_objectManager->CreateUnnamedObject();
	object4->AddComponent<Renderer, Tetromino>();
	object4->GetComponent<Renderer>()->AddBox();
	object4->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	m_objectManager->SetParentByGameObject(object2, object);
	m_objectManager->SetParentByGameObject(object3, object);
	m_objectManager->SetParentByGameObject(object4, object);

	object->GetComponent<Transform>()->Translate({ 0,17,0 });
	object2->GetComponent<Transform>()->Translate({ 1,0,0 });
	object3->GetComponent<Transform>()->Translate({ 0,0,-1 });
	object4->GetComponent<Transform>()->Translate({ -1,0,-1 });

	object->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object2->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object3->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object4->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);

	object->GetComponent<Tetromino>()->SetLevel(m_level);
	object2->GetComponent<Tetromino>()->SetLevel(m_level);
	object3->GetComponent<Tetromino>()->SetLevel(m_level);
	object4->GetComponent<Tetromino>()->SetLevel(m_level);

	object->Start();
	object2->Start();
	object3->Start();
	object4->Start();

	m_blocks.push_back(object);
	m_blocks.push_back(object2);
	m_blocks.push_back(object3);
	m_blocks.push_back(object4);

	m_nowBlocks.push_back(object);
	m_nowBlocks.push_back(object2);
	m_nowBlocks.push_back(object3);
	m_nowBlocks.push_back(object4);
}

void TetrisMechanism::Create_L_3x2()
{
	GameObject* object = m_objectManager->CreateUnnamedObject();
	object->AddComponent<Renderer, Tetromino, Controller>();
	object->GetComponent<Renderer>()->AddBox();
	object->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object2 = m_objectManager->CreateUnnamedObject();
	object2->AddComponent<Renderer, Tetromino>();
	object2->GetComponent<Renderer>()->AddBox();
	object2->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object3 = m_objectManager->CreateUnnamedObject();
	object3->AddComponent<Renderer, Tetromino>();
	object3->GetComponent<Renderer>()->AddBox();
	object3->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object4 = m_objectManager->CreateUnnamedObject();
	object4->AddComponent<Renderer, Tetromino>();
	object4->GetComponent<Renderer>()->AddBox();
	object4->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	m_objectManager->SetParentByGameObject(object2, object);
	m_objectManager->SetParentByGameObject(object3, object);
	m_objectManager->SetParentByGameObject(object4, object);

	object->GetComponent<Transform>()->Translate({ 0,17,0 });
	object2->GetComponent<Transform>()->Translate({ 1,0,0 });
	object3->GetComponent<Transform>()->Translate({ -1,0,0 });
	object4->GetComponent<Transform>()->Translate({ -1,0,-1 });

	object->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object2->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object3->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object4->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);

	object->GetComponent<Tetromino>()->SetLevel(m_level);
	object2->GetComponent<Tetromino>()->SetLevel(m_level);
	object3->GetComponent<Tetromino>()->SetLevel(m_level);
	object4->GetComponent<Tetromino>()->SetLevel(m_level);

	object->Start();
	object2->Start();
	object3->Start();
	object4->Start();

	m_blocks.push_back(object);
	m_blocks.push_back(object2);
	m_blocks.push_back(object3);
	m_blocks.push_back(object4);

	m_nowBlocks.push_back(object);
	m_nowBlocks.push_back(object2);
	m_nowBlocks.push_back(object3);
	m_nowBlocks.push_back(object4);
}

void TetrisMechanism::Create_T_3x2()
{
	GameObject* object = m_objectManager->CreateUnnamedObject();
	object->AddComponent<Renderer, Tetromino, Controller>();
	object->GetComponent<Renderer>()->AddBox();
	object->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object2 = m_objectManager->CreateUnnamedObject();
	object2->AddComponent<Renderer, Tetromino>();
	object2->GetComponent<Renderer>()->AddBox();
	object2->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object3 = m_objectManager->CreateUnnamedObject();
	object3->AddComponent<Renderer, Tetromino>();
	object3->GetComponent<Renderer>()->AddBox();
	object3->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object4 = m_objectManager->CreateUnnamedObject();
	object4->AddComponent<Renderer, Tetromino>();
	object4->GetComponent<Renderer>()->AddBox();
	object4->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	m_objectManager->SetParentByGameObject(object2, object);
	m_objectManager->SetParentByGameObject(object3, object);
	m_objectManager->SetParentByGameObject(object4, object);

	object->GetComponent<Transform>()->Translate({ 0,17,0 });
	object2->GetComponent<Transform>()->Translate({ 1,0,0 });
	object3->GetComponent<Transform>()->Translate({ -1,0,0 });
	object4->GetComponent<Transform>()->Translate({ 0,0,-1 });

	object->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object2->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object3->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object4->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);

	object->GetComponent<Tetromino>()->SetLevel(m_level);
	object2->GetComponent<Tetromino>()->SetLevel(m_level);
	object3->GetComponent<Tetromino>()->SetLevel(m_level);
	object4->GetComponent<Tetromino>()->SetLevel(m_level);

	object->Start();
	object2->Start();
	object3->Start();
	object4->Start();

	m_blocks.push_back(object);
	m_blocks.push_back(object2);
	m_blocks.push_back(object3);
	m_blocks.push_back(object4);

	m_nowBlocks.push_back(object);
	m_nowBlocks.push_back(object2);
	m_nowBlocks.push_back(object3);
	m_nowBlocks.push_back(object4);
}

void TetrisMechanism::Create_O_1x1()
{
	GameObject* object = m_objectManager->CreateUnnamedObject();
	object->AddComponent<Renderer, Tetromino, Controller>();
	object->GetComponent<Renderer>()->AddBox();
	object->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);


	object->GetComponent<Transform>()->Translate({ 0,17,0 });

	object->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);

	object->GetComponent<Tetromino>()->SetLevel(m_level);

	object->Start();

	m_blocks.push_back(object);

	m_nowBlocks.push_back(object);
}

void TetrisMechanism::Create_I_3x1()
{
	GameObject* object = m_objectManager->CreateUnnamedObject();
	object->AddComponent<Renderer, Tetromino, Controller>();
	object->GetComponent<Renderer>()->AddBox();
	object->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object2 = m_objectManager->CreateUnnamedObject();
	object2->AddComponent<Renderer, Tetromino>();
	object2->GetComponent<Renderer>()->AddBox();
	object2->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object3 = m_objectManager->CreateUnnamedObject();
	object3->AddComponent<Renderer, Tetromino>();
	object3->GetComponent<Renderer>()->AddBox();
	object3->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);


	m_objectManager->SetParentByGameObject(object2, object);
	m_objectManager->SetParentByGameObject(object3, object);

	object->GetComponent<Transform>()->Translate({ 0,17,0 });
	object2->GetComponent<Transform>()->Translate({ 1,0,0 });
	object3->GetComponent<Transform>()->Translate({ -1,0,0 });

	object->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object2->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object3->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);

	object->GetComponent<Tetromino>()->SetLevel(m_level);
	object2->GetComponent<Tetromino>()->SetLevel(m_level);
	object3->GetComponent<Tetromino>()->SetLevel(m_level);

	object->Start();
	object2->Start();
	object3->Start();

	m_blocks.push_back(object);
	m_blocks.push_back(object2);
	m_blocks.push_back(object3);

	m_nowBlocks.push_back(object);
	m_nowBlocks.push_back(object2);
	m_nowBlocks.push_back(object3);
}

void TetrisMechanism::Create_I_2x1()
{
	GameObject* object = m_objectManager->CreateUnnamedObject();
	object->AddComponent<Renderer, Tetromino, Controller>();
	object->GetComponent<Renderer>()->AddBox();
	object->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object2 = m_objectManager->CreateUnnamedObject();
	object2->AddComponent<Renderer, Tetromino>();
	object2->GetComponent<Renderer>()->AddBox();
	object2->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);


	m_objectManager->SetParentByGameObject(object2, object);

	object->GetComponent<Transform>()->Translate({ 0,17,0 });
	object2->GetComponent<Transform>()->Translate({ 1,0,0 });

	object->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object2->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);

	object->GetComponent<Tetromino>()->SetLevel(m_level);
	object2->GetComponent<Tetromino>()->SetLevel(m_level);

	object->Start();
	object2->Start();

	m_blocks.push_back(object);
	m_blocks.push_back(object2);

	m_nowBlocks.push_back(object);
	m_nowBlocks.push_back(object2);
}

void TetrisMechanism::Create_V_2x2()
{
	GameObject* object = m_objectManager->CreateUnnamedObject();
	object->AddComponent<Renderer, Tetromino, Controller>();
	object->GetComponent<Renderer>()->AddBox();
	object->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object2 = m_objectManager->CreateUnnamedObject();
	object2->AddComponent<Renderer, Tetromino>();
	object2->GetComponent<Renderer>()->AddBox();
	object2->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object3 = m_objectManager->CreateUnnamedObject();
	object3->AddComponent<Renderer, Tetromino>();
	object3->GetComponent<Renderer>()->AddBox();
	object3->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);


	m_objectManager->SetParentByGameObject(object2, object);
	m_objectManager->SetParentByGameObject(object3, object);

	object->GetComponent<Transform>()->Translate({ 0,17,0 });
	object2->GetComponent<Transform>()->Translate({ 1,0,0 });
	object3->GetComponent<Transform>()->Translate({ 0,0,1 });

	object->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object2->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object3->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);

	object->GetComponent<Tetromino>()->SetLevel(m_level);
	object2->GetComponent<Tetromino>()->SetLevel(m_level);
	object3->GetComponent<Tetromino>()->SetLevel(m_level);

	object->Start();
	object2->Start();
	object3->Start();

	m_blocks.push_back(object);
	m_blocks.push_back(object2);
	m_blocks.push_back(object3);

	m_nowBlocks.push_back(object);
	m_nowBlocks.push_back(object2);
	m_nowBlocks.push_back(object3);
}

void TetrisMechanism::Create_I_7x1()
{
	GameObject* object = m_objectManager->CreateUnnamedObject();
	object->AddComponent<Renderer, Tetromino, Controller>();
	object->GetComponent<Renderer>()->AddBox();
	object->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object2 = m_objectManager->CreateUnnamedObject();
	object2->AddComponent<Renderer, Tetromino>();
	object2->GetComponent<Renderer>()->AddBox();
	object2->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object3 = m_objectManager->CreateUnnamedObject();
	object3->AddComponent<Renderer, Tetromino>();
	object3->GetComponent<Renderer>()->AddBox();
	object3->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object4 = m_objectManager->CreateUnnamedObject();
	object4->AddComponent<Renderer, Tetromino>();
	object4->GetComponent<Renderer>()->AddBox();
	object4->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object5 = m_objectManager->CreateUnnamedObject();
	object5->AddComponent<Renderer, Tetromino>();
	object5->GetComponent<Renderer>()->AddBox();
	object5->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object6 = m_objectManager->CreateUnnamedObject();
	object6->AddComponent<Renderer, Tetromino>();
	object6->GetComponent<Renderer>()->AddBox();
	object6->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	GameObject* object7 = m_objectManager->CreateUnnamedObject();
	object7->AddComponent<Renderer, Tetromino>();
	object7->GetComponent<Renderer>()->AddBox();
	object7->GetComponent<Renderer>()->SetBoxColor(1.f, 1.f, 1.f, 1.f);

	m_objectManager->SetParentByGameObject(object2, object);
	m_objectManager->SetParentByGameObject(object3, object);
	m_objectManager->SetParentByGameObject(object4, object);
	m_objectManager->SetParentByGameObject(object5, object);
	m_objectManager->SetParentByGameObject(object6, object);
	m_objectManager->SetParentByGameObject(object7, object);

	object->GetComponent<Transform>()->Translate({ 0,17,0 });
	object2->GetComponent<Transform>()->Translate({ 1,0,0 });
	object3->GetComponent<Transform>()->Translate({ 2,0,0 });
	object4->GetComponent<Transform>()->Translate({ 3,0,0 });
	object5->GetComponent<Transform>()->Translate({ -1,0,0 });
	object6->GetComponent<Transform>()->Translate({ -2,0,0 });
	object7->GetComponent<Transform>()->Translate({ -3,0,0 });

	object->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object2->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object3->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object4->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object5->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object6->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);
	object7->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);

	object->GetComponent<Tetromino>()->SetLevel(m_level);
	object2->GetComponent<Tetromino>()->SetLevel(m_level);
	object3->GetComponent<Tetromino>()->SetLevel(m_level);
	object4->GetComponent<Tetromino>()->SetLevel(m_level);
	object5->GetComponent<Tetromino>()->SetLevel(m_level);
	object6->GetComponent<Tetromino>()->SetLevel(m_level);
	object7->GetComponent<Tetromino>()->SetLevel(m_level);


	object->Start();
	object2->Start();
	object3->Start();
	object4->Start();
	object5->Start();
	object6->Start();
	object7->Start();

	m_blocks.push_back(object);
	m_blocks.push_back(object2);
	m_blocks.push_back(object3);
	m_blocks.push_back(object4);
	m_blocks.push_back(object5);
	m_blocks.push_back(object6);
	m_blocks.push_back(object7);

	m_nowBlocks.push_back(object);
	m_nowBlocks.push_back(object2);
	m_nowBlocks.push_back(object3);
	m_nowBlocks.push_back(object4);
	m_nowBlocks.push_back(object5);
	m_nowBlocks.push_back(object6);
	m_nowBlocks.push_back(object7);
}

void TetrisMechanism::Pit()
{
	if (m_pitBlocks.size() == 0)
	{
		for (auto& e : m_nowBlocks)
		{
			m_pitBlocks.push_back(e);
		}
		m_nowBlocks.clear();
		m_isUsingBlock = false;
	}
	else
	{
		std::vector<GameObject*> blocks;
		for (auto& e : m_nowBlocks)
		{
			blocks.push_back(e);
		}
		m_nowBlocks.clear();
		for (auto& e : m_pitBlocks)
		{
			if (!e->GetParent())
			{
				e->AddComponent<Controller>();
				e->GetComponent<Transform>()->SetPosition({ 0,17,0 });
			}
			e->AddComponent<Tetromino>();

			e->GetComponent<Tetromino>()->SetObjectManager(m_objectManager);

			e->GetComponent<Tetromino>()->SetLevel(m_level);

			e->Start();

			m_nowBlocks.push_back(e);
			m_blocks.push_back(e);
		}
		m_pitBlocks.clear();
		for (auto& e : blocks)
		{
			m_pitBlocks.push_back(e);
		}
	}
	for (auto& e : m_pitBlocks)
	{
		if (e->GetComponent<Controller>())
		{
			e->DeleteComponent<Controller>();
		}
		e->DeleteComponent<Tetromino>();
	}

	for (auto& e : m_pitBlocks)
	{
		for (auto& d : m_blocks)
		{
			if (e == d)
			{
				m_blocks.erase(remove(m_blocks.begin(), m_blocks.end(), e), m_blocks.end());
			}
		}
	}
}

int TetrisMechanism::GetUsedBlockCount(int floor)
{
	int count = 0;
	for (auto& e : m_usedBlocks)
	{
		if (e.second == floor)
		{
			count++;
		}
	}

	return count;
}

/// <summary>
/// 여기부터 잘 고쳐 삭제를 잘해줘야돼 순서대로 걸림 없이
/// </summary>
void TetrisMechanism::DeleteBlocks()
{
	for (auto& e : m_deleteBlocks)
	{
		e.first->GetComponent<Renderer>()->DeleteRenderer();
		for (auto& c : e.first->GetChildren())
		{
			if (c->GetComponent<Renderer>())
			{
				c->GetComponent<Renderer>()->DeleteRenderer();
			}
		}

		int fx = m_randomInt->GetActualInt(e.first->GetComponent<Transform>()->GetWorldPosition().x);
		int fy = m_randomInt->GetActualInt(e.first->GetComponent<Transform>()->GetWorldPosition().y);
		int fz = m_randomInt->GetActualInt(e.first->GetComponent<Transform>()->GetWorldPosition().z);

		int x = fx + 3;
		int y = -fy + 16;
		int z = -fz + 3;


		m_floor[z][x]--;

		for (int i = 16 - fy; i > fy; i--)
		{
			for (int j = 0; j < 7; j++)
			{
				m_frontWall[i][j] = m_frontWall[i - 1][j];

				m_leftWall[i][j] = m_leftWall[i - 1][j];
			}
		}

	}

	for (auto& e : m_usedBlocks)
	{
		for (auto& d : m_deleteBlocks)
		{
			if (e == d)
			{
				m_usedBlocks.erase(remove(m_usedBlocks.begin(), m_usedBlocks.end(), e), m_usedBlocks.end());
				m_objectManager->DeleteObjectFromManager(d.first);
			}

		}
	}
	m_objectManager->DestroyObjects();
	m_deleteBlocks.clear();
}

