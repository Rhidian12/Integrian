#include "QbertFSM.h"
#include <FiniteStateMachine.h>
#include <Blackboard.h>
#include "PyramidComponent.h"
#include <App.h>
#include <App_Selector.h>
#include "QbertSpriteComponent.h"
#include "TileComponent.h"
#include "TeleportationPadComponent.h"
#include "TileFactoryComponent.h"
#include <InputManager.h>
#include <TextureManager.h>
#include <Texture.h>
#include <EventQueue.h>

QbertFSM::QbertFSM(Integrian::GameObject* pParent, std::array<Integrian::GameInput, 4>&& keybinds)
	: Component{ pParent }
	, m_pFSM{}
	, m_Keybinds{ std::forward<std::array<Integrian::GameInput, 4>>(keybinds) }
{
	using namespace Integrian;

	EventQueue::GetInstance().AddListener(this);

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };
	Blackboard* pNewBlackboard{ new Blackboard{} };
	PyramidComponent* pPyramid{ pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>() };

	std::shared_ptr<FSMState> pStandingState{ new FSMState{
	[](Blackboard*, const FSMStateTransition) {},
	[this](Blackboard* pBlackboard, const float elapsedSeconds)
	{
		const Point2f initPosition{m_pParent->transform.GetPosition()};
		const Integrian::Vector2f speed{ pBlackboard->GetData<Vector2f>("QbertVelocity") * pBlackboard->GetData<float>("QbertSpeed") * elapsedSeconds };

		m_pParent->transform.SetPosition(initPosition + speed);
	},
	[this, pPyramid](Blackboard* pBlackboard, const float)
	{
		if (!pBlackboard->GetData<bool>("CanMoveAgain") || pBlackboard->GetData<bool>("IsOnTeleporter"))
			return;

		const Point2f qbertPosition{ m_pParent->transform.GetPosition() };

		TileComponent* pQbertTile{ pPyramid->GetTile(qbertPosition) };
		TileComponent* pEndTile{};
		TeleportationPadComponent* pTP{};

		InputManager& inputManager{ InputManager::GetInstance() };

		Vector2f vectorTowardsOtherTile{ pBlackboard->GetData<Vector2f>("VectorTowardsOtherTile") };
		QbertSpriteComponent* pSpriteComponent{ pBlackboard->GetData<QbertSpriteComponent*>("QbertSpriteComponent") };

		if (inputManager.IsPressed(m_Keybinds[KeybindMovementDirection::LeftBottom])) // Left Bottom Movement
		{
			if (std::holds_alternative<TileComponent*>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection))
				pEndTile = std::get<0>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection);

			vectorTowardsOtherTile = Vector2f{ -vectorTowardsOtherTile.x, -vectorTowardsOtherTile.y };

			Rectf sourceRect{ pSpriteComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x += pSpriteComponent->GetTexture()->GetWidth() * 0.5f;
			pSpriteComponent->SetTexture(TextureManager::GetInstance().GetTexture("QbertLeftBottomAnimation"));
			pSpriteComponent->SetSourceRect(sourceRect);
		}
		else if (inputManager.IsPressed(m_Keybinds[KeybindMovementDirection::RightBottom])) // Right Bottom Movement
		{
			if (std::holds_alternative<TileComponent*>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection))
				pEndTile = std::get<0>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection);

			vectorTowardsOtherTile = Vector2f{ vectorTowardsOtherTile.x, -vectorTowardsOtherTile.y };

			Rectf sourceRect{ pSpriteComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x += pSpriteComponent->GetTexture()->GetWidth() * 0.5f;
			pSpriteComponent->SetTexture(TextureManager::GetInstance().GetTexture("QbertRightBottomAnimation"));
			pSpriteComponent->SetSourceRect(sourceRect);
		}
		else if (inputManager.IsPressed(m_Keybinds[KeybindMovementDirection::LeftTop])) // Left Top Movement
		{
			if (std::holds_alternative<TileComponent*>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftTop)].connection))
				pEndTile = std::get<0>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftTop)].connection);
			else
				pTP = std::get<1>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftTop)].connection);

			vectorTowardsOtherTile = Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y };

			Rectf sourceRect{ pSpriteComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x += pSpriteComponent->GetTexture()->GetWidth() * 0.5f;
			pSpriteComponent->SetTexture(TextureManager::GetInstance().GetTexture("QbertLeftTopAnimation"));
			pSpriteComponent->SetSourceRect(sourceRect);
		}
		else if (inputManager.IsPressed(m_Keybinds[KeybindMovementDirection::RightTop])) // Right Top Movement
		{
			if (std::holds_alternative<TileComponent*>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightTop)].connection))
				pEndTile = std::get<0>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightTop)].connection);
			else
				pTP = std::get<1>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightTop)].connection);

			vectorTowardsOtherTile = vectorTowardsOtherTile;

			Rectf sourceRect{ pSpriteComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x += pSpriteComponent->GetTexture()->GetWidth() * 0.5f;
			pSpriteComponent->SetTexture(TextureManager::GetInstance().GetTexture("QbertRightTopAnimation"));
			pSpriteComponent->SetSourceRect(sourceRect);
		}
		else
			return;

		Point2f endPosition{};

		if (pEndTile) // is there a connection to the tile
			endPosition = pEndTile->GetCenter();
		else if (pTP && pTP->GetParent()->GetIsActive()) // is there a connection to a teleporter
		{
			endPosition = pTP->GetParent()->transform.GetPosition();
			pBlackboard->ChangeData("MovingTowardsTeleporter", true);
		}
		else // there is no connection == jumping off the map
		{
			endPosition = qbertPosition + vectorTowardsOtherTile;
			EventQueue::GetInstance().QueueEvent(Event{ "QbertDeath" });
		}

		pBlackboard->ChangeData("CanMoveAgain", false); // make sure we cant move while we're still moving

		Vector2f velocity{};
		velocity = endPosition - qbertPosition;
		Integrian::Normalize(velocity);
		pBlackboard->ChangeData("QbertVelocity", velocity);
		pBlackboard->ChangeData("QbertEndPosition", endPosition);
	},
	[this, pPyramid](Blackboard* pBlackboard, const float)
	{
		Vector2f velocity{ pBlackboard->GetData<Vector2f>("QbertVelocity") };
		Point2f endPosition{ pBlackboard->GetData<Point2f>("QbertEndPosition") };
		QbertSpriteComponent* pSpriteComponent{ pBlackboard->GetData<QbertSpriteComponent*>("QbertSpriteComponent") };

		if (AreEqual(m_pParent->transform.GetPosition().x, endPosition.x, 1.f) && AreEqual(m_pParent->transform.GetPosition().y, endPosition.y, 1.f))
		{
			m_pParent->transform.SetPosition(endPosition);
			if (velocity != Vector2f{})
			{
				Rectf sourceRect{ pSpriteComponent->GetSourceRect() };
				sourceRect[VertexLocation::LeftBottom].x = 0.f;
				pSpriteComponent->SetSourceRect(sourceRect);

				if (pBlackboard->GetData<bool>("MovingTowardsTeleporter"))
				{
					pBlackboard->ChangeData("IsOnTeleporter", true);
					pBlackboard->ChangeData("MovingTowardsTeleporter", false);
				}
				else
					EventQueue::GetInstance().QueueEvent(Event{ "QbertMovementEnded", pPyramid->GetTile(endPosition) });
			}

			pBlackboard->ChangeData("QbertVelocity", Vector2f{});

			//pBlackboard->ChangeData("CurrentQbertWaitTimer", pBlackboard->GetData<float>("CurrentQbertWaitTimer") + dt);
			//if (pBlackboard->GetData<bool>("CurrentQbertWaitTimer") >= pBlackboard->GetData<bool>("QbertWaitTimer"))
			//{
			//	pBlackboard->ChangeData("CurrentQbertWaitTimer", 0.f);
			//}

			pBlackboard->ChangeData("CanMoveAgain", true);
		}
	} } };

	std::shared_ptr<FSMTransition> pToTeleporterTransition{ new FSMTransition{
	[](Blackboard* pBlackboard)->bool
		{
			return pBlackboard->GetData<bool>("IsOnTeleporter");
		}} };
	std::shared_ptr<FSMTransition> pToStandingTransition{ new FSMTransition{
	[](Blackboard* pBlackboard)->bool
	{
		return !pBlackboard->GetData<bool>("IsOnTeleporter");
	}} };

	std::shared_ptr<FSMState> pTpState{ new FSMState{
	[this, pPyramid, pActiveApp](Blackboard* pBlackboard, const FSMStateTransition stateTransition)
	{
		if (stateTransition == FSMStateTransition::OnEnter)
		{
			// left teleporter is active
			if (pBlackboard->GetData<TeleportationPadComponent*>("LeftTeleporter")->GetParent()->transform.GetPosition() == m_pParent->transform.GetPosition())
			{
				pBlackboard->ChangeData("IsLeftTeleporterActive", true);
				pBlackboard->GetData<TeleportationPadComponent*>("LeftTeleporter")->Activate();
			}
			else // right teleporter is active
			{
				pBlackboard->ChangeData("IsRightTeleporterActive", true);
				pBlackboard->GetData<TeleportationPadComponent*>("RightTeleporter")->Activate();
			}
		}
		else
		{
			if (pBlackboard->GetData<bool>("IsLeftTeleporterActive"))
			{
				pActiveApp->GetGameObject("TeleportationPad0")->SetIsActive(false);
				pBlackboard->ChangeData("IsLeftTeleporterActive", false);

				// remove connection
				//const std::vector<GameObject*>* pTiles{ &pPyramid->GetTiles() };
				//
				//unsigned int increment{ 1 };
				//for (unsigned int i{}; i < pTiles->size(); i += increment++)
				//{
				//	TileComponent* pCurrentTile{ (*pTiles)[i]->GetComponentByType<TileComponent>() };
				//	// check if the tile in question has a connection to the teleporter
				//	if (std::holds_alternative<TeleportationPadComponent*>(pCurrentTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftTop)].connection))
				//	{
				//		pCurrentTile->SetConnection(Direction::LeftTop, Connection{});
				//		break;
				//	}
				//}
			}
			else if (pBlackboard->GetData<bool>("IsRightTeleporterActive"))
			{
				pActiveApp->GetGameObject("TeleportationPad1")->SetIsActive(false);
				pBlackboard->ChangeData("IsRightTeleporterActive", false);

				// remove connection
				//const std::vector<GameObject*>* pTiles{ &pPyramid->GetTiles() };
				//
				//unsigned int increment{ 2 };
				//for (unsigned int i{}; i < pTiles->size(); i += increment++)
				//{
				//	TileComponent* pCurrentTile{ (*pTiles)[i]->GetComponentByType<TileComponent>() };
				//	// check if the tile in question has a connection to the teleporter
				//	if (std::holds_alternative<TeleportationPadComponent*>(pCurrentTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightTop)].connection))
				//	{
				//		pCurrentTile->SetConnection(Direction::RightTop, Connection{});
				//		break;
				//	}
				//}
			}
		}
	},
	[](Blackboard*, const float) {},
	[](Blackboard* pBlackboard, const float)
	{
		if (pBlackboard->GetData<bool>("IsLeftTeleporterActive"))
		{
			if (pBlackboard->GetData<TeleportationPadComponent*>("LeftTeleporter")->IsCompletelyDone())
			{
				pBlackboard->ChangeData("IsOnTeleporter", false);
			}
		}
		else if (pBlackboard->GetData<bool>("IsRightTeleporterActive"))
		{
			if (pBlackboard->GetData<TeleportationPadComponent*>("RightTeleporter")->IsCompletelyDone())
			{
				pBlackboard->ChangeData("IsOnTeleporter", false);
			}
		}
	}
	} };

	std::shared_ptr<FSMState> pResetState{ new FSMState{
	[](Blackboard* pBlackboard, FSMStateTransition)
		{
			pBlackboard->ChangeData("CurrentQbertWaitTimer", 0.f);
		},
	[](Blackboard*, const float) {},
	[](Blackboard* pBlackboard, const float dt)
		{
			pBlackboard->ChangeData("CurrentQbertWaitTimer", pBlackboard->GetData<float>("CurrentQbertWaitTimer") + dt);
			if (pBlackboard->GetData<float>("CurrentQbertWaitTimer") >= pBlackboard->GetData<float>("QbertWaitTimer"))
			{
				pBlackboard->ChangeData("CurrentQbertWaitTimer", 0.f);
				pBlackboard->ChangeData("CanMoveAgain", true);
				pBlackboard->ChangeData("ShouldReset", false);
			}
		}
	} };

	std::shared_ptr<FSMTransition> pToResetState{ new FSMTransition{
	[](Blackboard* pBlackboard)->bool
		{
			return pBlackboard->GetData<bool>("ShouldReset");
		}
	} };

	std::shared_ptr<FSMTransition> pToStandingState{ new FSMTransition{
	[](Blackboard* pBlackboard)->bool
		{
			return pBlackboard->GetData<bool>("CanMoveAgain");
		}
	} };


	m_pFSM = new FiniteStateMachineComponent{ m_pParent, pStandingState, pNewBlackboard };
	m_pFSM->AddTransition(pStandingState, pTpState, pToTeleporterTransition);
	m_pFSM->AddTransition(pTpState, pStandingState, pToStandingTransition);
	m_pFSM->AddTransition(pStandingState, pResetState, pToResetState);
	m_pFSM->AddTransition(pResetState, pStandingState, pToStandingState);

	m_pParent->AddComponent(m_pFSM);
}

