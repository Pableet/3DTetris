#include "Controller.h"
#include "InputManager.h"
#include "Transform.h"
#include "Tetromino.h"
#include "RandomNumber.h"

Controller::~Controller()
{

}

void Controller::Start()
{
	m_inputManager = InputManager::GetInstance();
	m_randomInt = new RandomNumber();
}

void Controller::FixedUpdate()
{

}

void Controller::Update(float dTime)
{
	m_isUpEnd = 0;
	m_isDownEnd = 0;
	m_isLeftEnd = 0;
	m_isRightEnd = 0;
	m_onFloorCount = 0;

	m_isUpEnd += m_owner->GetComponent<Tetromino>()->GetUpEnd();
	m_isDownEnd += m_owner->GetComponent<Tetromino>()->GetDownEnd();
	m_isLeftEnd += m_owner->GetComponent<Tetromino>()->GetLeftEnd();
	m_isRightEnd += m_owner->GetComponent<Tetromino>()->GetRightEnd();
	m_onFloorCount += m_owner->GetComponent<Tetromino>()->GetUnderEnd();
	m_owner->GetComponent<Tetromino>()->ResetCount();
	for (auto& e : m_owner->GetChildren())
	{
		m_isUpEnd += e->GetComponent<Tetromino>()->GetUpEnd();
		m_isDownEnd += e->GetComponent<Tetromino>()->GetDownEnd();
		m_isLeftEnd += e->GetComponent<Tetromino>()->GetLeftEnd();
		m_isRightEnd += e->GetComponent<Tetromino>()->GetRightEnd();
		m_onFloorCount += e->GetComponent<Tetromino>()->GetUnderEnd();
		e->GetComponent<Tetromino>()->ResetCount();
	}

	if (m_inputManager->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Up) && m_isUpEnd == 0)
	{
		m_owner->GetComponent<Transform>()->TranslateZ(1);
	}

	if (m_inputManager->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Down) && m_isDownEnd == 0)
	{
		m_owner->GetComponent<Transform>()->TranslateZ(-1);
	}

	if (m_inputManager->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Left) && m_isLeftEnd == 0)
	{
		m_owner->GetComponent<Transform>()->TranslateX(-1);
	}

	if (m_inputManager->m_Keyboard.IsKeydown(DirectX::Keyboard::Keys::Right) && m_isRightEnd == 0)
	{
		m_owner->GetComponent<Transform>()->TranslateX(1);
	}

	if (m_inputManager->m_Keyboard.IsKeydown('Q') && m_spin == Spin::None && m_onFloorCount == 0)
	{
		m_spin = Spin::QSpin;
	}

	if (m_inputManager->m_Keyboard.IsKeydown('W') && m_spin == Spin::None && m_onFloorCount == 0)
	{
		m_spin = Spin::WSpin;
	}

	if (m_inputManager->m_Keyboard.IsKeydown('E') && m_spin == Spin::None && m_onFloorCount == 0)
	{
		m_spin = Spin::ESpin;
	}

	if (m_inputManager->m_Keyboard.IsKeydown('A') && m_spin == Spin::None && m_onFloorCount == 0)
	{
		m_spin = Spin::ASpin;
	}

	if (m_inputManager->m_Keyboard.IsKeydown('S') && m_spin == Spin::None && m_onFloorCount == 0)
	{
		m_spin = Spin::SSpin;
	}

	if (m_inputManager->m_Keyboard.IsKeydown('D') && m_spin == Spin::None && m_onFloorCount == 0)
	{
		m_spin = Spin::DSpin;
	}

	if (m_inputManager->m_Keyboard.IsKeyHold(DirectX::Keyboard::Keys::Space) && m_onFloorCount == 0)
	{
		m_passingTime += dTime;
		if (m_passingTime > 0.1f)
		{
			m_owner->GetComponent<Transform>()->TranslateY(-1);
			m_passingTime = 0.f;
		}
	}
}

void Controller::LateUpdate(float dTime)
{
	switch (m_spin)
	{
	case Spin::QSpin:
	{
		m_spinTime += dTime;
		if (m_spinTime > 0.04f)
		{

			m_owner->GetComponent<Transform>()->Yaw(-18);
			m_spinTime = 0.f;
			m_spinCount++;
		}

		if (m_spinCount == 5)
		{
			m_spinCount = 0;
			m_spin = Spin::None;
		}
	}
	break;

	case Spin::WSpin:
	{
		m_spinTime += dTime;
		if (m_spinTime > 0.04f)
		{
			m_owner->GetComponent<Transform>()->Pitch(18);
			m_spinTime = 0.f;
			m_spinCount++;
		}

		if (m_spinCount == 5)
		{
			m_spinCount = 0;
			m_spin = Spin::None;
		}
	}
	break;

	case Spin::ESpin:
	{
		m_spinTime += dTime;
		if (m_spinTime > 0.04f)
		{
			m_owner->GetComponent<Transform>()->Yaw(18);
			m_spinTime = 0.f;
			m_spinCount++;
		}

		if (m_spinCount == 5)
		{
			m_spinCount = 0;
			m_spin = Spin::None;
		}
	}
	break;

	case Spin::ASpin:
	{
		m_spinTime += dTime;
		if (m_spinTime > 0.04f)
		{
			m_owner->GetComponent<Transform>()->Roll(18);
			m_spinTime = 0.f;
			m_spinCount++;
		}

		if (m_spinCount == 5)
		{
			m_spinCount = 0;
			m_spin = Spin::None;
		}
	}
	break;

	case Spin::SSpin:
	{
		m_spinTime += dTime;
		if (m_spinTime > 0.04f)
		{
			m_owner->GetComponent<Transform>()->Pitch(-18);
			m_spinTime = 0.f;
			m_spinCount++;
		}

		if (m_spinCount == 5)
		{
			m_spinCount = 0;
			m_spin = Spin::None;
		}
	}
	break;

	case Spin::DSpin:
	{
		m_spinTime += dTime;
		if (m_spinTime > 0.04f)
		{
			m_owner->GetComponent<Transform>()->Roll(-18);
			m_spinTime = 0.f;
			m_spinCount++;
		}

		if (m_spinCount == 5)
		{
			m_spinCount = 0;
			m_spin = Spin::None;
		}
	}
	break;

	default:
		break;
	}
}
