#pragma once
#include <Component.h>

namespace Integrian
{
	class GameObject;
}

class BallSpawnerComponent final : public Integrian::Component
{
public:
	BallSpawnerComponent(Integrian::GameObject* pParent, const int maxAllowedPerScreen);
	
	virtual void Initialize() override;
	virtual void Update(const float dt) override;

private:
	int m_MaxAllowedBallsPerScreen;
	float m_SpawnTimer;
	float m_CurrentTime;
};

