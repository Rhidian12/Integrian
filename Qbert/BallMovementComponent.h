#pragma once
#include <Component.h>

namespace Integrian
{
	class GameObject;
	class TextureComponent;
}

class PyramidComponent;
class BallMovementComponent final : public Integrian::Component
{
public:
	BallMovementComponent(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	virtual void Update(const float) override;
	virtual void FixedUpdate(const float dt) override;

private:
	bool HasBallReachedEndpoint() const noexcept;

	float m_Speed;
	Integrian::Vector2f m_Velocity;
	PyramidComponent* m_pPyramid;
	Integrian::TextureComponent* m_pSprite;
	Integrian::Vector2f m_VectorTowardsOtherTile;
	Integrian::Point2f m_EndPosition;
	float m_BallWaitTimer;
	float m_CurrentWaitTimer;
};