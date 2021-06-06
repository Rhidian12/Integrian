#include "SlickSpawnerComponent.h"

#include <TextureManager.h>
#include <App.h>
#include <App_Selector.h>
#include <TextureComponent.h>
#include <Texture.h>
#include <Blackboard.h>
#include <EventQueue.h>
#include <FiniteStateMachine.h>

#include "PyramidComponent.h"
#include "TileComponent.h"

SlickSpawnerComponent::SlickSpawnerComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_CurrentTime{}
	, m_WaitTimer{ 10.f }
{
}

void SlickSpawnerComponent::PostInitialize()
{
	using namespace Integrian;

	TextureManager& textureManager{ TextureManager::GetInstance() };
	textureManager.AddTexture("Slick Left", "Resources/Images/Slick and Sam/Slick_Left.png");
	textureManager.AddTexture("Sam Right", "Resources/Images/Slick and Sam/Sam_Right.png");

	App* const pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	PyramidComponent* const pPyramid{ pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>() };

	GameObject* pSlick{ new GameObject{} };
	pSlick->SetTag("Green");
	pSlick->SetIsActive(false);

	pSlick->transform.SetPosition(pPyramid->GetTopTileCenter());

	TextureComponent* pSlickTextureComponent{ new TextureComponent{pSlick, textureManager.GetTexture("Slick Left")} };
	pSlickTextureComponent->SetSourceRect(Rectf{ 0.f, 0.f, textureManager.GetTexture("Slick Left")->GetWidth() / 2.f,textureManager.GetTexture("Slick Left")->GetHeight() });
	pSlick->AddComponent(pSlickTextureComponent);
	pSlick->AddComponent(CreateSlickFiniteStateMachine(pSlick));

	pActiveApp->AddGameObject("Slick", pSlick);

	GameObject* pSam{ new GameObject{} };
	pSam->SetTag("Green");
	pSam->SetIsActive(false);

	pSam->transform.SetPosition(pPyramid->GetTopTileCenter());

	TextureComponent* pSamTextureComponent{ new TextureComponent{pSam, textureManager.GetTexture("Sam Right")} };
	pSamTextureComponent->SetSourceRect(Rectf{ 0.f, 0.f, textureManager.GetTexture("Sam Right")->GetWidth() / 2.f,textureManager.GetTexture("Sam Right")->GetHeight() });
	pSam->AddComponent(pSamTextureComponent);
	pSam->AddComponent(CreateSamFiniteStateMachine(pSam));

	pActiveApp->AddGameObject("Sam", pSam);

	m_pSlickAndSam.push_back(pSlick);
	m_pSlickAndSam.push_back(pSam);
}

void SlickSpawnerComponent::Update(const float dt)
{
	using namespace Integrian;

	m_CurrentTime += dt;

	if (m_CurrentTime >= m_WaitTimer)
	{
		m_CurrentTime = 0.f;

		// spawn slick or sam
		for (GameObject* pS : m_pSlickAndSam)
		{
			if (!pS->GetIsActive())
			{
				pS->SetIsActive(true);
				break;
			}
		}
	}

	if (m_pSlickAndSam[0]->GetIsActive() || m_pSlickAndSam[1]->GetIsActive())
	{
		auto temp{ m_pSlickAndSam[0] };
		m_pSlickAndSam[0] = m_pSlickAndSam[1];
		m_pSlickAndSam[1] = temp;
	}
}

