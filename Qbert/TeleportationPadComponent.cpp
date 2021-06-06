#include "TeleportationPadComponent.h"
#include <App_Selector.h>
#include <App.h>
#include "PyramidComponent.h"

TeleportationPadComponent::TeleportationPadComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pQbert{}
	, m_IsActivated{}
	, m_Speed{ 65.f }
	, m_IsQbertDroppedOff{}
	, m_CompletelyDone{}
	, m_StartPosition{}
{
}

void TeleportationPadComponent::PostInitialize()
{
	m_StartPosition = m_pParent->transform.GetPosition();
}

void TeleportationPadComponent::Update(const float dt)
{
	using namespace Integrian;

	if (!m_pQbert)
	{
		App* pActiveApp{ Integrian::App_Selector::GetInstance().GetActiveApplication() };

		m_pQbert = pActiveApp->GetGameObject("QbertOne");
		m_EndPosition = pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>()->GetTopTileCenter();

		m_EndPosition.y += 20.f;
	}

	if (m_IsActivated && !m_IsQbertDroppedOff)
	{
		const Point2f parentPosition{ m_pParent->transform.GetPosition() };
		const Point2f qbertPosition{ m_pQbert->transform.GetPosition() };
		Vector2f velocity{ m_EndPosition - parentPosition };
		Normalize(velocity);
		m_pParent->transform.SetPosition(parentPosition + velocity * m_Speed * dt);
		m_pQbert->transform.SetPosition(qbertPosition + velocity * m_Speed * dt);

		if (AreEqual(m_pParent->transform.GetPosition().x, m_EndPosition.x, 1.f) && AreEqual(m_pParent->transform.GetPosition().y, m_EndPosition.y, 1.f))
		{
			//m_IsActivated = false;
			m_EndPosition.y -= 20.f;
			m_IsQbertDroppedOff = true;
		}
	}

	if (m_IsActivated && m_IsQbertDroppedOff && !m_CompletelyDone)
	{
		const Point2f qbertPosition{ m_pQbert->transform.GetPosition() };
		Vector2f velocity{ m_EndPosition - m_pQbert->transform.GetPosition() };
		Normalize(velocity);
		m_pQbert->transform.SetPosition(qbertPosition + velocity * m_Speed * dt);

		if (AreEqual(m_pQbert->transform.GetPosition().x, m_EndPosition.x, 1.f) && AreEqual(m_pQbert->transform.GetPosition().y, m_EndPosition.y, 1.f))
		{
			m_pQbert->transform.SetPosition(m_EndPosition);
			m_CompletelyDone = true;
		}
	}
}

void TeleportationPadComponent::Activate()
{
	m_IsActivated = true;
}

bool TeleportationPadComponent::IsCompletelyDone() const
{
	return m_CompletelyDone;
}

bool TeleportationPadComponent::OnEvent(const Integrian::Event& event)
{
	if (event.GetEvent() == "ResetGame")
	{
		ResetGame();
		return true;
	}
	return false;
}

void TeleportationPadComponent::ResetGame()
{
	using namespace Integrian;
	if (!m_pParent->GetIsActive())
	{

		m_IsActivated = false;
		m_CompletelyDone = false;
		m_IsQbertDroppedOff = false;

		App* pActiveApp{ Integrian::App_Selector::GetInstance().GetActiveApplication() };

		m_EndPosition = pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>()->GetTopTileCenter();
		m_EndPosition.y += 20.f;

		m_pParent->transform.SetPosition(m_StartPosition);

		m_pParent->SetIsActive(true);
	}
}
