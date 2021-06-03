#pragma once
#include <Component.h>
#include <ListenerInterface.h>
#include <vector>

namespace Integrian
{
	class GameObject;
	class TextureComponent;
}

class ButtonComponent;

class ButtonHandlerComponent final : public Integrian::Component, public Integrian::IListener
{
public:
	ButtonHandlerComponent(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	virtual void Update(const float) override;

	virtual bool OnEvent(const Integrian::Event& event) override;

private:
	std::vector<ButtonComponent*> m_pButtons;
	Integrian::TextureComponent* m_pTextureComponent;
};

