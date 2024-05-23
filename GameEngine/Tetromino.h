#pragma once
#include "MonoBehaviour.h"

class ObjectManager;
class InputManager;
class RandomNumber;


/// <summary>
/// 테트리스 블럭의 기본 메커니즘
/// </summary>
class Tetromino : public MonoBehaviour
{
public:
	virtual ~Tetromino();
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;

	void SetIsOnFloor(bool isOnFloor);
	
	bool GetIsOnFloor()
	{
		return m_isOnFloor;
	}

	bool GetDisabled()
	{
		return m_isDisabled;
	}

	void SetObjectManager(ObjectManager* objectManager)
	{
		m_objectManager = objectManager;
	}

	void SetBlockHeight(int height)
	{
		m_blockHeight = height;
	}

	int GetBlockHeight()
	{
		return m_blockHeight;
	}

	int GetNowHeight()
	{
		return m_nowHeight;
	}

	void SetStopTime(float stopTime)
	{
		m_stopPassingTime = stopTime;
	}

	bool GetLeftEnd()
	{
		return m_isLeftEnd;
	}
	bool GetRightEnd()
	{
		return m_isRightEnd;
	}
	bool GetUpEnd()
	{
		return m_isUpEnd;
	}
	bool GetDownEnd()
	{
		return m_isDownEnd;
	}
	bool GetUnderEnd()
	{
		return m_isUnderEnd;
	}

	void SetOnLeft(bool isExist)
	{
		m_onLeft = isExist;
	}
	void SetOnRight(bool isExist)
	{
		m_onRight = isExist;
	}
	void SetOnUp(bool isExist)
	{
		m_onUp = isExist;
	}
	void SetOnDown(bool isExist)
	{
		m_onDown = isExist;
	}

	void ResetCount()
	{
		m_isLeftEnd = 0;
		m_isRightEnd = 0;
		m_isUpEnd = 0;
		m_isDownEnd = 0;
		m_isUnderEnd = 0;
	}

	void UpdateColor();

	void SetLevel(int level)
	{
		m_level = level;
	}

private:
	float m_passingTime = 0.f;
	float m_stopTime = 0.f;
	float m_stopPassingTime = 0.f;

	bool m_isDisabled = false;
	bool m_isOnFloor = false;

	float m_fallingSpeed = 0.f;

	ObjectManager* m_objectManager = nullptr;
	RandomNumber* m_randomInt = nullptr;


	float m_blue[4] = { 0.0f,0.0f,1.0f,1.0f };
	float m_green[4] = { 0.0f,1.0f,0.0f,1.0f };
	float m_lightblue[4] = { 0.0f,1.0f,1.0f,1.0f };
	float m_red[4] = { 1.0f,0.0f,0.0f,1.0f };
	float m_purple[4] = { 1.0f,0.0f,1.0f,1.0f };
	float m_orange[4] = { 1.0f,0.5f,0.0f,1.0f };
	float m_white[4] = { 1.0f,1.0f,1.0f,1.0f };


	int m_nowHeight = 0;
	int m_blockHeight = 0;
	int m_lastBlockHeight = 0;

	GameObject* m_filledObject = nullptr;

	int m_isLeftEnd = 0;
	int m_isRightEnd = 0;
	int m_isUpEnd = 0;
	int m_isDownEnd = 0;
	int m_isUnderEnd = 0;

	bool m_onLeft = false;
	bool m_onRight = false;
	bool m_onUp = false;
	bool m_onDown = false;

	int m_level = 1;

/// <summary>
/// 이건 쓸 날이 올까 (아마 안 올거임)
/// </summary>
/*
private:
	int R_2x2[3][3]
		= { 1, 1, 9,
			1, 8, 9,
			9, 9, 9 };

	int S_3x2[3][3]
		= { 1, 1, 9,
			9, 8, 1,
			9, 9, 9 };

	int L_3x2[3][3]
		= { 9, 9, 9,
			1, 8, 1,
			1, 9, 9 };

	int T_3x2[3][3]
		= { 9, 9, 9,
			1, 8, 1,
			9, 1, 9 };

	int O_1x1[3][3]
		= { 9, 9, 9,
			9, 8, 9,
			9, 9, 9 };

	int I_3x1[3][3]
		= { 9, 9, 9,
			1, 8, 1,
			9, 9, 9 };

	int I_2x1[3][3]
		= { 9, 9, 9,
			1, 8, 9,
			9, 9, 9 };

	int V_2x2[3][3]
		= { 9, 1, 9,
			1, 8, 9,
			9, 9, 9 };*/



};

