#pragma once
#include <Component.h>

namespace Integrian
{
	class GameObject;
}

class QbertSpriteComponent;
class PyramidComponent;

class QbertMovementComponent final : public Integrian::Component
{
public:
	QbertMovementComponent(Integrian::GameObject* pParent, const uint8_t index = 0);

	virtual void PostInitialize() override;

	virtual void Update(const float) override;
	virtual void FixedUpdate(const float elapsedSeconds) override;

private:
	PyramidComponent* m_pPyramidComponent;
	QbertSpriteComponent* m_pSpriteComponent;
	Integrian::Vector2f m_VectorTowardsOtherTile;
	Integrian::Vector2f m_Velocity;
	Integrian::Point2f m_EndPosition;
	float m_Speed;
	uint8_t m_Index;
	bool m_CanMoveAgain;
};