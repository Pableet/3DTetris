#pragma once
#include "MonoBehaviour.h"

class InputManager;
class RandomNumber;


/// <summary>
///  �� ������ ��Ʈ�ѷ�
/// </summary>
class Controller : public MonoBehaviour
{
public:
	virtual ~Controller();
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;

	// ���� �����ߴ��� ������ �Ѱܹ�������

	bool GetIsSpin()
	{
		if (m_spin == Spin::None)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

private:
	// �̰� ���� ������ ���� �ʿ� ���
	enum class Spin
	{
		QSpin,
		WSpin,
		ESpin,
		ASpin,
		SSpin,
		DSpin,
		None,
	};

	InputManager* m_inputManager = nullptr;
	RandomNumber* m_randomInt = nullptr;

	float m_passingTime = 0.f;
	float m_spinTime = 0.f;
	int m_spinCount = 0;
	Spin m_spin = Spin::None;

	int m_isUpEnd = 0;
	int m_isDownEnd = 0;
	int m_isLeftEnd = 0;
	int m_isRightEnd = 0;
	int m_onFloorCount = 0;
};

