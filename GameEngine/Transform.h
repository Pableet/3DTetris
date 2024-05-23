#pragma once
#include "Component.h"
#include "I3DRenderer.h"
#include <vector>
#include "SimpleMath.h"

class Transform : public Component
{
public:
	Transform();
	~Transform();

	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;

	void UpdateMatrix();
	void SetPosition(DirectX::XMFLOAT3 position);
	void Translate(DirectX::XMFLOAT3 position);
	void TranslateX(float x);
	void TranslateY(float y);
	void TranslateZ(float z);
	void Rotate(DirectX::XMFLOAT3 rotation);
	void Yaw(float angle);
	void Pitch(float angle);
	void Roll(float angle);

	DirectX::XMFLOAT3 GetLocalRotation()
	{
		return m_localRotation;
	}

	DirectX::XMFLOAT4X4 GetWorld()
	{
		return m_world;
	}
	

	void SetParent(Transform* parent)
	{
		m_parent = parent;
		if (!parent)
		{
			m_local = m_world;
			m_localPosition = m_worldPosition;
			UpdateMatrix();
		}
	}

	Transform* GetParent()
	{
		return m_parent;
	}

	void AddChild(Transform* child)
	{
		m_children.push_back(child);
	}

	DirectX::XMFLOAT3 GetLocalPosition()
	{
		return m_localPosition;
	}

	DirectX::XMFLOAT3 GetWorldPosition()
	{
		return m_worldPosition;
	}

	DirectX::XMFLOAT3 GetLocalAngle()
	{
		return m_localAngle;
	}

private:
	DirectX::XMFLOAT3 m_localPosition;
	DirectX::XMFLOAT3 m_worldPosition;
	DirectX::XMFLOAT3 m_localRotation;
	DirectX::XMFLOAT3 m_localAngle;
	DirectX::XMFLOAT3 m_scale;
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_local;
	Transform* m_parent;
	std::vector<Transform*> m_children;

	bool m_isParent;
	bool m_isChild;

};

