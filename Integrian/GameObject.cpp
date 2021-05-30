#include "IntegrianPCH.h" // precompiled header
#include "GameObject.h" // header
#include "Component.h" // component

Integrian::GameObject::~GameObject()
{
	for (Component*& pComponent : m_pComponents)
		SafeDelete(pComponent);
}

void Integrian::GameObject::Initialize()
{
	for (Component* pComponent : m_pComponents)
		pComponent->Initialize();
}

void Integrian::GameObject::PostInitialize()
{
	for (Component* pComponent : m_pComponents)
		pComponent->PostInitialize();
}

void Integrian::GameObject::AddComponent(Component* pComponent)
{
	const std::vector<Component*>::const_iterator isComponentAlreadyInList =
		std::find_if(m_pComponents.cbegin(), m_pComponents.cend(), [pComponent](Component* pC)->bool
			{
				return pComponent == pC;
			});
	if (isComponentAlreadyInList != m_pComponents.cend())
		Logger::LogWarning(std::string{ typeid(*pComponent).name() } + " was already added\n");
	else
		m_pComponents.push_back(pComponent);
}

void Integrian::GameObject::Update(const float elapsedSeconds)
{
	if (!m_IsActive || m_MarkedForDeletion)
		return;

	transform.Update(elapsedSeconds);

	for (Component* pComponent : m_pComponents)
		pComponent->Update(elapsedSeconds);
}

void Integrian::GameObject::FixedUpdate(const float elapsedSeconds)
{
	if (!m_IsActive || m_MarkedForDeletion)
		return;

	transform.FixedUpdate(elapsedSeconds);

	for (Component* pComponent : m_pComponents)
		pComponent->FixedUpdate(elapsedSeconds);
}

void Integrian::GameObject::LateUpdate(const float elapsedSeconds)
{
	if (!m_IsActive || m_MarkedForDeletion)
		return;

	transform.LateUpdate(elapsedSeconds);

	for (Component* pComponent : m_pComponents)
		pComponent->LateUpdate(elapsedSeconds);
}

void Integrian::GameObject::Render() const
{
	if (!m_IsActive || m_MarkedForDeletion)
		return;

	for (Component* pComponent : m_pComponents)
		pComponent->Render();
}

void Integrian::GameObject::SetIsActive(bool isActive) noexcept
{
	m_IsActive = isActive;
}

void Integrian::GameObject::MarkForDeletion(bool markedForDeletion) noexcept
{
	m_MarkedForDeletion = markedForDeletion;
}

bool Integrian::GameObject::GetIsActive() const noexcept
{
	return m_IsActive;
}

bool Integrian::GameObject::GetIsMarkedForDeletion() const noexcept
{
	return m_MarkedForDeletion;
}
