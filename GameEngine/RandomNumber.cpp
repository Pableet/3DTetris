#include "RandomNumber.h"
#include <random>

RandomNumber::RandomNumber()
{

}

RandomNumber::~RandomNumber()
{

}

void RandomNumber::Start()
{

}

void RandomNumber::FixedUpdate()
{

}

void RandomNumber::Update(float dTime)
{

}

void RandomNumber::LateUpdate(float dTime)
{

}

int RandomNumber::GetRandomInt(int _min, int _max)
{
	// �õ尪 ����
	std::random_device rd;
	// �õ尪���� ���� ���� ���� �ʱ�ȭ
	std::mt19937 gen(rd());
	// �յ� ���� ����
	std::uniform_int_distribution<int> dis(_min, _max);
	// ���� ��ȯ
	return dis(gen);
}

int RandomNumber::GetActualInt(float val)
{
	float a = 0.f;
	int b = 0;
	float c = 0.f;
	if (val > 0.f)
	{
		a = val;
		b = static_cast<int>(val);
		c = a - static_cast<float>(b);

		if (c >= 0.5f)
		{
			return b + 1;
		}
		else
		{
			return b;
		}
	}

	else if (val < 0.f)
	{
		a = val;
		b = static_cast<int>(val);
		c = a - static_cast<float>(b);
		if (c <= -0.5f)
		{
			return b - 1;
		}
		else
		{
			return b;
		}

	}

	else
	{
		return 0;
	}

}
