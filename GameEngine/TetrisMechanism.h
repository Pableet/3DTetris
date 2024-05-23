#pragma once
#include "MonoBehaviour.h"

class ObjectManager;
class RandomNumber;


/// <summary>
/// 테트리스 게임의 메커니즘
/// </summary>
class TetrisMechanism : public MonoBehaviour
{
public:
	virtual ~TetrisMechanism();
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;

	void SetObjectManager(ObjectManager* objectManager)
	{
		m_objectManager = objectManager;
	}

	void Create_R_2x2();
	void Create_S_3x2();
	void Create_L_3x2();
	void Create_T_3x2();
	void Create_O_1x1();
	void Create_I_3x1();
	void Create_I_2x1();
	void Create_V_2x2();
	void Create_I_7x1();

	void Pit();

	int m_floor[7][7] =
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
	};
	int m_frontWall[16][7] =
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
	};
	int m_leftWall[16][7] = 
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
	};

	int GetUsedBlockCount(int floor);
	void DeleteBlocks();

	int GetScore()
	{
		return m_score;
	}

	int GetLevel()
	{
		return m_level;
	}

	void SetLevel(int level)
	{
		m_level = level;
	}

	bool GetIsGameEnd()
	{
		return m_isGameEnded;
	}

private:
	bool m_isUsingBlock = false;
	ObjectManager* m_objectManager = nullptr;
	std::vector<GameObject*> m_blocks;
	RandomNumber* m_randomInt = nullptr;
	std::vector<GameObject*> m_nowBlocks;
	std::vector<GameObject*> m_pitBlocks;

	std::vector<std::pair<GameObject*, int>> m_deleteBlocks;
	

	// int는 층수
	std::vector<std::pair<GameObject*, int>> m_usedBlocks;

	bool m_isGameEnded = false;
	bool m_isExchanged = false;

	int m_score = 0;
	int m_level = 1;
	int m_deleted = 0;
};

