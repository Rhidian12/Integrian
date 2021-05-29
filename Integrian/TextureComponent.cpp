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
	, m_DrawMode{ DrawMode::LeftBottomCorner }
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

void Integrian::TextureComponent::SetDrawMode(const DrawMode drawMode)
{
	m_DrawMode = drawMode;
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
	m_TextureWidth = m_pTexture->GetWidth();
	m_TextureHeight = m_pTexture->GetHeight();
	m_SourceRect = Rectf{ 0.f, 0.f,m_TextureWidth, m_TextureHeight };
}

void Integrian::TextureComponent::Render() const
{
	switch (m_DrawMode)
	{
	case DrawMode::LeftBottomCorner:
		m_pTexture->Draw(m_pParent->transform.GetDestRect(), m_SourceRect);
		break;
	case DrawMode::Center:
	{
		Rectf destRect{ m_pParent->transform.GetDestRect() };
		destRect[VertexLocation::LeftBottom].x += m_TextureWidth * 0.5f;
		m_pTexture->Draw(destRect, m_SourceRect);
	}
	break;
	default:
		break;
	}
}
