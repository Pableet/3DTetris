#include "Component.h"


Component::Component()
	: m_owner(nullptr)
{

}

Component::~Component()
{
	m_owner = nullptr;
}

I3DRenderer* Component::m_renderer = nullptr;