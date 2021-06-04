#pragma once
#include <Component.h>
#include <ListenerInterface.h>

namespace Integrian
{
	class GameObject;
	class TextureComponent;
}

class LifeCounterComponent final : public Integrian::Component, public Integrian::IListener
{
public:
	LifeCounterComponent(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	virtual void Update(const float) override;

	virtual bool OnEvent(const Integrian::Event& event) override;

private:
	int m_Lives;
	Integrian::TextureComponent* m_pTextureComponent;
};