#include "TeleportationPadComponent.h"
#include <App_Selector.h>
#include <App.h>
#include "PyramidComponent.h"

TeleportationPadComponent::TeleportationPadComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pQbert{}
	, m_IsActivated{}
	, m_Speed{ 10.f }
{
}

void TeleportationPadComponent::Update(const float)
{
	using namespace Integrian;

	if (!m_pQbert)
	{
		App* pActiveApp{ Integrian::App_Selector::GetInstance().GetActiveApplication() };

		m_pQbert = pActiveApp->GetGameObject("Qbert");
		m_EndPosition = pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>()->GetTopTileCenter();

		m_EndPosition.y += 20.f;
	}

	if (m_IsActivated)
	{
		Vector2f velocity{ m_EndPosition - m_pParent->transform.GetPosition() };
		Normalize(velocity);
		m_pParent->transform.Translate(velocity * m_Speed);

		if (AreEqual(m_pParent->transform.GetPosition().x, m_EndPosition.x, 1.f) && AreEqual(m_pParent->transform.GetPosition().y, m_EndPosition.y, 1.f))
		{

		}
	}
}