#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Command.h"

Integrian::GameObject::~GameObject()
{
	for (Component* pComponent : m_pComponents)
		SafeDelete(pComponent);
}

void Integrian::GameObject::AddComponent(Component* pComponent)
{
	const std::vector<Component*>::const_iterator isComponentAlreadyInList =
		std::find_if(m_pComponents.cbegin(), m_pComponents.cend(), [pComponent](Component* pC)->bool
			{
				return pComponent == pC;
			});
	if (isComponentAlreadyInList != m_pComponents.cend())
	{
		Logger::GetInstance().Log(typeid(*pComponent).name(), ErrorLevel::severeError);
		Logger::GetInstance().Log(" was already added!\n", ErrorLevel::severeError);
	}
	else
		m_pComponents.push_back(pComponent);
}

//void Integrian::GameObject::AddCommand(Command* pCommand)
//{
//#if _DEBUG
//	std::vector<Command*>::const_iterator isCommandAlreadyInVector =
//		std::find_if(m_pCommands.cbegin(), m_pCommands.cend(), [pCommand](Command* pC)->bool
//			{
//				return pCommand == pC;
//			});
//	if (isCommandAlreadyInVector == m_pCommands.cend())
//	{
//		Logger::GetInstance().Log(typeid(*pCommand).name(), ErrorLevel::warning);
//		Logger::GetInstance().Log(" was already added!\n", ErrorLevel::warning);
//	}
//
//	m_pCommands.push_back(pCommand);
//#else
//	
//	m_pCommands.push_back(pCommand);
//
//#endif
//}

void Integrian::GameObject::Update(const float elapsedSeconds)
{
	for (Component* pComponent : m_pComponents)
		pComponent->Update(elapsedSeconds);
}

void Integrian::GameObject::FixedUpdate(const float elapsedSeconds)
{
	for (Component* pComponent : m_pComponents)
		pComponent->FixedUpdate(elapsedSeconds);
}

void Integrian::GameObject::LateUpdate(const float elapsedSeconds)
{
	for (Component* pComponent : m_pComponents)
		pComponent->LateUpdate(elapsedSeconds);
}

void Integrian::GameObject::Render() const
{
	for (Component* pComponent : m_pComponents)
		pComponent->Render(transform.GetPosition());
}
