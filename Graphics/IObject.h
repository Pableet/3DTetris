#pragma once

#include "DX11Define.h"


class IObject abstract
{
public:
	virtual void Initialize(ID3D11Device* device) abstract;
	virtual void Update() abstract;

	ID3D11Buffer* GetVertexBuffer()
	{
		return m_vb;
	}
	ID3D11Buffer* GetIndexBuffer()
	{
		return m_ib;
	}

	void SetViewMatrix(XMMATRIX view)
	{
		XMStoreFloat4x4(&m_view, view);
	}
	void SetProjMatrix(XMMATRIX proj)
	{
		XMStoreFloat4x4(&m_proj, proj);
	}
	void SetWorldMatrix(XMMATRIX world)
	{
		XMStoreFloat4x4(&m_world, world);
	}

	XMFLOAT4X4 GetWorld() { return m_world; }
	XMFLOAT4X4 GetView() { return m_view; }
	XMFLOAT4X4 GetProj() { return m_proj; }

	XMMATRIX GetWVP()
	{
		return m_worldViewProj;
	}
	UINT GetIndexCount() { return m_indexCount; }
	D3D_PRIMITIVE_TOPOLOGY GetPrimitive() { return m_primitive; }

	void SetGridXY(int x, int y)
	{
		m_xline = x;
		m_yline = y;
	}

	void SetTranslate(float x, float y, float z)
	{
		m_world._41 = x;
		m_world._42 = y;
		m_world._43 = z;
	}

	void SetRotation(float x, float y, float z)
	{
		float xAngle = static_cast<float>(x / 180.f * 3.141592);
		float yAngle = static_cast<float>(y / 180.f * 3.141592);
		float zAngle = static_cast<float>(z / 180.f * 3.141592);
		if (m_isParent)
		{
			m_local = m_world;
		}
		m_world = m_local * XMMatrixRotationX(xAngle) * XMMatrixRotationY(yAngle) * XMMatrixRotationZ(zAngle);
	}

	void SetName(std::string name)
	{
		m_name = name;
	}

	std::string GetName()
	{
		return m_name;
	}

	void SetColor(float r, float g, float b, float a)
	{
		m_color[0] = r;
		m_color[1] = g;
		m_color[2] = b;
		m_color[3] = a;
	}

	void SetRenderState(int nowRS)
	{
		m_currentRS = nowRS;
	}

	int GetRS()
	{
		return m_currentRS;
	}

	void SetID(int id)
	{
		m_id = id;
	}

	int GetID()
	{
		return m_id;
	}

	void SetScale(float scale)
	{
		m_scale = scale;
	}

protected:
	ID3D11Buffer* m_vb = nullptr;
	ID3D11Buffer* m_ib = nullptr;

	XMFLOAT4X4 m_local = {};
	XMFLOAT4X4 m_world = {};
	XMFLOAT4X4 m_view = {};
	XMFLOAT4X4 m_proj = {};
	XMMATRIX m_worldViewProj = {};

	UINT m_indexCount = 0;
	D3D_PRIMITIVE_TOPOLOGY m_primitive = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;

	int m_xline = 0;
	int m_yline = 0;

	bool m_isParent = true;
	bool m_isChild = false;

	std::string m_name = {};
	int m_id = 0;

	float m_color[4] = { 0.f,0.f,0.f,0.f };
	int m_currentRS = 0;

	float m_scale = 0.f;
};

