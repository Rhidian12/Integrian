#include "BallSpawnerComponent.h"
#include <GameObject.h>
#include "BallMovementComponent.h"
#include <TextureComponent.h>
#include <TextureManager.h>
#include <Texture.h>
#include <App_Selector.h>
#include <App.h>
#include <FiniteStateMachine.h>
#include <Blackboard.h>
#include "PyramidComponent.h"
#include "TileComponent.h"

BallSpawnerComponent::BallSpawnerComponent(Integrian::GameObject* pParent, const unsigned int maxAllowedPerScreen)
	: Component{ pParent }
	, m_MaxAllowedBallsPerScreen{ maxAllowedPerScreen }
	, m_SpawnTimer{ 2.5f }
	, m_CurrentTime{}
	, m_pBalls{}
{
}

void BallSpawnerComponent::PostInitialize()
{
	using namespace Integrian;

	TextureManager& textureManager{ TextureManager::GetInstance() };
	textureManager.AddTexture("Red Ball", "Resources/Images/Ball/Red_ball.png");

	App* const pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	PyramidComponent* const pPyramid{ pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>() };

	for (unsigned int i{}; i < m_MaxAllowedBallsPerScreen; ++i)
	{
		GameObject* pBall{ new GameObject{} };

		const Point2f tilePos{ pPyramid->GetTiles()[i + 1]->GetComponentByType<TileComponent>()->GetCenter() };
		pBall->transform.SetPosition(Point2f{ tilePos.x, tilePos.y + 20.f });

		pBall->AddComponent(new BallMovementComponent{ pBall });
		TextureComponent* pSprite{ new TextureComponent{ pBall, textureManager.GetTexture("Red Ball") } };
		pSprite->SetSourceRect(Rectf{ 0.f, 0.f, pSprite->GetTexture()->GetWidth() / 2.f, pSprite->GetTexture()->GetHeight() });
		pBall->AddComponent(pSprite);
		pBall->AddComponent(CreateBallFSM(pBall, pPyramid, pBall->transform.GetPosition(), pSprite));

		pActiveApp->AddGameObject("Red Ball_" + std::to_string(i), pBall);

		pBall->SetIsActive(false);

		m_pBalls.push_back(pBall);
	}
}

void BallSpawnerComponent::Update(const float dt)
{
	using namespace Integrian;

	m_CurrentTime += dt;

	if (m_CurrentTime >= m_SpawnTimer)
	{
		m_CurrentTime = 0.f;

		// spawn a ball
		for (GameObject* pBall : m_pBalls)
		{
			if (!pBall->GetIsActive())
			{
				pBall->SetIsActive(true);
				break;
			}
		}
	}
}

