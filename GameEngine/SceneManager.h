#pragma once
#include "IScene.h"
#include <vector>


class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Awake();
	void Start();
	void FixedUpdate();
	void Update(float dTime);
	void LateUpdate(float dTime);
	void Render();
	void Release();

	void AddScene(IScene* scene);
	void SetCurrentScene(int index);
	void SetObjectManager(ObjectManager* objectManager)
	{
		m_objectManager = objectManager;
	}
private:
	std::vector<IScene*> m_scenes;
	IScene* m_currentScene;
	ObjectManager* m_objectManager;

};