void QbertFSM::PostInitialize()
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	PyramidComponent* pPyramid{ pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>() };

	Blackboard* pBlackboard{ m_pFSM->GetBlackboard() };
	pBlackboard->AddData("VectorTowardsOtherTile", pPyramid->GetTiles()[1]->GetComponentByType<TileComponent>()->GetCenter() -
		pPyramid->GetTiles()[0]->GetComponentByType<TileComponent>()->GetCenter());
	pBlackboard->AddData("CanMoveAgain", true);
	pBlackboard->AddData("QbertSpeed", 65.f);
	pBlackboard->AddData("QbertVelocity", Vector2f{});
	pBlackboard->AddData("QbertSpriteComponent", m_pParent->GetComponentByType<QbertSpriteComponent>());
	pBlackboard->AddData("QbertEndPosition", Point2f{});
	pBlackboard->AddData("IsOnTeleporter", false);
	pBlackboard->AddData("MovingTowardsTeleporter", false);
	pBlackboard->AddData("LeftTeleporter", pActiveApp->GetGameObject("TeleportationPad0")->GetComponentByType<TeleportationPadComponent>());
	pBlackboard->AddData("RightTeleporter", pActiveApp->GetGameObject("TeleportationPad1")->GetComponentByType<TeleportationPadComponent>());
	pBlackboard->AddData("IsLeftTeleporterActive", false);
	pBlackboard->AddData("IsRightTeleporterActive", false);
	pBlackboard->AddData("PyramidSize", pPyramid->GetParent()->GetComponentByType<TileFactoryComponent>()->GetSize());
	pBlackboard->AddData("QbertWaitTimer", 0.5f);
	pBlackboard->AddData("CurrentQbertWaitTimer", 0.f);
	pBlackboard->AddData("ShouldReset", false);
}

void QbertFSM::Reset()
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };
	PyramidComponent* pPyramid{ pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>() };

	Blackboard* pBlackboard{ m_pFSM->GetBlackboard() };
	pBlackboard->ChangeData("QbertVelocity", Vector2f{});
	pBlackboard->ChangeData("ShouldReset", true);
	pBlackboard->ChangeData("CanMoveAgain", false);

	m_pParent->transform.SetPosition(pPyramid->GetTopTileCenter());
}

bool QbertFSM::OnEvent(const Integrian::Event& event)
{
	const std::string eventName{ event.GetEvent() };

	if (eventName == "QbertDeath")
	{
		Reset();
		return true;
	}

	if (eventName == "ResetGame")
	{
		Reset();
		return true;
	}

	return false;
}