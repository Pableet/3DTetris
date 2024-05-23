#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject(int id)
	: m_active(true), m_parent(nullptr), m_isChild(false), m_isParent(true)
{
	m_name = "";
	m_instanceID = id;
}

GameObject::GameObject(std::string name, int id)
	: m_active(true), m_parent(nullptr), m_isChild(false), m_isParent(true)
{
	m_name = name;
	m_instanceID = id;
}

GameObject::GameObject(const GameObject& obj, int id)
	: m_active(true), m_parent(obj.m_parent), m_isChild(false), m_isParent(true)
{
	m_name = obj.m_name;
	m_instanceID = id;
}

GameObject::~GameObject()
{
	if (m_components.size() != 0)
	{
		for (auto& e : m_components)
		{
			delete e;
		}
	}
	m_components.clear();
}

void GameObject::Start()
{
	for (auto& e : m_components)
	{
		e->Start();
	}
}

void GameObject::FixedUpdate()
{
	for (auto& e : m_components)
	{
		e->FixedUpdate();
	}
}

void GameObject::Update(float dTime)
{
	for (auto& e : m_components)
	{
		e->Update(dTime);
	}
}

void GameObject::LateUpdate(float dTime)
{
	for (auto& e : m_components)
	{
		e->LateUpdate(dTime);
	}
}


