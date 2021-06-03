#include "ButtonHandlerComponent.h"
#include <App_Selector.h>
#include <App.h>
#include <GameObject.h>
#include <InputManager.h>
#include <TextureComponent.h>
#include <Texture.h>
#include "ButtonComponent.h"

ButtonHandlerComponent::ButtonHandlerComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pButtons{}
	, m_pTextureComponent{}
{
	Integrian::EventQueue::GetInstance().AddListener(this);
}

void ButtonHandlerComponent::PostInitialize()
{
	using namespace Integrian;

	for (const std::pair<GameObjectInformation, GameObject*>& pair : App_Selector::GetInstance().GetActiveApplication()->GetGameObjects())
		if (pair.second->GetTag() == "Button")
			m_pButtons.push_back(pair.second->GetComponentByType<ButtonComponent>());

	m_pTextureComponent = m_pParent->GetComponentByType<TextureComponent>();

	m_pButtons[0]->SetIsSelected(true);
	m_pParent->transform.SetPosition(Point2f{ m_pButtons[0]->GetParent()->transform.GetPosition().x - m_pTextureComponent->GetTexture()->GetWidth(),
		m_pButtons[0]->GetParent()->transform.GetPosition().y - m_pTextureComponent->GetTexture()->GetHeight() / 4.f});

	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::S }, [this]()
		{
			for (size_t i{}; i < m_pButtons.size(); ++i)
			{
				if (m_pButtons[i]->GetIsSelected()) // select the next one down
				{
					if (i + 1 >= m_pButtons.size()) // back to the top
					{
						m_pButtons[i]->SetIsSelected(false); // set current button to non-selected
						m_pButtons[0]->SetIsSelected(true); // set top button to selected
					}
					else
					{
						m_pButtons[i]->SetIsSelected(false); // set current button to non-selected
						m_pButtons[i + 1]->SetIsSelected(true); // set next button to selected
					}
				}
			}
		}, State::OnPress);
}

void ButtonHandlerComponent::Update(const float)
{
	using namespace Integrian;

	for (ButtonComponent* const pButton : m_pButtons)
	{
		if (pButton->GetIsSelected())
		{
			m_pParent->transform.SetPosition(Point2f{ pButton->GetParent()->transform.GetPosition().x - m_pTextureComponent->GetTexture()->GetWidth(),
				pButton->GetParent()->transform.GetPosition().y - m_pTextureComponent->GetTexture()->GetHeight() / 4.f });			break;
		}
	}
}

bool ButtonHandlerComponent::OnEvent(const Integrian::Event& event)
{
	using namespace Integrian;

	const std::string eventName{ event.GetEvent() };

	if (eventName == "StartGame")
	{
		App_Selector::GetInstance().SetActiveApplication("Qbert_MainGame");
		return true;
	}

	return false;
}
