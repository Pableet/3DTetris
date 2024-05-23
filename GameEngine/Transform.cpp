#include "Transform.h"

Transform::Transform()
	: m_parent(nullptr), m_localPosition(0.f, 0.f, 0.f), m_worldPosition(0.f, 0.f, 0.f)
	, m_localRotation(0.f, 0.f, 0.f), m_scale(1.f, 1.f, 1.f), m_localAngle(0.f,0.f,0.f)
	, m_isChild(false), m_isParent(true)
	, m_local(), m_world()
{
	DirectX::XMStoreFloat4x4(&m_world, DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_local, DirectX::XMMatrixIdentity());
}

Transform::~Transform()
{
	for (auto& e : m_children)
	{
		e->SetParent(nullptr);
	}
	m_children.clear();
	m_parent = nullptr;
	delete m_parent;
}

void Transform::Start()
{

}

void Transform::FixedUpdate()
{

}

void Transform::Update(float dTime)
{


}

void Transform::LateUpdate(float dTime)
{
	UpdateMatrix();
	for (Transform* child : m_children)
	{
		child->UpdateMatrix();
	}
	// 	m_localPosition.x = m_local._41;
	// 	m_localPosition.y = m_local._42;
	// 	m_localPosition.z = m_local._43;

	
}

void Transform::UpdateMatrix()
{
	// ¸ÁÇÒ DirectXMath¶§¹®¿¡ ¾îÁö·¯¿ü´Ù
	m_local = DirectX::SimpleMath::Matrix::CreateScale({ 1.f, 1.f, 1.f }) * DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_localRotation) * DirectX::SimpleMath::Matrix::CreateTranslation(m_localPosition);


	if (m_parent)
	{
		DirectX::SimpleMath::Matrix world = m_parent->GetWorld();
		DirectX::SimpleMath::Matrix test = m_local * world;
		DirectX::XMStoreFloat4x4(&m_world, DirectX::XMLoadFloat4x4(&m_local) * DirectX::XMLoadFloat4x4(&world));
	}
	else
	{
		m_world = m_local;
	}
	if (m_owner->GetName() == "")
	{
		m_renderer->TransformObjectFromID(m_owner->GetID(), DirectX::XMLoadFloat4x4(&m_world));
	}
	else
	{
		m_renderer->TransformObjectFromName(m_owner->GetName(), DirectX::XMLoadFloat4x4(&m_world));
	}
	m_worldPosition.x = m_world._41;
	m_worldPosition.y = m_world._42;
	m_worldPosition.z = m_world._43;
}

void Transform::SetPosition(DirectX::XMFLOAT3 position)
{
	m_localPosition.x = position.x;
	m_localPosition.y = position.y;
	m_localPosition.z = position.z;
	UpdateMatrix();
}

void Transform::Translate(DirectX::XMFLOAT3 position)
{
	m_localPosition.x += position.x;
	m_localPosition.y += position.y;
	m_localPosition.z += position.z;
	UpdateMatrix();
}

void Transform::TranslateX(float x)
{
	m_localPosition.x += x;
	UpdateMatrix();
}

void Transform::TranslateY(float y)
{
	m_localPosition.y += y;
	UpdateMatrix();
}

void Transform::TranslateZ(float z)
{
	m_localPosition.z += z;
	UpdateMatrix();
}

void Transform::Rotate(DirectX::XMFLOAT3 rotation)
{

	m_localRotation.x = static_cast<float>(rotation.x / 180.f * 3.141592);
	m_localRotation.y = static_cast<float>(rotation.y / 180.f * 3.141592);
	m_localRotation.z = static_cast<float>(rotation.z / 180.f * 3.141592);
	UpdateMatrix();
}

void Transform::Yaw(float angle)
{
	//m_rotation.y += angle;

	// 	if (m_rotation.y >= 359.f)
	// 	{
	// 		m_rotation.y = 0.f;
	// 	}
	// 	else if (m_rotation.y < 1.f)
	// 	{
	// 		m_rotation.y = 360.f;
	// 		m_rotation.y += angle;
	// 	}
	
	m_localAngle.y += angle;
	m_localRotation.y += static_cast<float>(angle / 180.f * 3.141592);
	UpdateMatrix();
}

void Transform::Pitch(float angle)
{
	// 	m_rotation.x += angle;
	// 
	// 	if (m_rotation.x > 360.f)
	// 	{
	// 		m_rotation.x = 0.f;
	// 	}
	// 	else if (m_rotation.x < 0.f)
	// 	{
	// 		m_rotation.x = 360.f;
	// 	}
	m_localAngle.x += angle;
	m_localRotation.x += static_cast<float>(angle / 180.f * 3.141592);
	UpdateMatrix();
}

void Transform::Roll(float angle)
{
	// 	m_rotation.z += angle;
	// 
	// 	if (m_rotation.z > 360.f)
	// 	{
	// 		m_rotation.z = 0.f;
	// 	}
	// 	else if (m_rotation.z < 0.f)
	// 	{
	// 		m_rotation.z = 360.f;
	// 	}
	m_localAngle.z += angle;
 	m_localRotation.z += static_cast<float>(angle / 180.f * 3.141592);
	UpdateMatrix();
}

