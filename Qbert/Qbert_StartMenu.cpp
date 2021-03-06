#include "Qbert_StartMenu.h"

#include <GameObject.h>
#include <Component.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include <Texture.h>
#include <TextComponent.h>

#include "ButtonComponent.h"
#include "ButtonHandlerComponent.h"
#include "Qbert_MainGame.h"

Qbert_StartMenu::Qbert_StartMenu()
	: App{ "StartMenu" }
{}

void Qbert_StartMenu::Start()
{
	using namespace Integrian;

	TextureManager& textureManager{ TextureManager::GetInstance() };
	textureManager.AddTexture("PlayerSelection", "Resources/Images/UI/Player_Selection.png");
	textureManager.AddTexture("Q*bertLogo", "Resources/Images/UI/QbertLogo.png");

	const Point2f center{ m_WindowWidth / 2.f, m_WindowHeight / 2.f };

	SetClearColour(RGBColour{ 49.f, 34.f, 119.f });

	GameObject* pQbertLogo{ new GameObject{} };
	TextComponent* pQbertLogoText{ new TextComponent{ pQbertLogo, "qbert", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pQbertLogo->AddComponent(pQbertLogoText);
	pQbertLogo->transform.SetPosition(Point2f{ center.x - pQbertLogoText->GetWidth() / (pQbertLogoText->GetTextToRender().size() + 8), center.y + 100.f });
	AddGameObject("QbertLogo", pQbertLogo);

	GameObject* pStartButton{ new GameObject{} };
	pStartButton->SetTag("Button");
	TextComponent* pStartText{ new TextComponent{ pStartButton, "start game", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pStartButton->AddComponent(new ButtonComponent{ pStartButton, "StartGame" });
	pStartButton->AddComponent(pStartText);
	pStartButton->transform.SetPosition(Point2f{ center.x - pStartText->GetWidth() / (pStartText->GetTextToRender().size() + 3), center.y + 50.f });
	AddGameObject("StartButton", pStartButton);

	GameObject* pCoOpButton{ new GameObject{} };
	pCoOpButton->SetTag("Button");
	TextComponent* pCoopText{ new TextComponent{ pCoOpButton, "co-op", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pCoOpButton->AddComponent(new ButtonComponent{ pCoOpButton, "Co-Op" });
	pCoOpButton->AddComponent(pCoopText);
	pCoOpButton->transform.SetPosition(Point2f{ center.x - pCoopText->GetWidth() / (pCoopText->GetTextToRender().size() + 8), center.y });
	AddGameObject("Co-OpButton", pCoOpButton);

	GameObject* pQuitButton{ new GameObject{} };
	pQuitButton->SetTag("Button");
	TextComponent* pEndText{ new TextComponent{ pQuitButton, "exit", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pQuitButton->AddComponent(new ButtonComponent{ pQuitButton, "ExitGame" });
	pQuitButton->AddComponent(pEndText);
	pQuitButton->transform.SetPosition(Point2f{ center.x - pStartText->GetWidth() / (pStartText->GetTextToRender().size() + 3), center.y - 50.f});
	AddGameObject("QuitButton", pQuitButton);
	
	GameObject* pButtonHandler{ new GameObject{} };
	pButtonHandler->AddComponent(new TextureComponent{ pButtonHandler, textureManager.GetTexture("PlayerSelection") });
	pButtonHandler->AddComponent(new ButtonHandlerComponent{ pButtonHandler });
	AddGameObject("ButtonHandler", pButtonHandler);
}

void Qbert_StartMenu::OnAppEnter()
{
	Qbert_MainGame::SetLevel(1);
}
