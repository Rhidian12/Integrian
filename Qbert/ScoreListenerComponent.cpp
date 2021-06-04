#include "ScoreListenerComponent.h"

#include <TextComponent.h>
#include <GameObject.h>
#include <EventQueue.h>

ScoreListenerComponent::ScoreListenerComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pTextComponent{}
	, m_Score{}
{
	Integrian::EventQueue::GetInstance().AddListener(this);
}

void ScoreListenerComponent::PostInitialize()
{
	m_pTextComponent = m_pParent->GetComponentByType<Integrian::TextComponent>();
}

bool ScoreListenerComponent::OnEvent(const Integrian::Event& event)
{
	if (event.GetEvent() == "TileChanged")
	{
		std::string renderedText{ m_pTextComponent->GetTextToRender() };
		
		renderedText.erase(std::remove_if(renderedText.begin(), renderedText.end(), [](const char c)
			{
				return std::isdigit(c);
			}), renderedText.end());
		
		m_Score += std::get<0>(event.GetData<int>());

		renderedText += std::to_string(m_Score);

		m_pTextComponent->SetTextToRender(renderedText);

		return true;
	}

	return false;
}