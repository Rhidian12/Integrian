#include "IntegrianPCH.h" // precompiled header
#include "TextureComponent.h" // header
#include "Texture.h" // texture
#include "GameObject.h"

Integrian::TextureComponent::TextureComponent(GameObject* pParent)
	: TextureComponent{ pParent, nullptr }
{
}

Integrian::TextureComponent::TextureComponent(GameObject* pParent, Texture* pTexture)
	: Component{ pParent }
	, m_pTexture{ pTexture }
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

void Integrian::TextureComponent::Initialize()
{
	m_pParent->transform.SetSourceRect(Rectf{ 0.f, 0.f, m_pTexture->GetWidth(), m_pTexture->GetHeight() });
}

void Integrian::TextureComponent::Render(const Point2f& pos) const
{
	m_pTexture->Draw(pos);
}
