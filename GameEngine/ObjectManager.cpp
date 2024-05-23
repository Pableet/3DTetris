#include "ObjectManager.h"
#include "Transform.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	m_objects.clear();
}

GameObject* ObjectManager::CreateObject(std::string name)
{
	GameObject* object = new GameObject(name, m_id);
	object->AddComponent<Transform>();
	m_objects.push_back(object);
	m_id++;
	return object;
}

GameObject* ObjectManager::CreateUnnamedObject()
{
	GameObject* object = new GameObject(m_id);
	object->AddComponent<Transform>();
	m_objects.push_back(object);
	m_id++;
	return object;
}

GameObject* ObjectManager::CopyObject(GameObject* object)
{
	GameObject* copyObject = new GameObject(*object, m_id);
	object->AddComponent<Transform>();
	m_objects.push_back(copyObject);
	m_id++;
	return copyObject;
}

void ObjectManager::DeleteObjectFromManager(std::string name)
{
	for (auto& e : m_objects)
	{
		if (name == e->GetName())
		{
			//m_objects.erase(m_objects.begin() + i);
			m_objects.erase(remove(m_objects.begin(), m_objects.end(), e), m_objects.end());
			delete e;
			//m_id--;
		}
	}
}

void ObjectManager::DeleteObjectFromManager(GameObject* object)
{
	if (object != nullptr)
	{
		for (auto& e : m_objects)
		{
			if (object->GetHasChild())
			{
				for (auto& d : object->GetChildren())
				{
					m_objects.erase(remove(m_objects.begin(), m_objects.end(), d), m_objects.end());
					SetParentByGameObject(d, nullptr);
					object->DeleteChild(d);
					if (d->GetID() >= 0)
					{
						m_deleteQueue.push_back(d);
					}
					//m_id--;
				}
			}
			if (e == object)
			{
				e->DeleteComponent<Transform>();
				m_objects.erase(remove(m_objects.begin(), m_objects.end(), e), m_objects.end());
				if (e->GetID() >= 0)
				{
					m_deleteQueue.push_back(e);
				}
				//m_id--;
			}
		}
	}
}

GameObject* ObjectManager::FindObjectFromName(std::string name)
{
	for (auto& e : m_objects)
	{
		if (name == e->GetName())
		{
			return e;
		}
	}
	return nullptr;
}

void ObjectManager::SetParentByGameObject(GameObject* child, GameObject* parent)
{
	if (parent == nullptr)
	{
		GameObject* p = child->GetParent();
		if (child->GetParent())
		{
			child->GetParent()->DeleteChild(child);
		}
		child->SetParent(nullptr);
		child->GetComponent<Transform>()->SetParent(nullptr);
		return;
	}

	child->SetParent(parent);
	parent->SetChild(child);

	child->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
	parent->GetComponent<Transform>()->AddChild(child->GetComponent<Transform>());

	parent->GetComponent<Transform>()->UpdateMatrix();
}

void ObjectManager::DestroyObjects()
{
	if (m_deleteQueue.size() > 0)
	{
		for (auto& e : m_deleteQueue)
		{
			e = nullptr;

			delete e;
		}
		m_deleteQueue.clear();
	}
}

