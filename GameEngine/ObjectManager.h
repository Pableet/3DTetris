#pragma once
#include "GameObject.h"


class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	GameObject* CreateObject(std::string name);
	GameObject* CreateUnnamedObject();
	GameObject* CopyObject(GameObject* object);


	void DeleteObjectFromManager(std::string name);
	void DeleteObjectFromManager(GameObject* object);
	GameObject* FindObjectFromName(std::string name);

	void SetParentByGameObject(GameObject* child, GameObject* parent);

	void DestroyObjects();

private:
	std::vector<GameObject*> m_objects;
	std::vector<GameObject*> m_deleteQueue;
	int m_id = 0;

};

