#pragma once
#include "Object.h"
#include <vector>

class Component;

class GameObject : public Object
{
public:
	GameObject(int id);
	GameObject(std::string name, int id);
	GameObject(const GameObject& obj, int id);
	virtual ~GameObject();

	void Start();
	void FixedUpdate();
	void Update(float dTime);
	void LateUpdate(float dTime);

	void SetParent(GameObject* val)
	{
		if (val)
		{
			val->SetIsParent(true);
		}
		m_parent = val;
	}

	void SetChild(GameObject* val)
	{
		val->SetIsParent(false);
		m_children.push_back(val);
		m_isChild = true;
	}

	GameObject* GetParent()
	{
		return m_parent;
	}

	std::vector<GameObject*> GetChildren()
	{
		return m_children;
	}

	int GetID()
	{
		return m_instanceID;
	}

	void SetIsParent(bool isParent)
	{
		m_isParent = isParent;
	}

	bool GetIsParent()
	{
		return m_isParent;
	}

	bool GetHasChild()
	{
		return m_isChild;
	}

	void DeleteChild(GameObject* child)
	{
		for (auto& e : m_children)
		{
			if (e == child)
			{
				m_children.erase(remove(m_children.begin(), m_children.end(), e), m_children.end());
			}
		}
		if (m_children.size() == 0)
		{
			m_isChild = false;
		}

	}

public:
	template<typename T>
	T* AddComponent();

	template <typename T, typename First, typename... Rest>
	void AddComponent();

	template<typename T>
	T* GetComponent();

	template<typename T>
	void DeleteComponent();

	void SetActive(bool active)
	{
		m_active = active;
	}

	std::vector<Component*> GetComponents()
	{
		return m_components;
	}

private:
	bool m_active;
	bool m_isChild;
	bool m_isParent;
	std::vector<Component*> m_components;
	std::vector<GameObject*> m_children;
	GameObject* m_parent;

};

template<typename T>
T* GameObject::AddComponent()
{
	if (std::is_base_of_v<Component, T> == true)
	{
		T* newComponent = new T;
		newComponent->SetOwner(this);
		m_components.push_back(newComponent);
		return newComponent;
	}
	else
	{
		return nullptr;
	}
}

template <typename T, typename First, typename... Rest>
void GameObject::AddComponent()
{
	AddComponent<T>();
	AddComponent<First, Rest...>();
}

template<typename T>
T* GameObject::GetComponent()
{
	for (auto& e : m_components)
	{
		T* component = dynamic_cast<T*>(e);

		if (component)
		{
			return component;
		}
	}

	return nullptr;
}

template<typename T>
void GameObject::DeleteComponent()
{
	for (auto& e : m_components)
	{
		T* component = dynamic_cast<T*>(e);

		if (component)
		{
			m_components.erase(remove(m_components.begin(), m_components.end(), component), m_components.end());
		}
	}

}