Integrian::FiniteStateMachineComponent* SlickSpawnerComponent::CreateSlickFiniteStateMachine(Integrian::GameObject* pParent) const
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };
	PyramidComponent* pPyramid{ pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>() };

	const std::vector<GameObject*>* const pTiles{ &pPyramid->GetTiles() };

	const Vector2f vectorTowardsOtherTile = { // vector towards right bottom
	(*pTiles)[0]->GetComponentByType<TileComponent>()->GetCenter(),
	(*pTiles)[2]->GetComponentByType<TileComponent>()->GetCenter() };

	Blackboard* pBlackboard{ new Blackboard{} };
	pBlackboard->AddData("Pyramid", pPyramid);
	pBlackboard->AddData("Velocity", GetNormalized(Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y }));
	pBlackboard->AddData("EndPoint", pParent->transform.GetPosition() + Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y });
	pBlackboard->AddData("Speed", 45.f);
	pBlackboard->AddData("Sprite", pParent->GetComponentByType<TextureComponent>());
	pBlackboard->AddData("CurrentTimer", 0.f);
	pBlackboard->AddData("Timer", 0.4f);
	pBlackboard->AddData("ShouldReset", false);

	std::shared_ptr<FSMState> pResetState{ new FSMState{} };
	std::shared_ptr<FSMTransition> pToResetState{ new FSMTransition{
	[](Blackboard* pBlackboard)->bool
		{
			if (pBlackboard->GetData<bool>("ShouldReset"))
			{
				pBlackboard->ChangeData("ShouldReset", false);
				return true;
			}
			return false;
		}} };
	std::shared_ptr<FSMTransition> pToMoveState{ new FSMTransition{
	[pParent](Blackboard*)->bool
		{
			return pParent->GetIsActive();
		}} };

	std::shared_ptr<FSMState> pMoveDownPyramidState{ new FSMState{
	[pParent, vectorTowardsOtherTile](Blackboard* pBlackboard, const FSMStateTransition transition)
	{
		if (transition == FSMStateTransition::OnExit)
			return;

		const Point2f position{ pParent->transform.GetPosition() };
		TileComponent* const pSTile{ pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTile(position) };

		const std::variant leftBottomDirection{ pSTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection };
		TileComponent* const pLeftTile{ std::holds_alternative<TileComponent*>(leftBottomDirection) ? std::get<0>(leftBottomDirection) : nullptr };

		if (pLeftTile)
		{
			// can only move left, so move left
			pBlackboard->ChangeData("Velocity", GetNormalized(Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y }));
			pBlackboard->ChangeData("EndPoint", pLeftTile->GetCenter());
		}
		else
		{
			// cannot move in general, so we're at the bottom of the pyramid and need to jump off
			pBlackboard->ChangeData("Velocity", GetNormalized(Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y }));
			pBlackboard->ChangeData("EndPoint", pParent->transform.GetPosition() + Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y });
		}
	},
		// Fixed Update
		[pParent](Blackboard* pBlackboard, const float dt)
		{
			const Integrian::Point2f initialPosition{ pParent->transform.GetPosition() };

			const Integrian::Vector2f speed{ pBlackboard->GetData<Vector2f>("Velocity") * dt * pBlackboard->GetData<float>("Speed") };

			pParent->transform.SetPosition(initialPosition + speed);
		},
		// Update
		[pParent, vectorTowardsOtherTile](Blackboard* pBlackboard, const float dt)
		{
			const Point2f endPosition{ pBlackboard->GetData<Point2f>("EndPoint") };
			if (AreEqual(pParent->transform.GetPosition().x, endPosition.x, 1.f) && AreEqual(pParent->transform.GetPosition().y, endPosition.y, 1.f))
			{
				pParent->transform.SetPosition(endPosition);
				pBlackboard->ChangeData("Velocity", Vector2f{});

				// Change sprite
				TextureComponent* pTextureComponent{ pBlackboard->GetData<TextureComponent*>("Sprite") };
				Rectf sourceRect{ pTextureComponent->GetSourceRect() };
				sourceRect[VertexLocation::LeftBottom].x = 0.f;
				pTextureComponent->SetSourceRect(sourceRect);

				pBlackboard->ChangeData("CurrentTimer", pBlackboard->GetData<float>("CurrentTimer") + dt);
				if (pBlackboard->GetData<float>("CurrentTimer") >= pBlackboard->GetData<float>("Timer"))
				{
					pBlackboard->ChangeData("CurrentTimer", 0.f);
				}
				else
					return;
			}
			else
				return;

			const Point2f position{ pParent->transform.GetPosition() };
			TileComponent* const pCurrentTile{ pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTile(position) };

			if (!pCurrentTile)
			{
				// we're off the pyramid, so deactivate
				pParent->SetIsActive(false);
				pParent->transform.SetPosition(pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTopTileCenter());
				pBlackboard->ChangeData("EndPoint", pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTopTileCenter());
				pBlackboard->ChangeData("ShouldReset", true);
				return;
			}

			EventQueue::GetInstance().QueueEvent(Event{ "ChangeTileBack", pCurrentTile });

			const std::variant leftBottomDirection{ pCurrentTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection };
			TileComponent* const pLeftTile{ std::holds_alternative<TileComponent*>(leftBottomDirection) ? std::get<0>(leftBottomDirection) : nullptr };

			if (pLeftTile)
			{
				// can only move left, so move left
				pBlackboard->ChangeData("Velocity", GetNormalized(Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y }));
				pBlackboard->ChangeData("EndPoint", pLeftTile->GetCenter());
			}
			else
			{
				// cannot move in general, so we're at the bottom of the pyramid and need to jump off
				pBlackboard->ChangeData("Velocity", GetNormalized(Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y }));
				pBlackboard->ChangeData("EndPoint", pParent->transform.GetPosition() + Vector2f{ -vectorTowardsOtherTile.x, vectorTowardsOtherTile.y });
			}

			// Change sprite
			TextureComponent* pTextureComponent{ pBlackboard->GetData<TextureComponent*>("Sprite") };
			Rectf sourceRect{ pTextureComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x = sourceRect.width;
			pTextureComponent->SetSourceRect(sourceRect);
		}
		} };

	FiniteStateMachineComponent* pFSM{ new FiniteStateMachineComponent{pParent, pMoveDownPyramidState, pBlackboard} };
	pFSM->AddTransition(pMoveDownPyramidState, pResetState, pToResetState);
	pFSM->AddTransition(pResetState, pMoveDownPyramidState, pToMoveState);

	return pFSM;
}

