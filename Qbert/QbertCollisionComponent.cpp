#include "QbertCollisionComponent.h"
#include <App.h>
#include <App_Selector.h>
#include <EventQueue.h>
#include <MathFunctions.h>

QbertCollisionComponent::QbertCollisionComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pQbert{}
	, m_pEnemies{}
{
}

void QbertCollisionComponent::PostInitialize()
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	for (const std::pair<GameObjectInformation, GameObject*>& pair : pActiveApp->GetGameObjects())
	{
		if(pair.second->GetTag() == "Red" || pair.second->GetTag() == "Purple")
		{
			m_pEnemies.push_back(pair.second);
		}
	}

	m_pQbert = pActiveApp->GetGameObject("Qbert");
}

void QbertCollisionComponent::Update(const float)
{
	using namespace Integrian;

	const Rectf& qbertRect{ m_pQbert->transform.GetDestRect() };

	for (GameObject* pGameObject : m_pEnemies)
	{
		if (IsOverlapping(pGameObject->transform.GetDestRect(), qbertRect))
		{
			EventQueue::GetInstance().QueueEvent(Event{"QbertDeath"});
			break; // no need tohy is check the other enemies
		}
	}
}
