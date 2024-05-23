#include "Tetromino.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "Renderer.h"
#include "RandomNumber.h"
#include "Controller.h"


Tetromino::~Tetromino()
{

}

void Tetromino::Start()
{
	m_randomInt = new RandomNumber();
	// 떨어지는 속도 조절
	if (m_level == 1)
	{
		m_fallingSpeed = 2.5f;
	}
	if (m_level == 2)
	{
		m_fallingSpeed = 2.f;
	}
	if (m_level == 3)
	{
		m_fallingSpeed = 1.5f;
	}
	if (m_level == 4)
	{
		m_fallingSpeed = 1.f;
	}
	if (m_level == 5)
	{
		m_fallingSpeed = 0.8f;
	}
	if (m_level == 6)
	{
		m_fallingSpeed = 0.5f;
	}

	m_stopTime = 1.f;
}

void Tetromino::FixedUpdate()
{

}

void Tetromino::Update(float dTime)
{
	// 비활성화 되지 않은 동안
	if (!m_isDisabled)
	{
		// 회전시 블럭이 빠져나가면 돌아오게
		// 상단이 빠져나가면
		if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().z) > 3)
		{
			if (m_owner->GetParent())
			{
				m_owner->GetParent()->GetComponent<Transform>()->TranslateZ(-1);
			}
			else
			{
				m_owner->GetComponent<Transform>()->TranslateZ(-1);
			}
		}
		// 하단이 빠져나가면
		if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().z) < -3)
		{
			if (m_owner->GetParent())
			{
				m_owner->GetParent()->GetComponent<Transform>()->TranslateZ(1);
			}
			else
			{
				m_owner->GetComponent<Transform>()->TranslateZ(1);
			}
		}
		// 좌측이 빠져나가면
		if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().x) < -3)
		{
			if (m_owner->GetParent())
			{
				m_owner->GetParent()->GetComponent<Transform>()->TranslateX(1);
			}
			else
			{
				m_owner->GetComponent<Transform>()->TranslateX(1);
			}
		}
		// 우측이 빠져나가면
		if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().x) > 3)
		{
			if (m_owner->GetParent())
			{
				m_owner->GetParent()->GetComponent<Transform>()->TranslateX(-1);
			}
			else
			{
				m_owner->GetComponent<Transform>()->TranslateX(-1);
			}
		}



		// 상하좌우로 못 빠져나가게
		if (m_owner->GetComponent<Controller>())
		{
			if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().z) > 3)
			{
				m_owner->GetComponent<Transform>()->TranslateZ(-1);
			}
			if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().z) < -3)
			{
				m_owner->GetComponent<Transform>()->TranslateZ(1);
			}
			if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().x) < -3)
			{
				m_owner->GetComponent<Transform>()->TranslateX(1);
			}
			if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().x) > 3)
			{
				m_owner->GetComponent<Transform>()->TranslateX(-1);
			}
			if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().y) < 1)
			{
				m_owner->GetComponent<Transform>()->TranslateY(1);
			}
		}


		// 상단 최대
		if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().z) == 3)
		{
			m_isUpEnd++;
		}
		else
		{
			m_isUpEnd;
		}

		// 하단 최대
		if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().z) == -3)
		{
			m_isDownEnd++;
		}
		else
		{
			m_isDownEnd;
		}


		// 좌측 최대
		if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().x) == -3)
		{
			m_isLeftEnd++;
		}
		else
		{
			m_isLeftEnd;
		}


		// 우측 최대
		if (m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().x) == 3)
		{
			m_isRightEnd++;
		}
		else
		{
			m_isRightEnd;
		}


		// 바닥 최대
		if (m_isOnFloor)
		{
			m_isUnderEnd++;
		}
		else
		{
			m_isUnderEnd;
		}
	}

}

