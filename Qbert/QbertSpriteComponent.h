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
	QbertSpriteComponent(Integrian::GameObject* pGameobject, const std::string& filepath);

	virtual void Initialize() override;

	virtual void Update(const float) override;

	virtual void Render(const Integrian::Point2f&) const override;

private:
	Integrian::Texture* m_pTexture;
	std::string m_Filepath;
	Integrian::Rectf m_SourceRect;
};