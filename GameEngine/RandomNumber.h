#pragma once
#include "MonoBehaviour.h"

class RandomNumber : public MonoBehaviour
{
public:
	RandomNumber();
	~RandomNumber();

	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;

	// 랜덤 정수를 받는 함수
	int GetRandomInt(int _min, int _max);

	// 값이 이상한 실수형 값을 정수로 바꿔주려고 만듦
	int GetActualInt(float val);

};

