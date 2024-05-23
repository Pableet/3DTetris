#pragma once
#include "Object.h"
#include "GameObject.h"
#include "../Graphics/I3DRenderer.h"

class Component : public Object
{
public:
	Component();
	virtual ~Component();

	virtual void Start() abstract;
	virtual void FixedUpdate() abstract;
	virtual void Update(float dTime) abstract;
	virtual void LateUpdate(float dTime) abstract;

public:
	void SetOwner(GameObject* owner)
	{
		m_owner = owner;
	}
	GameObject* GetOwner()
	{
		return m_owner;
	}

protected:
	GameObject* m_owner = nullptr;
	static I3DRenderer* m_renderer;

private:
	friend class GameEngine;
	static void SetRenderer(I3DRenderer* _Value) { if (m_renderer == nullptr) m_renderer = _Value; };
};

