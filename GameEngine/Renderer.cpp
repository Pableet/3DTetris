#include "Renderer.h"
#include <stdarg.h>
#include <tchar.h>

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	if (m_owner->GetName() == "")
	{
		m_renderer->DeleteObject(m_owner->GetID());
	}
	else
	{
		m_renderer->DeleteObject(m_owner->GetName());
	}
}

void Renderer::Start()
{

}

void Renderer::FixedUpdate()
{

}

void Renderer::Update(float dTime)
{

}

void Renderer::LateUpdate(float dTime)
{

}

void Renderer::AddBox()
{
	if (m_owner->GetName() == "")
	{
		m_renderer->AddBox(m_owner->GetID(), 0);
	}
	else
	{
		m_renderer->AddBox(m_owner->GetName(), 0);
	}
}

void Renderer::AddGrid(int gridSize_x, int gridSize_y)
{
	m_renderer->AddGrid(m_owner->GetName(), gridSize_x, gridSize_y);
}

void Renderer::SetBoxColor(float r, float g, float b, float a)
{
	if (m_owner->GetName() == "")
	{
		m_renderer->SetBoxColor(m_owner->GetID(), r, g, b, a);

	}
	else
	{
		m_renderer->SetBoxColor(m_owner->GetName(), r, g, b, a);
	}
}

void Renderer::SetBoxColor(float* rgba)
{
	if (m_owner->GetName() == "")
	{
		m_renderer->SetBoxColor(m_owner->GetID(), rgba[0], rgba[1], rgba[2], rgba[3]);

	}
	else
	{
		m_renderer->SetBoxColor(m_owner->GetName(), rgba[0], rgba[1], rgba[2], rgba[3]);
	}
}

void Renderer::SetRS(int nowRS)
{
	if (m_owner->GetName() == "")
	{
		m_renderer->SetRenderState(m_owner->GetID(), nowRS);
	}
	else
	{
		m_renderer->SetRenderState(m_owner->GetName(), nowRS);
	}
}

void Renderer::SetRectSize(float scale)
{
	if (m_owner->GetName() == "")
	{
		m_renderer->SetRectSize(m_owner->GetID(), scale);
	}
	else
	{
		m_renderer->SetRectSize(m_owner->GetName(), scale);
	}
}

void Renderer::AddText(int x, int y, float r, float g, float b, float a, const wchar_t* text, ...)
{
	TCHAR _buffer[1024] = L"";
	va_list vl;
	va_start(vl, text);
	_vstprintf(_buffer, 1024, text, vl);
	va_end(vl);
	if (m_owner->GetName() == "")
	{
		m_renderer->DrawColoredText(x, y, r, g, b, a, m_owner->GetID(), _buffer);
	}
	else
	{
		m_renderer->DrawColoredText(x, y, r, g, b, a, m_owner->GetID(), _buffer);
	}
}

void Renderer::DeleteRenderer()
{
	if (m_owner)
	{
		if (m_owner->GetName() == "")
		{
			m_renderer->DeleteObject(m_owner->GetID());
		}
		else
		{
			m_renderer->DeleteObject(m_owner->GetName());
		}
	}
}
