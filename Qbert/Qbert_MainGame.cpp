#include "Qbert_MainGame.h"
#include <Texture.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include "PyramidComponent.h"
#include "QbertMovementComponent.h"
#include "TileFactoryComponent.h"
#include "QbertSpriteComponent.h"
#include <Utility Functions.h>
#include <FiniteStateMachine.h>
#include "TileComponent.h"
#include <InputManager.h>
#include "TeleportationPadComponent.h"

Qbert_MainGame::Qbert_MainGame()
	: Integrian::App{ "Qbert_MainGame" }
{
}

void Qbert_MainGame::Start()
{
	using namespace Integrian;

	GameObject* pPyramidRoot{ new GameObject{} };
	pPyramidRoot->transform.SetPosition(Point2f{ m_WindowWidth / 2.f, (m_WindowHeight / 2.f) });

	PyramidComponent* pPyramidComponent{ new PyramidComponent{pPyramidRoot} };
	pPyramidRoot->AddComponent(pPyramidComponent);

	TileFactoryComponent* pTileFactoryComponent{ new TileFactoryComponent{pPyramidRoot} };
	pTileFactoryComponent->CreateTiles(1);
	pPyramidRoot->AddComponent(pTileFactoryComponent);

	GameObject* pQbert{ new GameObject{} };
	//pQbert->AddComponent(new QbertMovementComponent{ pQbert });
	pQbert->AddComponent(new QbertSpriteComponent{ pQbert });

	Blackboard* pNewBlackboard{ new Blackboard{} };
	pNewBlackboard->AddData("VectorTowardsOtherTile", pPyramidComponent->GetTiles()[1]->GetComponentByType<TileComponent>()->GetCenter() -
		pPyramidComponent->GetTiles()[0]->GetComponentByType<TileComponent>()->GetCenter());
	pNewBlackboard->AddData("CanMoveAgain", true);
	pNewBlackboard->AddData("QbertSpeed", 65.f);
	pNewBlackboard->AddData("QbertVelocity", Vector2f{});
	pNewBlackboard->AddData("QbertSpriteComponent", pQbert->GetComponentByType<QbertSpriteComponent>());
	pNewBlackboard->AddData("Qbert", pQbert);
	pNewBlackboard->AddData("QbertEndPosition", Point2f{});
	pNewBlackboard->AddData("IsOnTeleporter", false);
	pNewBlackboard->AddData("MovingTowardsTeleporter", false);
	pNewBlackboard->AddData("LeftTeleporter", GetGameObject("TeleportationPad0")->GetComponentByType<TeleportationPadComponent>());
	pNewBlackboard->AddData("RightTeleporter", GetGameObject("TeleportationPad1")->GetComponentByType<TeleportationPadComponent>());
	pNewBlackboard->AddData("IsLeftTeleporterActive", false);
	pNewBlackboard->AddData("IsRightTeleporterActive", false);

	FSMState* pStandingState{ new FSMState{
		[](Blackboard*, const FSMStateTransition) {},
		[](Blackboard* pBlackboard, const float elapsedSeconds)
		{
			const Point2f initPosition{pBlackboard->GetData<GameObject*>("Qbert")->transform.GetPosition()};
			const Integrian::Vector2f speed{ pBlackboard->GetData<Vector2f>("QbertVelocity") * pBlackboard->GetData<float>("QbertSpeed") * elapsedSeconds };

			pBlackboard->GetData<GameObject*>("Qbert")->transform.SetPosition(initPosition + speed);
		},
		[pPyramidComponent](Blackboard* pBlackboard, const float)
		{
			if (!pBlackboard->GetData<bool>("CanMoveAgain") || pBlackboard->GetData<bool>("IsOnTeleporter"))
				return;

			const Point2f qbertPosition{ pBlackboard->GetData<GameObject*>("Qbert")->transform.GetPosition() };

			TileComponent* pQbertTile{ pPyramidComponent->GetTile(qbertPosition) };
			TileComponent* pEndTile{};
			TeleportationPadComponent* pTP{};

			InputManager& inputManager{ InputManager::GetInstance() };

			Vector2f vectorTowardsOtherTile{ pBlackboard->GetData<Vector2f>("VectorTowardsOtherTile") };
			QbertSpriteComponent* pSpriteComponent{ pBlackboard->GetData<QbertSpriteComponent*>("QbertSpriteComponent") };

			if (inputManager.IsKeyboardKeyPressed(KeyboardInput::A)) // Left Bottom Movement
			{
				if (std::holds_alternative<TileComponent*>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection))
					pEndTile = std::get<0>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection);

				vectorTowardsOtherTile = Vector2f{ -vectorTowardsOtherTile.x, -vectorTowardsOtherTile.y };

				Rectf sourceRect{ pSpriteComponent->GetSourceRect() };
				sourceRect[VertexLocation::LeftBottom].x += pSpriteComponent->GetTexture()->GetWidth() * 0.5f;
				pSpriteComponent->SetTexture(TextureManager::GetInstance().GetTexture("QbertLeftBottomAnimation"));
				pSpriteComponent->SetSourceRect(sourceRect);
			}
			else if (inputManager.IsKeyboardKeyPressed(KeyboardInput::D)) // Right Bottom Movement
			{
				if (std::holds_alternative<TileComponent*>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection))
					pEndTile = std::get<0>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection);

				vectorTowardsOtherTile = Vector2f{ vectorTowardsOtherTile.x, -vectorTowardsOtherTile.y };

				Rectf sourceRect{ pSpriteComponent->GetSourceRect() };
				sourceRect[VertexLocation::LeftBottom].x += pSpriteComponent->GetTexture()->GetWidth() * 0.5f;
				pSpriteComponent->SetTexture(TextureManager::GetInstance().GetTexture("QbertRightBottomAnimation"));
				pSpriteComponent->SetSourceRect(sourceRect);
			}
			else if (inputManager.IsKeyboardKeyPressed(KeyboardInput::Q)) // Left Top Movement
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
			else if (inputManager.IsKeyboardKeyPressed(KeyboardInput::E)) // Right Top Movement
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
			else if (pTP) // is there a connection to a teleporter
			{
				endPosition = pTP->GetParent()->transform.GetPosition();
				pBlackboard->ChangeData("MovingTowardsTeleporter", true);
			}
			else // there is no connection == jumping off the map
			{
				endPosition = qbertPosition + vectorTowardsOtherTile;
				EventQueue::GetInstance().QueueEvent(Event{ "QbertMoveOffTheMap" });
			}

			pBlackboard->ChangeData("CanMoveAgain", false); // make sure we cant move while we're still moving

			Vector2f velocity{};
			velocity = endPosition - qbertPosition;
			Integrian::Normalize(velocity);
			pBlackboard->ChangeData("QbertVelocity", velocity);
			pBlackboard->ChangeData("QbertEndPosition", endPosition);
		},
		[pPyramidComponent](Blackboard* pBlackboard, const float)
		{
			GameObject* pParent{ pBlackboard->GetData<GameObject*>("Qbert") };
			Vector2f velocity{ pBlackboard->GetData<Vector2f>("QbertVelocity") };
			Point2f endPosition{ pBlackboard->GetData<Point2f>("QbertEndPosition") };
			QbertSpriteComponent* pSpriteComponent{ pBlackboard->GetData<QbertSpriteComponent*>("QbertSpriteComponent") };

			if (AreEqual(pParent->transform.GetPosition().x, endPosition.x, 1.f) && AreEqual(pParent->transform.GetPosition().y, endPosition.y, 1.f))
			{
				pParent->transform.SetPosition(endPosition);
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
						EventQueue::GetInstance().QueueEvent(Event{ "QbertMovementEnded", pPyramidComponent->GetTile(endPosition) });

				}

				pBlackboard->ChangeData("QbertVelocity", Vector2f{});

				pBlackboard->ChangeData("CanMoveAgain", true);
			}
		} } };

	FSMTransition* pToTeleporterTransition{ new FSMTransition{
	[](Blackboard* pBlackboard)->bool
		{
			return pBlackboard->GetData<bool>("IsOnTeleporter");
		}} };
	FSMTransition* pToStandingTransition{ new FSMTransition{
	[](Blackboard* pBlackboard)->bool
	{
		return !pBlackboard->GetData<bool>("IsOnTeleporter");
	}} };

	FSMState* pTpState{ new FSMState{
	[](Blackboard* pBlackboard, const FSMStateTransition stateTransition)
	{
		if (stateTransition == FSMStateTransition::OnEnter)
		{
			// left teleporter is active
			if (pBlackboard->GetData<TeleportationPadComponent*>("LeftTeleporter")->GetParent()->transform.GetPosition() == pBlackboard->GetData<GameObject*>("Qbert")->transform.GetPosition())
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

			}
			else if (pBlackboard->GetData<bool>("IsRightTeleporterActive"))
			{

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

	FiniteStateMachineComponent* pFSM{ new FiniteStateMachineComponent{pQbert, pStandingState, pNewBlackboard} };
	pFSM->AddTransition(pStandingState, pTpState, pToTeleporterTransition);
	pFSM->AddTransition(pTpState, pStandingState, pToStandingTransition);

	pQbert->AddComponent(pFSM);
	pQbert->transform.SetPosition(pPyramidComponent->GetTopTileCenter());

	AddGameObject("PyramidRoot", pPyramidRoot);
	AddGameObject("Qbert", pQbert);

	//pPyramidRoot->transform.SetScale(2.f, 2.f);
	//pQbert->transform.SetScale(2.f, 2.f);
}

void Qbert_MainGame::Render() const
{
	using namespace Integrian;

	//DrawFilledCircle(Circlef{ Point2f{336.f - 112.f, 174.f}, 3.f }, RGBColour{ 255.f, 0.f, 0.f });
	//DrawFilledCircle(Circlef{ Point2f{336.f + 112.f, 174.f}, 3.f }, RGBColour{ 255.f, 0.f, 0.f });
}

void Qbert_MainGame::LateUpdate(const float)
{
}
