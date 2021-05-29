#include "IntegrianPCH.h"
#include "AnimationComponent.h"
#include "Texture.h"
#include "GameObject.h"

Integrian::AnimationComponent::AnimationComponent(GameObject* pParent)
	: Component{ pParent }
	, m_pTexture{}
	, m_NrOfFrames{}
	, m_FramesPerSec{}
	, m_CurrentTime{}
	, m_FrameWidth{}
	, m_FrameHeight{}
	, m_CurrentFrame{}
{
}

Integrian::AnimationComponent::AnimationComponent(GameObject* pParent, const int nrOfFrames, const int framesPerSec, Texture* pTexture)
	: Component{ pParent }
	, m_pTexture{ pTexture }
	, m_NrOfFrames{ nrOfFrames }
	, m_FramesPerSec{ framesPerSec }
	, m_CurrentTime{}
	, m_FrameWidth{}
	, m_FrameHeight{}
	, m_CurrentFrame{}
{
}

Integrian::AnimationComponent::AnimationComponent(GameObject* pParent, const int nrOfFrames, const int framesPerSec, const float frameWidth, const float frameHeight, Texture* pTexture)
	: Component{ pParent }
	, m_pTexture{ pTexture }
	, m_NrOfFrames{ nrOfFrames }
	, m_FramesPerSec{ framesPerSec }
	, m_CurrentTime{}
	, m_FrameWidth{ frameWidth }
	, m_FrameHeight{ frameHeight }
	, m_CurrentFrame{}
{
}

void Integrian::AnimationComponent::Initialize()
{
	if (m_pTexture)
	{
		if (m_FrameWidth == 0.f)
			m_FrameWidth = m_pTexture->GetWidth() / m_NrOfFrames;

		if (m_FrameHeight == 0.f)
			m_FrameHeight = m_pTexture->GetHeight() / m_NrOfFrames;
	}
}

void Integrian::AnimationComponent::Update(const float elapsedSeconds)
{
	m_CurrentTime += elapsedSeconds;

	if (m_CurrentTime > 1.f / m_FramesPerSec)
	{
		++m_CurrentFrame% m_NrOfFrames;

		m_CurrentTime = 0.f;
	}
}

void Integrian::AnimationComponent::Render() const
{
	m_pTexture->Draw(m_pParent->transform.GetDestRect(), Rectf{ m_CurrentFrame * m_FrameWidth, 0.f, m_FrameWidth, m_FrameHeight });
}
