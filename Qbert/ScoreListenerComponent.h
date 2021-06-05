#pragma once
#include <Component.h>
#include <ListenerInterface.h>

namespace Integrian
{
	class GameObject;
	class TextComponent;
}

class ScoreListenerComponent final : public Integrian::Component, public Integrian::IListener
{
public:
	ScoreListenerComponent(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	virtual bool OnEvent(const Integrian::Event& event) override;

	static const int GetScore();
	static void SetScore(const int score);

private:
	Integrian::TextComponent* m_pTextComponent;
	inline static int m_Score{};
};