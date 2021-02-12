#include "GameObject.h"
#include "Component.h"

void Integrian::GameObject::AddComponent(const std::string& name, Component* pComponent)
{
	if (!m_pComponents.insert(std::make_pair(name, pComponent)).second)
	{
		// TODO: Make the Logger print a message that this component was already added
	}
}

const std::unordered_map<std::string, Integrian::Component*>& Integrian::GameObject::GetComponents() const
{
	return m_pComponents;
}
