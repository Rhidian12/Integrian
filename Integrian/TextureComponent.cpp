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
	, m_SourceRect{}
	, m_TextureWidth{}
	, m_TextureHeight{}
{
}

void Integrian::TextureComponent::SetTexture(Texture* pTexture)
{
	m_pTexture = pTexture;
	m_TextureWidth = pTexture->GetWidth();
	m_TextureHeight = pTexture->GetHeight();
	m_SourceRect = Rectf{ 0.f, 0.f, m_TextureWidth, m_TextureHeight };
}

void Integrian::TextureComponent::SetSourceRect(const Rectf& sourceRect)
{
	m_SourceRect = sourceRect;
}

const Integrian::Rectf& Integrian::TextureComponent::GetSourceRect() const noexcept
{
	return m_SourceRect;
}

Integrian::Texture* Integrian::TextureComponent::GetTexture() const
{
	return m_pTexture;
}

void Integrian::TextureComponent::Initialize()
{
	if (m_SourceRect != Rectf{})
		return;

	m_TextureWidth = m_pTexture->GetWidth();
	m_TextureHeight = m_pTexture->GetHeight();
	m_SourceRect = Rectf{ 0.f, 0.f,m_TextureWidth, m_TextureHeight };
}

void Integrian::TextureComponent::Render() const
{
	m_pTexture->Draw(m_pParent->transform.GetDestRect(), m_SourceRect);
}
