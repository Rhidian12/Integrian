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
	m_pTextureComponent->SetSourceRect(Integrian::Rectf{ 0.f, 0.f,
		m_pTextureComponent->GetTexture()->GetWidth(), (m_pTextureComponent->GetTexture()->GetHeight() / 3.f) * m_Lives });
}

bool LifeCounterComponent::OnEvent(const Integrian::Event& event)
{
	if (event.GetEvent() == "QbertDeath")
	{
		std::cout <<"?????" << std::endl;
		m_Lives = m_Lives - 1;

		if (m_Lives < 0)
		{
			Integrian::App_Selector::GetInstance().SetActiveApplication("EndScreen");
		}

		return true;
	}
	return false;
}