Integrian::FiniteStateMachineComponent* BallSpawnerComponent::CreateBallFSM(Integrian::GameObject* pParent, PyramidComponent* pPyramidComponent, const Integrian::Point2f& position, Integrian::TextureComponent* pTextureComponent) const noexcept
{
	using namespace Integrian;

	Blackboard* pFSMBlackboard{ new Blackboard{} };
	pFSMBlackboard->AddData("BallSpeed", 50.f);

	const std::vector<GameObject*>* const pTiles{ &pPyramidComponent->GetTiles() };

	const Vector2f vectorTowardsOtherTile = { // vector towards right bottom
	pPyramidComponent->GetTiles()[0]->GetComponentByType<TileComponent>()->GetCenter(),
	pPyramidComponent->GetTiles()[2]->GetComponentByType<TileComponent>()->GetCenter() };

	const std::vector<GameObject*>::const_iterator cIt{ std::find_if(pTiles->cbegin(), pTiles->cend(), [position](GameObject* pA)
		{
			return pA->GetComponentByType<TileComponent>()->GetCenter().x == position.x;
		}) };

	pFSMBlackboard->AddData("FirstEndPosition", (*cIt)->GetComponentByType<TileComponent>()->GetCenter());
	pFSMBlackboard->AddData("ReachedFirstEndPosition", false);
	pFSMBlackboard->AddData("BallVelocity", Vector2f{});
	pFSMBlackboard->AddData("EndPoint", Point2f{});
	pFSMBlackboard->AddData("BallWaitTimer", 0.5f);
	pFSMBlackboard->AddData("CurrentBallWaitTimer", 0.f);

	FSMState* pDropDownState{ new FSMState
		{
			[](Blackboard*, const FSMStateTransition) {},
			// Fixed Update
			[this, pParent](Blackboard* pBlackboard, const float dt)
			{
			// just drop straight down
			const Point2f initPosition{ pParent->transform.GetPosition() };
			const Vector2f speed{ Vector2f { 0.f, -1.f } *pBlackboard->GetData<float>("BallSpeed") * dt };
			pParent->transform.SetPosition(initPosition + speed);
		},
		// Update
		[this, pParent](Blackboard* pBlackboard, const float)
		{
			const Point2f initPosition{ pParent->transform.GetPosition() };
			const Point2f endPosition{ pBlackboard->GetData<Point2f>("FirstEndPosition") };

			if (AreEqual(initPosition.x, endPosition.x, 1.f) && AreEqual(initPosition.y, endPosition.y, 1.f))
			{
				pParent->transform.SetPosition(endPosition);
				pBlackboard->ChangeData("ReachedFirstEndPosition", true);
			}
		}
	} };

	FSMTransition* pToMoveStateTransition{ new FSMTransition{[](Blackboard* pBlackboard)->bool
		{
			return pBlackboard->GetData<bool>("ReachedFirstEndPosition");
		}} };

	FSMState* pMoveState{ new FSMState{
	[pParent, pPyramidComponent, vectorTowardsOtherTile](Blackboard* pBlackboard, const FSMStateTransition transition)
	{
		if (transition == FSMStateTransition::OnExit)
			return;

		const Point2f ballPosition{ pParent->transform.GetPosition() };
		TileComponent* const pBallTile{ pPyramidComponent->GetTile(ballPosition) };

		const std::variant leftBottomDirection{ pBallTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection };
		TileComponent* const pLeftTile{ std::holds_alternative<TileComponent*>(leftBottomDirection) ? std::get<0>(leftBottomDirection) : nullptr };

		const std::variant rightBottomDirection{ pBallTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection };
		TileComponent* const pRightTile{ std::holds_alternative<TileComponent*>(rightBottomDirection) ? std::get<0>(rightBottomDirection) : nullptr };

		if (pLeftTile && pRightTile)
		{
			// can move both left bottom and right bottom so take a random direction
			const int randomDirection{ rand() % 2 }; // 0 == left, 1 == right

			if (randomDirection == 0) // go left
			{
				pBlackboard->ChangeData("BallVelocity", GetNormalized(Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y }));
				pBlackboard->ChangeData("EndPoint", pLeftTile->GetCenter());
			}

			else // go right
			{
				pBlackboard->ChangeData("BallVelocity", GetNormalized(vectorTowardsOtherTile));
				pBlackboard->ChangeData("EndPoint", pRightTile->GetCenter());
			}
		}
		else if (pLeftTile && !pRightTile)
		{
			// can only move left, so move left
			pBlackboard->ChangeData("BallVelocity", GetNormalized(Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y }));
			pBlackboard->ChangeData("EndPoint", pLeftTile->GetCenter());
		}
		else if (!pLeftTile && pRightTile)
		{
			// can only move right, so move right
			pBlackboard->ChangeData("BallVelocity", GetNormalized(vectorTowardsOtherTile));
			pBlackboard->ChangeData("EndPoint", pRightTile->GetCenter());
		}
		else
		{
			// cannot move in general, so we're at the bottom of the pyramid and are going to die
			// do jump off the pyramid, we'll jump left cus I hate right
			pBlackboard->ChangeData("BallVelocity", GetNormalized(vectorTowardsOtherTile));
		}
	},
	// Fixed Update
	[this, pParent](Blackboard* pBlackboard, const float dt)
	{
		const Integrian::Point2f initialPosition{ pParent->transform.GetPosition() };

		const Integrian::Vector2f speed{ pBlackboard->GetData<Vector2f>("BallVelocity") * dt * pBlackboard->GetData<float>("BallSpeed") };

		pParent->transform.SetPosition(initialPosition + speed);
	},
	// Update
	[this, pTextureComponent, pPyramidComponent, vectorTowardsOtherTile, pParent, position](Blackboard* pBlackboard, const float dt)
	{
		const Point2f endPosition{ pBlackboard->GetData<Point2f>("EndPoint") };
		if (AreEqual(pParent->transform.GetPosition().x, endPosition.x, 1.f) && AreEqual(pParent->transform.GetPosition().y, endPosition.y, 1.f))
		{
			pParent->transform.SetPosition(endPosition);
			pBlackboard->ChangeData("BallVelocity", Vector2f{});

			// Change sprite
			Rectf sourceRect{ pTextureComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x = 0.f;
			pTextureComponent->SetSourceRect(sourceRect);

			pBlackboard->ChangeData("CurrentBallWaitTimer", pBlackboard->GetData<float>("CurrentBallWaitTimer") + dt);
			if (pBlackboard->GetData<float>("CurrentBallWaitTimer") >= pBlackboard->GetData<float>("BallWaitTimer"))
			{
				pBlackboard->ChangeData("CurrentBallWaitTimer", 0.f);
			}
			else
				return;
		}
		else
			return;

		const Point2f ballPosition{ pParent->transform.GetPosition() };
		TileComponent* const pBallTile{ pPyramidComponent->GetTile(ballPosition) };

		if (!pBallTile) // if we're not on a tile, it means we're from the pyramid and should be deleted
		{
			pParent->SetIsActive(false);
			pParent->transform.SetPosition(position);
		}

		const std::variant leftBottomDirection{ pBallTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection };
		TileComponent* const pLeftTile{ std::holds_alternative<TileComponent*>(leftBottomDirection) ? std::get<0>(leftBottomDirection) : nullptr };

		const std::variant rightBottomDirection{ pBallTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection };
		TileComponent* const pRightTile{ std::holds_alternative<TileComponent*>(rightBottomDirection) ? std::get<0>(rightBottomDirection) : nullptr };

		if (pLeftTile && pRightTile)
		{
			// can move both left bottom and right bottom so take a random direction
			const int randomDirection{ rand() % 2 }; // 0 == left, 1 == right

			if (randomDirection == 0) // go left
			{
				pBlackboard->ChangeData("BallVelocity", GetNormalized(Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y }));
				pBlackboard->ChangeData("EndPoint", pLeftTile->GetCenter());
			}

			else // go right
			{
				pBlackboard->ChangeData("BallVelocity", GetNormalized(vectorTowardsOtherTile));
				pBlackboard->ChangeData("EndPoint", pRightTile->GetCenter());
			}
		}
		else if (pLeftTile && !pRightTile)
		{
			// can only move left, so move left
			pBlackboard->ChangeData("BallVelocity", GetNormalized(Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y }));
			pBlackboard->ChangeData("EndPoint", pLeftTile->GetCenter());
		}
		else if (!pLeftTile && pRightTile)
		{
			// can only move right, so move right
			pBlackboard->ChangeData("BallVelocity", GetNormalized(vectorTowardsOtherTile));
			pBlackboard->ChangeData("EndPoint", pRightTile->GetCenter());
		}
		else
		{
			// cannot move in general, so we're at the bottom of the pyramid and are going to die
			// do jump off the pyramid, we'll jump left cus I hate right
			pBlackboard->ChangeData("BallVelocity", GetNormalized(vectorTowardsOtherTile));
		}

		// Change sprite
		Rectf sourceRect{ pTextureComponent->GetSourceRect() };
		sourceRect[VertexLocation::LeftBottom].x = sourceRect.width * 0.5f;
		pTextureComponent->SetSourceRect(sourceRect);
	}
	} };

	FiniteStateMachineComponent* pFSM{ new FiniteStateMachineComponent{pParent, pDropDownState, pFSMBlackboard} };
	pFSM->AddTransition(pDropDownState, pMoveState, pToMoveStateTransition);

	return pFSM;
}