Integrian::FiniteStateMachineComponent* SlickSpawnerComponent::CreateSamFiniteStateMachine(Integrian::GameObject* pParent) const
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };
	PyramidComponent* pPyramid{ pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>() };

	const std::vector<GameObject*>* const pTiles{ &pPyramid->GetTiles() };

	const Vector2f vectorTowardsOtherTile = { // vector towards right bottom
	(*pTiles)[0]->GetComponentByType<TileComponent>()->GetCenter(),
	(*pTiles)[2]->GetComponentByType<TileComponent>()->GetCenter() };

	Blackboard* pBlackboard{ new Blackboard{} };
	pBlackboard->AddData("Pyramid", pPyramid);
	pBlackboard->AddData("Velocity", GetNormalized(vectorTowardsOtherTile));
	pBlackboard->AddData("EndPoint", pParent->transform.GetPosition() + vectorTowardsOtherTile);
	pBlackboard->AddData("Speed", 45.f);
	pBlackboard->AddData("Sprite", pParent->GetComponentByType<TextureComponent>());
	pBlackboard->AddData("CurrentTimer", 0.f);
	pBlackboard->AddData("Timer", 0.4f);
	pBlackboard->AddData("ShouldReset", false);

	std::shared_ptr<FSMState> pResetState{ new FSMState{} };
	std::shared_ptr<FSMTransition> pToResetState{ new FSMTransition{
	[](Blackboard* pBlackboard)->bool
		{
			if (pBlackboard->GetData<bool>("ShouldReset"))
			{
				pBlackboard->ChangeData("ShouldReset", false);
				return true;
			}
			return false;
		}} };
	std::shared_ptr<FSMTransition> pToMoveState{ new FSMTransition{
	[pParent](Blackboard*)->bool
		{
			return pParent->GetIsActive();
		}} };

	std::shared_ptr<FSMState> pMoveDownPyramidState{ new FSMState{
	[pParent, vectorTowardsOtherTile](Blackboard* pBlackboard, const FSMStateTransition transition)
	{
		if (transition == FSMStateTransition::OnExit)
			return;

		const Point2f position{ pParent->transform.GetPosition() };
		TileComponent* const pSTile{ pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTile(position) };

		const std::variant rightBottomDirection{ pSTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection };
		TileComponent* const pRightTile{ std::holds_alternative<TileComponent*>(rightBottomDirection) ? std::get<0>(rightBottomDirection) : nullptr };

		if (pRightTile)
		{
			// can only move left, so move left
			pBlackboard->ChangeData("Velocity", GetNormalized(vectorTowardsOtherTile));
			pBlackboard->ChangeData("EndPoint", pRightTile->GetCenter());
		}
		else
		{
			// cannot move in general, so we're at the bottom of the pyramid and need to jump off
			pBlackboard->ChangeData("Velocity", GetNormalized(vectorTowardsOtherTile));
			pBlackboard->ChangeData("EndPoint", pParent->transform.GetPosition() + vectorTowardsOtherTile);
		}
	},
		// Fixed Update
		[pParent](Blackboard* pBlackboard, const float dt)
		{
			const Integrian::Point2f initialPosition{ pParent->transform.GetPosition() };

			const Integrian::Vector2f speed{ pBlackboard->GetData<Vector2f>("Velocity") * dt * pBlackboard->GetData<float>("Speed") };

			pParent->transform.SetPosition(initialPosition + speed);
		},
		// Update
		[pParent, vectorTowardsOtherTile](Blackboard* pBlackboard, const float dt)
		{
			const Point2f endPosition{ pBlackboard->GetData<Point2f>("EndPoint") };
			if (AreEqual(pParent->transform.GetPosition().x, endPosition.x, 1.f) && AreEqual(pParent->transform.GetPosition().y, endPosition.y, 1.f))
			{
				pParent->transform.SetPosition(endPosition);
				pBlackboard->ChangeData("Velocity", Vector2f{});

				// Change sprite
				TextureComponent* pTextureComponent{ pBlackboard->GetData<TextureComponent*>("Sprite") };
				Rectf sourceRect{ pTextureComponent->GetSourceRect() };
				sourceRect[VertexLocation::LeftBottom].x = 0.f;
				pTextureComponent->SetSourceRect(sourceRect);

				pBlackboard->ChangeData("CurrentTimer", pBlackboard->GetData<float>("CurrentTimer") + dt);
				if (pBlackboard->GetData<float>("CurrentTimer") >= pBlackboard->GetData<float>("Timer"))
				{
					pBlackboard->ChangeData("CurrentTimer", 0.f);
				}
				else
					return;
			}
			else
				return;

			const Point2f position{ pParent->transform.GetPosition() };
			TileComponent* const pCurrentTile{ pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTile(position) };

			if (!pCurrentTile)
			{
				// we're off the pyramid, so deactivate
				pParent->SetIsActive(false);
				pParent->transform.SetPosition(pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTopTileCenter());
				pBlackboard->ChangeData("EndPoint", pBlackboard->GetData<PyramidComponent*>("Pyramid")->GetTopTileCenter());
				pBlackboard->ChangeData("ShouldReset", true);
				return;
			}

			EventQueue::GetInstance().QueueEvent(Event{ "ChangeTileBack", pCurrentTile });

			const std::variant rightBottomDirection{ pCurrentTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection };
			TileComponent* const pRightTile{ std::holds_alternative<TileComponent*>(rightBottomDirection) ? std::get<0>(rightBottomDirection) : nullptr };

			if (pRightTile)
			{
				// can only move right, so move right
				pBlackboard->ChangeData("Velocity", GetNormalized(vectorTowardsOtherTile));
				pBlackboard->ChangeData("EndPoint", pRightTile->GetCenter());
			}
			else
			{
				// cannot move in general, so we're at the bottom of the pyramid and need to jump off
				pBlackboard->ChangeData("Velocity", GetNormalized(vectorTowardsOtherTile));
				pBlackboard->ChangeData("EndPoint", pParent->transform.GetPosition() + vectorTowardsOtherTile);
			}

			// Change sprite
			TextureComponent* pTextureComponent{ pBlackboard->GetData<TextureComponent*>("Sprite") };
			Rectf sourceRect{ pTextureComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x = sourceRect.width;
			pTextureComponent->SetSourceRect(sourceRect);
		}
		} };

	FiniteStateMachineComponent* pFSM{ new FiniteStateMachineComponent{pParent, pMoveDownPyramidState, pBlackboard} };
	pFSM->AddTransition(pMoveDownPyramidState, pResetState, pToResetState);
	pFSM->AddTransition(pResetState, pMoveDownPyramidState, pToMoveState);

	return pFSM;
}
