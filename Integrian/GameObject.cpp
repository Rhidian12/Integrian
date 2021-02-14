#include "pch.h"
#include "GameObject.h"
#include "Component.h"

Integrian::GameObject::~GameObject()
{
	for (std::pair<std::string, Component*> pair : m_pComponents)
		SAFE_DELETE(pair.second);
}

void Integrian::GameObject::AddComponent(const std::string& name, Component* pComponent)
{
	if (!m_pComponents.insert(std::make_pair(name, pComponent)).second)
	{
		// TODO: Make the Logger print a message that this component was already added
	}
}

void Integrian::GameObject::Update(const float elapsedSeconds)
{
	for (const std::pair<std::string, Component*>& pair : m_pComponents)
		pair.second->Update(elapsedSeconds);
}

void Integrian::GameObject::FixedUpdate(const float elapsedSeconds)
{
	for (const std::pair<std::string, Component*>& pair : m_pComponents)
		pair.second->FixedUpdate(elapsedSeconds);
}

void Integrian::GameObject::LateUpdate(const float elapsedSeconds)
{
	for (const std::pair<std::string, Component*>& pair : m_pComponents)
		pair.second->LateUpdate(elapsedSeconds);
}

void Integrian::GameObject::Render() const
{
	for (const std::pair<std::string, Component*>& pair : m_pComponents)
		pair.second->Render(transform.GetPosition());
}
