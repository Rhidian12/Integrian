#pragma once
#include <Component.h>
#include <string>
#include <ListenerInterface.h>
#include <Event.h>

namespace Integrian
{
	class GameObject;
	class Texture;
}

class QbertSpriteComponent final : public Integrian::Component, public Integrian::IListener
{
public:
	QbertSpriteComponent(Integrian::GameObject* pGameobject);

	virtual void Initialize() override;

	virtual void Update(const float) override;

	virtual void Render() const override;

	virtual bool OnEvent(const Integrian::Event& event) override;

private:
	Integrian::Texture* m_pTexture;
	Integrian::Rectf m_SourceRect;
};