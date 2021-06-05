#pragma once
#include <Component.h>
#include <ListenerInterface.h>

namespace Integrian
{
	class GameObject;
}

class TeleportationPadComponent final : public Integrian::Component, public Integrian::IListener
{
public:
	TeleportationPadComponent(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	virtual void Update(const float elapsedSeconds) override;
	void Activate();
	bool IsCompletelyDone() const;

	virtual bool OnEvent(const Integrian::Event& event) override;

private:
	void ResetGame();

	Integrian::GameObject* m_pQbert;
	Integrian::Point2f m_EndPosition;
	bool m_IsActivated;
	float m_Speed;
	bool m_IsQbertDroppedOff;
	bool m_CompletelyDone;
	Integrian::Point2f m_StartPosition;
};