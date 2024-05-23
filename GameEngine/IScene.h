#pragma once
#include "ObjectManager.h"
//#include "SceneManager.h"

class SceneManager;

class IScene
{
public:
	virtual void Awake() abstract;
	virtual void Start() abstract;
	virtual void FixedUpdate() abstract;
	virtual void Update(float dTime) abstract;
	virtual void LateUpdate(float dTime) abstract;
	virtual void Render() abstract;
	virtual void Release() abstract;

	virtual void EditScene() abstract;

	void SetObjectManager(ObjectManager* objectManager)
	{
		m_objectManager = objectManager;
	}

	void SetSceneManager(SceneManager* sceneManager)
	{
		m_sceneManager = sceneManager;
	}

protected:
	float m_dTime = 0.f;
	ObjectManager* m_objectManager = nullptr;
	std::vector<GameObject*> m_objects;
	SceneManager* m_sceneManager = nullptr;
};

