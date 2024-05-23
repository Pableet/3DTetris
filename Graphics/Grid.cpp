#include "Grid.h"
#include "DirectXColors.h"

Grid::Grid()
{

}

Grid::~Grid()
{
	ReleaseCOM(m_ib);
	ReleaseCOM(m_vb);
}

void Grid::Initialize(ID3D11Device* device)
{
	std::vector<Vertex> vertices;


	for (int i = 0; i < (m_xline + 1) * (m_yline + 1); i++)
	{
		Vertex v;
		v.Pos = XMFLOAT3((float)(i % (m_xline + 1)) - ((m_xline + 1) / 2.f), 0.0f, (float)(i / (m_xline + 1)) - ((m_xline + 1) / 2.f));
		v.Color = XMFLOAT4((const float*)&Colors::Green);	// (어두운 회색)
		vertices.push_back(v);
	}


	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * (UINT)vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices.data();
	HR(device->CreateBuffer(&vbd, &vinitData, &m_vb));


	// 인덱스 버퍼를 생성한다.
	// 역시 40개의 라인을 나타내도록 했다.
	std::vector<UINT> indices;
	for (int i = 0; i < m_xline + 1; i++)
	{
		indices.push_back(i);
		indices.push_back(i + (m_xline + 1) * m_yline);
	}

	for (int i = 0; i < m_yline + 1; i++)
	{
		indices.push_back(i * (m_xline + 1));
		indices.push_back(i * (m_xline + 1) + m_xline);
	}



	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * (UINT)indices.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices.data();
	HR(device->CreateBuffer(&ibd, &iinitData, &m_ib));


	m_indexCount = (UINT)indices.size();


	m_primitive = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
}

void Grid::Update()
{
	m_worldViewProj = m_world * m_view * m_proj;
}

