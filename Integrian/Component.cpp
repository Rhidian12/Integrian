#include "IntegrianPCH.h" // precompiled header
#include "Component.h" // header

Integrian::Component::Component(GameObject* pParent)
	: m_pParent{ pParent }
{
}

Integrian::GameObject* Integrian::Component::GetParent() const
{
	return m_pParent;
}