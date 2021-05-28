#include "QbertSpriteComponent.h"
#include <Texture.h>
#include <TextureManager.h>
#include <GameObject.h>
#include <EventQueue.h>

QbertSpriteComponent::QbertSpriteComponent(Integrian::GameObject* pGameobject)
	: Component{ pGameobject }
	, m_pTexture{}
	, m_SourceRect{}
{
}

void QbertSpriteComponent::Initialize()
{
	Integrian::TextureManager::GetInstance().AddTexture("QbertLeftBottomAnimation", "Resources/Images/Qbert/QbertLeftBottomAnimation.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertLeftTopAnimation", "Resources/Images/Qbert/QbertLeftTopAnimation.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertRightBottomAnimation", "Resources/Images/Qbert/QbertRightBottomAnimation.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertRightTopAnimation", "Resources/Images/Qbert/QbertRightTopAnimation.png");

	m_pTexture = Integrian::TextureManager::GetInstance().GetTexture("QbertLeftBottomAnimation");

	const Integrian::Rectf sourceRect{
		0.f, 0.f,
		m_pTexture->GetWidth() / 2.f,
		m_pTexture->GetHeight()
	};
	m_SourceRect = sourceRect;
}

void QbertSpriteComponent::Update(const float)
{
}

void QbertSpriteComponent::Render() const
{
	m_pTexture->Draw(Integrian::Point2f{ m_pParent->transform.GetPosition().x - m_pTexture->GetWidth() * 0.25f, m_pParent->transform.GetPosition().y }, m_SourceRect);
}

Integrian::Texture* QbertSpriteComponent::GetTexture() const noexcept
{
	return m_pTexture;
}

const Integrian::Rectf& QbertSpriteComponent::GetSourceRect() const noexcept
{
	return m_SourceRect;
}

void QbertSpriteComponent::SetSourceRect(const Integrian::Rectf& sourceRect)
{
	m_SourceRect = sourceRect;
}

void QbertSpriteComponent::SetTexture(Integrian::Texture* pTexture)
{
	m_pTexture = pTexture;
}