void Tetromino::LateUpdate(float dTime)
{
	int fallCount = 0;
	// 한칸씩 내려가게
	if (!m_isDisabled && !m_isOnFloor)
	{
		if (!m_owner->GetParent())
		{
			m_passingTime += dTime;
			if (m_passingTime > m_fallingSpeed)
			{
				if (!m_isOnFloor)
				{
					fallCount++;
				}
				for (auto& e : m_owner->GetChildren())
				{
					if (!e->GetComponent<Tetromino>()->GetIsOnFloor())
					{
						fallCount++;
					}
				}
				if (fallCount == m_owner->GetChildren().size() + 1)
				{
 					m_owner->GetComponent<Transform>()->TranslateY(-1);
				}
				m_passingTime = 0.f;
			}
		}
	}


	if (m_onLeft)
	{
		m_isLeftEnd++;
		m_onLeft = false;
	}
	if (m_onRight)
	{
		m_isRightEnd++;
		m_onRight = false;
	}
	if (m_onUp)
	{
		m_isUpEnd++;
		m_onUp = false;
	}
	if (m_onDown)
	{
		m_isDownEnd++;
		m_onDown = false;
	}



	if (!m_isDisabled && m_isOnFloor)
	{
		if (!m_owner->GetParent())
		{
			for (auto& e : m_owner->GetChildren())
			{
				if (e->GetComponent<Tetromino>())
				{
					e->GetComponent<Tetromino>()->SetIsOnFloor(true);
				}
			}
		}
		else
		{
			m_owner->GetParent()->GetComponent<Tetromino>()->SetIsOnFloor(true);
			for (auto& e : m_owner->GetParent()->GetChildren())
			{
				if (e->GetComponent<Tetromino>())
				{
					e->GetComponent<Tetromino>()->SetIsOnFloor(true);
				}
			}
		}

		if (m_owner->GetComponent<Controller>())
		{
			if (!m_owner->GetComponent<Controller>()->GetIsSpin())
			{
				m_stopPassingTime += dTime;
			}
		}
// 		else if (!m_owner->GetComponent<Controller>())
// 		{
// 			if (m_owner->GetParent()->GetComponent<Controller>())
// 			{
// 				if (!m_owner->GetParent()->GetComponent<Controller>()->GetIsSpin())
// 				{
// 					m_stopPassingTime += dTime;
// 				}
// 			}
// 		}

		if (m_stopPassingTime >= m_stopTime)
		{
			if (m_owner->GetParent())
			{
				m_owner->GetParent()->GetComponent<Tetromino>()->SetStopTime(m_stopTime);
				for (auto& e : m_owner->GetParent()->GetChildren())
				{
					if (e->GetComponent<Tetromino>())
					{
						e->GetComponent<Tetromino>()->SetStopTime(m_stopTime);
						e->GetComponent<Tetromino>()->SetIsOnFloor(true);
					}
				}
			}
			else
			{
				for (auto& e : m_owner->GetChildren())
				{
					if (e->GetComponent<Tetromino>())
					{
						e->GetComponent<Tetromino>()->SetStopTime(m_stopTime);
						e->GetComponent<Tetromino>()->SetIsOnFloor(true);
					}
				}
			}
		}

		if (!m_isDisabled && !m_isOnFloor && m_stopPassingTime != 0.f)
		{
			m_stopPassingTime = 0.f;
			if (m_owner->GetParent())
			{
				m_owner->GetParent()->GetComponent<Tetromino>()->SetStopTime(0.f);
				for (auto& e : m_owner->GetParent()->GetChildren())
				{
					if (e->GetComponent<Tetromino>())
					{
						e->GetComponent<Tetromino>()->SetStopTime(0.f);
						e->GetComponent<Tetromino>()->SetIsOnFloor(false);
					}
				}
			}
			else
			{
				for (auto& e : m_owner->GetChildren())
				{
					if (e->GetComponent<Tetromino>())
					{
						e->GetComponent<Tetromino>()->SetStopTime(0.f);
						e->GetComponent<Tetromino>()->SetIsOnFloor(false);
					}
				}
			}
		}

		if (!m_isDisabled && m_isOnFloor && m_stopPassingTime >= m_stopTime)
		{
			m_owner->GetComponent<Renderer>()->SetBoxColor(0.f, 0.f, 0.f, 1.f);


			// 안쪽에 블럭을 하나 더 만들어서 채우기
			m_filledObject = m_objectManager->CreateUnnamedObject();
			m_filledObject->AddComponent<Renderer>()->AddBox();

			// 색을 7개 돌려쓸려고 나머지 값으로 높이 비교하기

			m_filledObject->GetComponent<Renderer>()->SetRS(1);
			m_filledObject->GetComponent<Renderer>()->SetRectSize(0.47f);
			m_objectManager->SetParentByGameObject(m_filledObject, m_owner);
			
			// 가만히 있게 비활성화 시켜줌
			m_isDisabled = true;

			// 이건 이 부분을 한번만 돌려주려고 만듦
			m_isOnFloor = false;

			//m_objectManager->SetParentByGameObject(m_owner, nullptr);


			// 바닥에 가만히 있게 컨트롤러 제거
			if (m_owner->GetComponent<Controller>())
			{
				m_owner->DeleteComponent<Controller>();
			}
		}


		UpdateColor();

	}

}

void Tetromino::SetIsOnFloor(bool isOnFloor)
{
	m_isOnFloor = isOnFloor;
}

void Tetromino::UpdateColor()
{
	if (m_filledObject)
	{
		// 현재 높이를 저장
		m_nowHeight = m_randomInt->GetActualInt(m_owner->GetComponent<Transform>()->GetWorldPosition().y);

		int nowHeight = m_nowHeight % 7;
		// 높이에 따라 채워지는 색이 다름
		switch (nowHeight)
		{
		case 1:
			m_filledObject->GetComponent<Renderer>()->SetBoxColor(m_blue);
			break;
		case 2:
			m_filledObject->GetComponent<Renderer>()->SetBoxColor(m_green);
			break;
		case 3:
			m_filledObject->GetComponent<Renderer>()->SetBoxColor(m_lightblue);
			break;
		case 4:
			m_filledObject->GetComponent<Renderer>()->SetBoxColor(m_red);
			break;
		case 5:
			m_filledObject->GetComponent<Renderer>()->SetBoxColor(m_purple);
			break;
		case 6:
			m_filledObject->GetComponent<Renderer>()->SetBoxColor(m_orange);
			break;
		case 0:
			m_filledObject->GetComponent<Renderer>()->SetBoxColor(m_white);
			break;
		}
	}
}

