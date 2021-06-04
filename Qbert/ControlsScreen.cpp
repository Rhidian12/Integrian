#include "ControlsScreen.h"

#include "ButtonComponent.h"
#include "ButtonHandlerComponent.h"

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
	TextComponent* pControlsTextComponent{ new TextComponent{ pControlsText, "Keyboard or Controller?", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pControlsText->AddComponent(pControlsTextComponent);
	pControlsText->transform.SetPosition(Point2f{ center.x - 280.f, center.y + 100.f });
	AddGameObject("ControlsText", pControlsText);

	GameObject* pKeyboardButton{ new GameObject{} };
	pKeyboardButton->SetTag("Button");
	TextComponent* pKeyboardText{ new TextComponent{ pKeyboardButton, "Keyboard", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pKeyboardButton->AddComponent(new ButtonComponent{ pKeyboardButton, "KeyboardExplanationScreen" });
	pKeyboardButton->AddComponent(pKeyboardText);
	pKeyboardButton->transform.SetPosition(Point2f{ center.x - pKeyboardText->GetWidth() / (pKeyboardText->GetTextToRender().size() + 3), center.y + 50.f });
	AddGameObject("KeyboardButton", pKeyboardButton);

	GameObject* pControllerButton{ new GameObject{} };
	pControllerButton->SetTag("Button");
	TextComponent* pControllerText{ new TextComponent{ pControllerButton, "Controller", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pControllerButton->AddComponent(new ButtonComponent{ pControllerButton, "ControllerExplanationScreen" });
	pControllerButton->AddComponent(pControllerText);
	pControllerButton->transform.SetPosition(Point2f{ center.x - 160.f, center.y });
	AddGameObject("ControllerButton", pControllerButton);

	GameObject* pButtonHandler{ new GameObject{} };
	pButtonHandler->AddComponent(new TextureComponent{ pButtonHandler, TextureManager::GetInstance().GetTexture("PlayerSelection") });
	pButtonHandler->AddComponent(new ButtonHandlerComponent{ pButtonHandler });
	AddGameObject("ButtonHandler", pButtonHandler);
}
