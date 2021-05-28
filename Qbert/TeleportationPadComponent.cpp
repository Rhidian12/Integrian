#include "TeleportationPadComponent.h"
#include <App_Selector.h>
#include <App.h>
#include "PyramidComponent.h"

TeleportationPadComponent::TeleportationPadComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pQbert{}
{
}

void TeleportationPadComponent::PostInitialize()
{
	using namespace Integrian;

	App* pActiveApp{ Integrian::App_Selector::GetInstance().GetActiveApplication() };

	m_pQbert = pActiveApp->GetGameObject("Qbert");
	m_EndPosition = pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>()->GetTopTileCenter();

	m_EndPosition.y += 20.f;
}

void TeleportationPadComponent::Update(const float elapsedSeconds)
{

}