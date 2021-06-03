#include "Qbert_StartMenu.h"

#include <GameObject.h>
#include <Component.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include <Texture.h>
#include <TextComponent.h>

#include "ButtonComponent.h"
#include "ButtonHandlerComponent.h"

Qbert_StartMenu::Qbert_StartMenu()
	: App{ "StartMenu" }
{}

void Qbert_StartMenu::Start()
{
	using namespace Integrian;

	TextureManager& textureManager{ TextureManager::GetInstance() };
	textureManager.AddTexture("PlayerSelection", "Resources/Images/UI/Player_Selection.png");

	const Point2f center{ m_WindowWidth / 2.f, m_WindowHeight / 2.f };

	GameObject* pStartButton{ new GameObject{} };
	pStartButton->SetTag("Button");
	TextComponent* pStartText{ new TextComponent{ pStartButton, "Start Game", 30, RGBColour{255.f, 255.f, 0.f} } };
	pStartButton->AddComponent(new ButtonComponent{ pStartButton, "StartGame" });
	pStartButton->AddComponent(pStartText);
	pStartButton->transform.SetPosition(Point2f{ center.x - pStartText->GetWidth() / (pStartText->GetTextToRender().size() + 3), center.y + 100.f });
	AddGameObject("StartButton", pStartButton);
	
	GameObject* pButtonHandler{ new GameObject{} };
	pButtonHandler->AddComponent(new TextureComponent{ pButtonHandler, textureManager.GetTexture("PlayerSelection") });
	pButtonHandler->AddComponent(new ButtonHandlerComponent{ pButtonHandler });
	AddGameObject("ButtonHandler", pButtonHandler);
}
