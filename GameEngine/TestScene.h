#pragma once
#include "IScene.h"


class TestScene : public IScene
{
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void EditScene() override;
};

