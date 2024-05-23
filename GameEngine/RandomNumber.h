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

	// ���� ������ �޴� �Լ�
	int GetRandomInt(int _min, int _max);

	// ���� �̻��� �Ǽ��� ���� ������ �ٲ��ַ��� ����
	int GetActualInt(float val);

};

