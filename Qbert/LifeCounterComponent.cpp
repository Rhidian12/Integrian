#include "LifeCounterComponent.h"

#include <App_Selector.h>
#include <GameObject.h>
#include <TextureComponent.h>
#include <Texture.h>
#include <EventQueue.h>

LifeCounterComponent::LifeCounterComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_Lives{ 3 }
	, m_pTextureComponent{}
{
	Integrian::EventQueue::GetInstance().AddListener(this);
}

void LifeCounterComponent::PostInitialize()
{
	m_pTextureComponent = m_pParent->GetComponentByType<Integrian::TextureComponent>();
}

void LifeCounterComponent::Update(const float)
{
	float height{ (m_pTextureComponent->GetTexture()->GetHeight() / 3.f) * m_Lives };
	if (height == 0.f)
		height = 0.1f;

	m_pTextureComponent->SetSourceRect(Integrian::Rectf{ 0.f, 0.f,
		m_pTextureComponent->GetTexture()->GetWidth(), height });
}

bool LifeCounterComponent::OnEvent(const Integrian::Event& event)
{
	const std::string& eventName{ event.GetEvent() };

	if (eventName == "QbertDeath")
	{
		--m_Lives;

		if (m_Lives < 0)
		{
			Integrian::EventQueue::GetInstance().QueueEvent(Integrian::Event{ "GameOver" });
		}

		return true;
	}

	if (eventName == "ResetGame")
	{
		m_Lives = 3;
		return true;
	}

	return false;
}
