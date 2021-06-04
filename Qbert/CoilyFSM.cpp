#include "CoilyFSM.h"
#include <Blackboard.h>
#include <FiniteStateMachine.h>
#include <TextureComponent.h>
#include <App.h>
#include <App_Selector.h>
#include "PyramidComponent.h"
#include <GameObject.h>
#include "TileComponent.h"
#include <Graph2D.h>
#include "QbertGraphComponent.h"
#include <queue>
#include <set>
#include <TextureComponent.h>
#include <Texture.h>
#include <TextureManager.h>
#include <EventQueue.h>

CoilyFSM::CoilyFSM(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pBlackboard{ new Integrian::Blackboard{} }
	, m_pQbert{}
	, m_pGraph{}
{
	Integrian::EventQueue::GetInstance().AddListener(this);
}

void CoilyFSM::PostInitialize()
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	m_pQbert = pActiveApp->GetGameObject("Qbert");
	m_pGraph = pActiveApp->GetGameObject("QbertGraph")->GetComponentByType<QbertGraphComponent>();

	PyramidComponent* pPyramid{ pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>() };

	const Point2f& tilePosition{ pPyramid->GetTiles()[1]->GetComponentByType<TileComponent>()->GetCenter() };
	m_pParent->transform.SetPosition(Point2f{ tilePosition.x, tilePosition.y + 50.f });

	m_pBlackboard->AddData("CoilySpeed", 50.f);
	m_pBlackboard->AddData("CoilyVelocity", Vector2f{});
	m_pBlackboard->AddData("Pyramid", pPyramid);
	m_pBlackboard->AddData("CoilyBallSprite", m_pParent->GetComponentByType<TextureComponent>());
	m_pBlackboard->AddData("EndPosition", Point2f{});
	m_pBlackboard->AddData("CoilyBallWaitTimer", 0.5f);
	m_pBlackboard->AddData("CoilyBallCurrentWaitTimer", 0.f);
	//pBlackboard->AddData("BeginPosition",)

	const std::vector<GameObject*>* const pTiles{ &m_pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTiles() };

	const Vector2f vectorTowardsOtherTile = { // vector towards right bottom
	(*pTiles)[0]->GetComponentByType<TileComponent>()->GetCenter(),
	(*pTiles)[2]->GetComponentByType<TileComponent>()->GetCenter() };

	const std::vector<GameObject*>::const_iterator cIt{ std::find_if(pTiles->cbegin(), pTiles->cend(), [this](GameObject* pA)
		{
			return pA->GetComponentByType<TileComponent>()->GetCenter().x == m_pParent->transform.GetPosition().x;
		}) };

	m_pBlackboard->AddData("FirstEndPosition", (*cIt)->GetComponentByType<TileComponent>()->GetCenter());
	m_pBlackboard->AddData("ReachedFirstEndPosition", false);
	m_pBlackboard->AddData("BallVelocity", Vector2f{});
	m_pBlackboard->AddData("EndPoint", Point2f{});
	m_pBlackboard->AddData("BallWaitTimer", 0.25f);
	m_pBlackboard->AddData("CurrentBallWaitTimer", 0.f);
	m_pBlackboard->AddData("ShouldReset", false);
	m_pBlackboard->AddData("ReachedEndOfPyramid", false);
	m_pBlackboard->AddData("CanMoveAgain", true);
	m_pBlackboard->AddData("CoilyWaitTimer", 0.3f);
	m_pBlackboard->AddData("CurrentCoilyWaitTimer", 0.f);

	std::shared_ptr<FSMState> pDropDownState{ new FSMState
		{
			[](Blackboard*, const FSMStateTransition) {},
			// Fixed Update
			[this](Blackboard* pBlackboard, const float dt)
			{
			// just drop straight down
			const Point2f initPosition{ m_pParent->transform.GetPosition() };
			const Vector2f speed{ Vector2f { 0.f, -1.f } *pBlackboard->GetData<float>("CoilySpeed") * dt };
			m_pParent->transform.SetPosition(initPosition + speed);
		},
		// Update
		[this](Blackboard* pBlackboard, const float)
		{
			const Point2f initPosition{ m_pParent->transform.GetPosition() };
			const Point2f endPosition{ pBlackboard->GetData<Point2f>("FirstEndPosition") };

			if (AreEqual(initPosition.x, endPosition.x, 1.f) && AreEqual(initPosition.y, endPosition.y, 1.f))
			{
				m_pParent->transform.SetPosition(endPosition);
				pBlackboard->ChangeData("ReachedFirstEndPosition", true);
			}
		}
	} };

	std::shared_ptr<FSMTransition> pToMoveStateTransition{ new FSMTransition{[](Blackboard* pBlackboard)->bool
		{
			if (pBlackboard->GetData<bool>("ReachedFirstEndPosition"))
			{
				pBlackboard->ChangeData("ReachedFirstEndPosition", false);
				return true;
			}
			else
				return false;
		}} };
	std::shared_ptr<FSMTransition> pToDropDownStateTransition{ new FSMTransition{[](Blackboard* pBlackboard)->bool
		{
			if (pBlackboard->GetData<bool>("ShouldReset"))
			{
				pBlackboard->ChangeData<bool>("ShouldReset", false);
				return true;
			}
			else
				return false;
		}} };

	std::shared_ptr<FSMState> pMoveDownPyramidState{ new FSMState{
	[this, vectorTowardsOtherTile](Blackboard* pBlackboard, const FSMStateTransition transition)
	{
		if (transition == FSMStateTransition::OnExit)
			return;

		const Point2f ballPosition{ m_pParent->transform.GetPosition() };
		TileComponent* const pBallTile{ pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTile(ballPosition) };

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
			// cannot move in general, so we're at the bottom of the pyramid and Coily needs to transform
			pBlackboard->ChangeData("ReachedEndOfPyramid", true);
		}
	},
		// Fixed Update
		[this](Blackboard* pBlackboard, const float dt)
		{
			const Integrian::Point2f initialPosition{ m_pParent->transform.GetPosition() };

			const Integrian::Vector2f speed{ pBlackboard->GetData<Vector2f>("BallVelocity") * dt * pBlackboard->GetData<float>("CoilySpeed") };

			m_pParent->transform.SetPosition(initialPosition + speed);
		},
		// Update
		[this, vectorTowardsOtherTile](Blackboard* pBlackboard, const float dt)
		{
			const Point2f endPosition{ pBlackboard->GetData<Point2f>("EndPoint") };
			if (AreEqual(m_pParent->transform.GetPosition().x, endPosition.x, 1.f) && AreEqual(m_pParent->transform.GetPosition().y, endPosition.y, 1.f))
			{
				m_pParent->transform.SetPosition(endPosition);
				pBlackboard->ChangeData("BallVelocity", Vector2f{});

				// Change sprite
				TextureComponent* pTextureComponent{ pBlackboard->GetData<TextureComponent*>("CoilyBallSprite") };
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

			const Point2f ballPosition{ m_pParent->transform.GetPosition() };
			TileComponent* const pBallTile{ pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTile(ballPosition) };

			assert(pBallTile != nullptr); // coily cant go off the pyramid

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
				// cannot move in general, so we're at the bottom of the pyramid and Coily needs to transform
				pBlackboard->ChangeData("ReachedEndOfPyramid", true);
			}

			// Change sprite
			TextureComponent* pTextureComponent{ pBlackboard->GetData<TextureComponent*>("CoilyBallSprite") };
			Rectf sourceRect{ pTextureComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x = sourceRect.width;
			pTextureComponent->SetSourceRect(sourceRect);
		}
		} };

	std::shared_ptr<FSMTransition> pToCoilyState{ new FSMTransition{
	[](Blackboard* pBlackboard)->bool
	{
		return pBlackboard->GetData<bool>("ReachedEndOfPyramid");
	}
	} };

	std::shared_ptr<FSMState> pCoilyState{ new FSMState{
	[this](Blackboard*, const FSMStateTransition) {},
	// fixed update
	[this](Blackboard* pBlackboard, const float dt)
	{
		const Integrian::Point2f initialPosition{ m_pParent->transform.GetPosition() };

		const Integrian::Vector2f speed{ pBlackboard->GetData<Vector2f>("CoilyVelocity") * dt * pBlackboard->GetData<float>("CoilySpeed") };

		m_pParent->transform.SetPosition(initialPosition + speed);
	},
		// Update
		[this](Blackboard* pBlackboard, const float dt)
		{
			const Point2f endPosition{ pBlackboard->GetData<Point2f>("EndPoint") };
			if (AreEqual(m_pParent->transform.GetPosition().x, endPosition.x, 1.f) && AreEqual(m_pParent->transform.GetPosition().y, endPosition.y, 1.f))
			{
				m_pParent->transform.SetPosition(endPosition);
				TextureComponent* pTextureComponent{ m_pParent->GetComponentByType<TextureComponent>() };

				pBlackboard->ChangeData("CoilyVelocity", Vector2f{});

				pTextureComponent->SetSourceRect(Rectf{ 0.f, 0.f,
					pTextureComponent->GetTexture()->GetWidth() / 2.f, pTextureComponent->GetTexture()->GetHeight() });

				pBlackboard->ChangeData("CurrentCoilyWaitTimer", pBlackboard->GetData<float>("CurrentCoilyWaitTimer") + dt);
				if (pBlackboard->GetData<float>("CurrentCoilyWaitTimer") >= pBlackboard->GetData<float>("CoilyWaitTimer"))
				{
					pBlackboard->ChangeData("CurrentCoilyWaitTimer", 0.f);
					pBlackboard->ChangeData("CanMoveAgain", true);
				}
			}

			if (!pBlackboard->GetData<bool>("CanMoveAgain"))
				return;

			PyramidComponent* pPyramid{ pBlackboard->GetData<PyramidComponent*>("Pyramid") };
			// do a Breadth First Search to find where tf Q*bert is

			const Point2f coilyPosition{ m_pParent->transform.GetPosition() };
			TileComponent* const pCoilyTile{ pPyramid->GetTile(coilyPosition) };

			const Point2f qbertPosition{ m_pQbert->transform.GetPosition() };
			TileComponent* const pQbertTile{ pPyramid->GetTile(qbertPosition) };

			if (!pQbertTile)
				return;

			std::vector<int> path{};
			BFS(path, pCoilyTile->GetIndex(), pQbertTile->GetIndex());

			const Point2f nextPosition{ m_pGraph->GetGraph()->GetNode(path[1])->GetPosition() };
			const Vector2f coilyVelocity{ GetNormalized(nextPosition - pCoilyTile->GetCenter()) };
			pBlackboard->ChangeData("EndPoint", nextPosition);
			pBlackboard->ChangeData("CanMoveAgain", false);
			pBlackboard->ChangeData("CoilyVelocity", coilyVelocity);

			// Change sprite
			TextureManager& textureManager{ TextureManager::GetInstance() };
			TextureComponent* pTextureComponent{ m_pParent->GetComponentByType<TextureComponent>() };

			if (coilyVelocity.x > 0.f && coilyVelocity.y > 0.f) // right top
				pTextureComponent->SetTexture(textureManager.GetTexture("CoilyRightTopAnimation"));
			else if (coilyVelocity.x > 0.f && coilyVelocity.y < 0.f) // right bottom
				pTextureComponent->SetTexture(textureManager.GetTexture("CoilyRightBottomAnimation"));
			else if (coilyVelocity.x < 0.f && coilyVelocity.y > 0.f) // left top
				pTextureComponent->SetTexture(textureManager.GetTexture("CoilyLeftTopAnimation"));
			else if (coilyVelocity.x < 0.f && coilyVelocity.y < 0.f) // left bottom
				pTextureComponent->SetTexture(textureManager.GetTexture("CoilyLeftBottomAnimation"));

			pTextureComponent->SetSourceRect(Rectf{ pTextureComponent->GetTexture()->GetWidth() / 2.f, 0.f,
				pTextureComponent->GetTexture()->GetWidth() / 2.f, pTextureComponent->GetTexture()->GetHeight() });
		}
		} };

	FiniteStateMachineComponent* pFSM{ new FiniteStateMachineComponent{m_pParent, pDropDownState, m_pBlackboard} };
	pFSM->AddTransition(pDropDownState, pMoveDownPyramidState, pToMoveStateTransition);
	pFSM->AddTransition(pMoveDownPyramidState, pDropDownState, pToDropDownStateTransition);
	pFSM->AddTransition(pMoveDownPyramidState, pCoilyState, pToCoilyState);
	pFSM->AddTransition(pCoilyState, pDropDownState, pToDropDownStateTransition);

	m_pParent->AddComponent(pFSM);
}

