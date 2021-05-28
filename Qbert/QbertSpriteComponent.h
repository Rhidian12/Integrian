#pragma once
#include <Component.h>
#include <string>

namespace Integrian
{
	class GameObject;
	class Texture;
}

class QbertSpriteComponent final : public Integrian::Component
{
public:
	QbertSpriteComponent(Integrian::GameObject* pGameobject);

	virtual void Initialize() override;

	virtual void Update(const float) override;

	virtual void Render() const override;

	Integrian::Texture* GetTexture() const noexcept;
	const Integrian::Rectf& GetSourceRect() const noexcept;

	void SetSourceRect(const Integrian::Rectf& sourceRect);
	void SetTexture(Integrian::Texture* pTexture);

private:
	Integrian::Texture* m_pTexture;
	Integrian::Rectf m_SourceRect;
};