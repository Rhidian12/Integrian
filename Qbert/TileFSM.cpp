#include "TileFSM.h"
#include <TextureComponent.h>
#include <GameObject.h>
#include "TileComponent.h"
#include <EventQueue.h>

TileFSM::TileFSM(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pBlackboard{ new Integrian::Blackboard{} }
{
	Integrian::EventQueue::GetInstance().AddListener(this);
}

Integrian::FiniteStateMachineComponent* TileFSM::CreatePermanentFSM(Integrian::Texture* pInactiveTexture, Integrian::Texture* pActiveTexture)
{
	using namespace Integrian;

	m_pBlackboard->AddData("TileChanged", nullptr);
	m_pBlackboard->AddData("InactiveTexture", pInactiveTexture);
	m_pBlackboard->AddData("ActiveTexture", pActiveTexture);

	std::shared_ptr<FSMState> beginState{ new FSMState{
	[](Blackboard*, const FSMStateTransition) {},
	// Fixed Update
	[](Blackboard*, const float) {},
	// Update
	[](Blackboard* pBlackboard, const float)
	{
		GameObject* pTile{pBlackboard->GetData<GameObject*>("TileChanged")};
		if (pTile)
		{
			TextureComponent* pTextureComponent{ pTile->GetComponentByType<TextureComponent>() };
			if (pTextureComponent->GetTexture() == pBlackboard->GetData<Texture*>("InactiveTexture"))
			{
				pTextureComponent->SetTexture(pBlackboard->GetData<Texture*>("ActiveTexture"));
				pBlackboard->ChangeData("TileChanged", nullptr);
				EventQueue::GetInstance().QueueEvent(Event{ "TileChanged", 25 });
			}
		}
	}
	} };

	return new FiniteStateMachineComponent{ m_pParent, beginState, m_pBlackboard };
}

bool TileFSM::OnEvent(const Integrian::Event& event)
{
	if (event.GetEvent() == "QbertMovementEnded")
	{
		m_pBlackboard->ChangeData("TileChanged", std::get<0>(event.GetData<TileComponent*>())->GetParent());
		return true;
	}

	return false;
}
