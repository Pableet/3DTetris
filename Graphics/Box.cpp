#include "Box.h"
#include <DirectXColors.h>

Box::Box()
{

}

Box::~Box()
{
	ReleaseCOM(m_ib);
	ReleaseCOM(m_vb);
}

void Box::Initialize(ID3D11Device* device)
{
	Vertex vertices[] =
	{
		{ XMFLOAT3(-m_scale, -m_scale, -m_scale), XMFLOAT4((const float*)&m_color) },
		{ XMFLOAT3(-m_scale, +m_scale, -m_scale), XMFLOAT4((const float*)&m_color) },
		{ XMFLOAT3(+m_scale, +m_scale, -m_scale), XMFLOAT4((const float*)&m_color) },	// 우상 증가
		{ XMFLOAT3(+m_scale, -m_scale, -m_scale), XMFLOAT4((const float*)&m_color) },
		{ XMFLOAT3(-m_scale, -m_scale, +m_scale), XMFLOAT4((const float*)&m_color) },
		{ XMFLOAT3(-m_scale, +m_scale, +m_scale), XMFLOAT4((const float*)&m_color) },
		{ XMFLOAT3(+m_scale, +m_scale, +m_scale), XMFLOAT4((const float*)&m_color) },
		{ XMFLOAT3(+m_scale, -m_scale, +m_scale), XMFLOAT4((const float*)&m_color) }
	};

	UINT indices[] =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};



	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * 8;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	HR(device->CreateBuffer(&vbd, &vinitData, &m_vb));

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * 36;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	HR(device->CreateBuffer(&ibd, &iinitData, &m_ib));

	m_indexCount = 36;
	m_primitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

void Box::Update()
{
	m_worldViewProj = m_world * m_view * m_proj;
}

