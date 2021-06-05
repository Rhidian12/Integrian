#include "EndScreen.h"

#include <GameObject.h>
#include <Component.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include <Texture.h>
#include <TextComponent.h>
#include <EventQueue.h>

#include "ButtonComponent.h"
#include "ButtonHandlerComponent.h"
#include "ScoreListenerComponent.h"

EndScreen::EndScreen()
	: App{ "EndScreen" }
{
}

void EndScreen::Start()
{
	using namespace Integrian;

	TextureManager& textureManager{ TextureManager::GetInstance() };

	const Point2f center{ m_WindowWidth / 2.f, m_WindowHeight / 2.f };

	SetClearColour(RGBColour{ 49.f, 34.f, 119.f });

	GameObject* pScore{ new GameObject{} };
	TextComponent* pScoreText{ new TextComponent{ pScore, "score: " + std::to_string(ScoreListenerComponent::GetScore()), "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pScore->AddComponent(pScoreText);
	pScore->AddComponent(new ScoreListenerComponent{ pScore });
	pScore->transform.SetPosition(Point2f{ center.x - 50.f, center.y + 100.f });
	AddGameObject("Score", pScore);

	GameObject* pStartButton{ new GameObject{} };
	pStartButton->SetTag("Button");
	TextComponent* pStartText{ new TextComponent{ pStartButton, "restart game", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pStartButton->AddComponent(new ButtonComponent{ pStartButton, "StartMenu" });
	pStartButton->AddComponent(pStartText);
	pStartButton->transform.SetPosition(Point2f{ center.x - 50.f, center.y + 50.f });
	AddGameObject("StartButton", pStartButton);

	GameObject* pQuitButton{ new GameObject{} };
	pQuitButton->SetTag("Button");
	TextComponent* pEndText{ new TextComponent{ pQuitButton, "exit", "Resources/Fonts/QbertFont.ttf", 30, RGBColour{255.f, 255.f, 0.f} } };
	pQuitButton->AddComponent(new ButtonComponent{ pQuitButton, "ExitGame" });
	pQuitButton->AddComponent(pEndText);
	pQuitButton->transform.SetPosition(Point2f{ center.x - 50.f, center.y });
	AddGameObject("QuitButton", pQuitButton);

	GameObject* pButtonHandler{ new GameObject{} };
	pButtonHandler->AddComponent(new TextureComponent{ pButtonHandler, textureManager.GetTexture("PlayerSelection") });
	pButtonHandler->AddComponent(new ButtonHandlerComponent{ pButtonHandler });
	AddGameObject("ButtonHandler", pButtonHandler);
}

void EndScreen::OnAppExit()
{
	Integrian::EventQueue::GetInstance().QueueDelayedEvent(Integrian::Event{ "ResetScore" }, 1);
}
