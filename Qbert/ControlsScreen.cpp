#include "ControlsScreen.h"

#include "ButtonComponent.h"
#include "ButtonHandlerComponent.h"
#include "Qbert_MainGame.h"

#include <TextComponent.h>
#include <TextureComponent.h>
#include <Texture.h>
#include <TextureManager.h>

ControlsScreen::ControlsScreen()
	: App{ "ControlsScreen" }
{
}

void ControlsScreen::Start()
{
	using namespace Integrian;

	SetClearColour(RGBColour{ 49.f, 34.f, 119.f });

	const Point2f center{ m_WindowWidth / 2.f, m_WindowHeight / 2.f };

	GameObject* pControlsText{ new GameObject{} };
	TextComponent* pControlsTextComponent{ new TextComponent{ pControlsText, "keyboard or controller?", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pControlsText->AddComponent(pControlsTextComponent);
	pControlsText->transform.SetPosition(Point2f{ center.x - 280.f, center.y + 100.f });
	AddGameObject("ControlsText", pControlsText);

	GameObject* pKeyboardButton{ new GameObject{} };
	pKeyboardButton->SetTag("Button");
	TextComponent* pKeyboardText{ new TextComponent{ pKeyboardButton, "keyboard", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pKeyboardButton->AddComponent(new ButtonComponent{ pKeyboardButton, "Qbert_MainGame" + std::to_string(Qbert_MainGame::GetLevel()) });
	pKeyboardButton->AddComponent(pKeyboardText);
	pKeyboardButton->transform.SetPosition(Point2f{ center.x - pKeyboardText->GetWidth() / (pKeyboardText->GetTextToRender().size() + 3), center.y + 50.f });
	AddGameObject("KeyboardButton", pKeyboardButton);

	GameObject* pControllerButton{ new GameObject{} };
	pControllerButton->SetTag("Button");
	TextComponent* pControllerText{ new TextComponent{ pControllerButton, "controller", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pControllerButton->AddComponent(new ButtonComponent{ pControllerButton, "Qbert_MainGame" + std::to_string(Qbert_MainGame::GetLevel()) });
	pControllerButton->AddComponent(pControllerText);
	pControllerButton->transform.SetPosition(Point2f{ center.x - 160.f, center.y });
	AddGameObject("ControllerButton", pControllerButton);

	GameObject* pButtonHandler{ new GameObject{} };
	pButtonHandler->AddComponent(new TextureComponent{ pButtonHandler, TextureManager::GetInstance().GetTexture("PlayerSelection") });
	pButtonHandler->AddComponent(new ButtonHandlerComponent{ pButtonHandler });
	AddGameObject("ButtonHandler", pButtonHandler);
}
