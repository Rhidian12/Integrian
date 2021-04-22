#include "IntegrianPCH.h" // precompiled header
#include "TextureComponent.h" // header
#include "Texture.h" // texture

Integrian::TextureComponent::TextureComponent()
	: TextureComponent{ nullptr }
{
}

Integrian::TextureComponent::TextureComponent(Texture* pTexture)
	: m_pTexture{ pTexture }
{
}

void Integrian::TextureComponent::AddTexture(Texture* pTexture)
{
	m_pTexture = pTexture;
}

Integrian::Texture* Integrian::TextureComponent::GetTexture() const
{
	return m_pTexture;
}

void Integrian::TextureComponent::Render(const Point2f& pos) const
{
	m_pTexture->Draw(pos);
}
