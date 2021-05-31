#pragma once
#include <Component.h> // Integrian::Component
#include <vector> // std::vector

namespace Integrian
{
	class GameObject;
	class TextureComponent;
	class FiniteStateMachineComponent;
}

class PyramidComponent;
class BallSpawnerComponent final : public Integrian::Component
{
public:
	BallSpawnerComponent(Integrian::GameObject* pParent, const unsigned int maxAllowedPerScreen);
	
	virtual void PostInitialize() override;
	virtual void Update(const float dt) override;

private:
	Integrian::FiniteStateMachineComponent* CreateBallFSM(Integrian::GameObject* pParent, PyramidComponent* pPyramidComponent, const Integrian::Point2f& position, Integrian::TextureComponent* pTextureComponent) const noexcept;

	unsigned int m_MaxAllowedBallsPerScreen;
	float m_SpawnTimer;
	float m_CurrentTime;

	std::vector<Integrian::GameObject*> m_pBalls;
};

