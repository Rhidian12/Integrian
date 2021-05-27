#include "QbertSpriteComponent.h"
#include <Texture.h>
#include <TextureManager.h>
#include <GameObject.h>

QbertSpriteComponent::QbertSpriteComponent(Integrian::GameObject* pGameobject, const std::string& filepath)
	: Component{ pGameobject }
	, m_pTexture{}
	, m_Filepath{ filepath }
	, m_SourceRect{}
{
}

void QbertSpriteComponent::Initialize()
{
	Integrian::TextureManager::GetInstance().AddTexture("QbertLeftBottomAnimation", m_Filepath);
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

void QbertSpriteComponent::Render(const Integrian::Point2f& pos) const
{
	m_pTexture->Draw(Integrian::Point2f{ pos.x - m_pTexture->GetWidth() * 0.25f, pos.y }, m_SourceRect);
}

bool QbertSpriteComponent::OnEvent(const Integrian::Event& event)
{
	const std::string& eventName{ event.GetEvent() };

	if (eventName == "QbertMoveLeftBottom")
	{
		m_pTexture = Integrian::TextureManager::GetInstance().GetTexture("QbertLeftBottomAnimation");
		const Integrian::Rectf sourceRect{
			m_pTexture->GetWidth() / 2.f,
			0.f, m_pTexture->GetWidth() / 2.f,
			m_pTexture->GetHeight() };

		return true;
	}

	if (eventName == "QbertMoveRightBottom")
	{
		m_pTexture = Integrian::TextureManager::GetInstance().GetTexture("QbertLeftBottomAnimation");
		const Integrian::Rectf sourceRect{
			m_pTexture->GetWidth() / 2.f,
			0.f, m_pTexture->GetWidth() / 2.f,
			m_pTexture->GetHeight() };

		return true;
	}

	if (eventName == "QbertMoveLeftBottom")
	{
		m_pTexture = Integrian::TextureManager::GetInstance().GetTexture("QbertLeftBottomAnimation");
		const Integrian::Rectf sourceRect{
			m_pTexture->GetWidth() / 2.f,
			0.f, m_pTexture->GetWidth() / 2.f,
			m_pTexture->GetHeight() };

		return true;
	}

	if (eventName == "QbertMoveLeftBottom")
	{
		m_pTexture = Integrian::TextureManager::GetInstance().GetTexture("QbertLeftBottomAnimation");
		const Integrian::Rectf sourceRect{
			m_pTexture->GetWidth() / 2.f,
			0.f, m_pTexture->GetWidth() / 2.f,
			m_pTexture->GetHeight() };

		return true;
	}

	return false;
}