void CoilyFSM::Reset()
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	PyramidComponent* pPyramid{ pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>() };

	const Point2f& tilePosition{ pPyramid->GetTiles()[1]->GetComponentByType<TileComponent>()->GetCenter() };
	m_pBlackboard->ChangeData("ShouldReset", true);
	m_pBlackboard->ChangeData("ReachedFirstEndPosition", false);
	m_pBlackboard->ChangeData("BallVelocity", Vector2f{});
	m_pBlackboard->ChangeData("CoilyVelocity", Vector2f{});
	m_pBlackboard->ChangeData("ReachedEndOfPyramid", false);
	TextureComponent* pTextureComponent{ m_pParent->GetComponentByType<TextureComponent>() };
	pTextureComponent->SetTexture(TextureManager::GetInstance().GetTexture("CoilyBall"));
	pTextureComponent->SetSourceRect(Rectf{ 0.f, 0.f, pTextureComponent->GetTexture()->GetWidth() / 2.f, pTextureComponent->GetTexture()->GetHeight() });
	m_pParent->transform.SetPosition(Point2f{ tilePosition.x, tilePosition.y + 50.f });
}

bool CoilyFSM::OnEvent(const Integrian::Event& event)
{
	if (event.GetEvent() == "QbertDeath")
	{
		Reset();
		return true;
	}

	return false;
}

void CoilyFSM::BFS(std::vector<int>& path, int startNode, int wantedNode)
{
	using namespace Integrian;

	std::queue<int> openList;
	std::map<int, int> closedList;

	openList.push(startNode);

	while (!openList.empty())
	{
		int currentNode{ openList.front() };
		openList.pop();

		if (currentNode == wantedNode)
			break;

		for (GraphConnection2D* const pConnection : m_pGraph->GetGraph()->GetNodeConnections(currentNode))
		{
			int nextNode{ m_pGraph->GetGraph()->GetNode(pConnection->GetTo())->GetIndex() };
			if (closedList.find(nextNode) == closedList.end())
			{
				openList.push(nextNode);
				closedList[nextNode] = currentNode;
			}
		}
	}

	int currentNode{ wantedNode };

	while (currentNode != startNode)
	{
		path.push_back(currentNode);
		currentNode = closedList[currentNode];
	}

	path.push_back(startNode);
	std::reverse(path.begin(), path.end());
}
