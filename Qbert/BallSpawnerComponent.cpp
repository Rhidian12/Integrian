#include "BallSpawnerComponent.h"

BallSpawnerComponent::BallSpawnerComponent(Integrian::GameObject* pParent, const int maxAllowedPerScreen)
	: Component{ pParent }
	, m_MaxAllowedBallsPerScreen{ maxAllowedPerScreen }
	, m_SpawnTimer{ 1.5f }
	, m_CurrentTime{}
{
}

void BallSpawnerComponent::Initialize()
{

}

void BallSpawnerComponent::Update(const float dt)
{
	m_CurrentTime += dt;

	if (m_CurrentTime >= m_SpawnTimer)
	{

	}
}
