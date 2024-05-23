#pragma once
#include "IScene.h"


class MenuScene : public IScene
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

private:
	bool m_isPressStart = false;
	bool m_showSelect = false;
	int m_selectedLevel = 0;
	int m_arrowPos = 0;
};

