#include "KeyboardExplanationScreen.h"

#include <TextComponent.h>
#include <FiniteStateMachine.h>

#include "KeyboardExplanationFSM.h"

KeyboardExplanationScreen::KeyboardExplanationScreen()
	: App{ "KeyboardExplanationScreen" }
{
}

void KeyboardExplanationScreen::Start()
{
	using namespace Integrian;

	SetClearColour(RGBColour{ 49.f, 34.f, 119.f });

	const Point2f center{ m_WindowWidth / 2.f, m_WindowHeight / 2.f };

	GameObject* pRightTopText{ new GameObject{} };
	pRightTopText->SetTag("Text");
	TextComponent* pRightTopTextComponent{ new TextComponent{ pRightTopText, "assign a button for right top movement", "Resources/Fonts/QbertFont.ttf", 15, RGBColour{255.f, 255.f, 0.f} } };
	pRightTopText->AddComponent(pRightTopTextComponent);
	pRightTopText->transform.SetPosition(Point2f{ center.x - 300.f, center.y });
	AddGameObject("RightTopText", pRightTopText);

	GameObject* pRightBottomText{ new GameObject{} };
	pRightBottomText->SetTag("Text");
	TextComponent* pRightBottomTextComponent{ new TextComponent{ pRightBottomText, "assign a button for right bottom movement", "Resources/Fonts/QbertFont.ttf", 15, RGBColour{255.f, 255.f, 0.f} } };
	pRightBottomText->AddComponent(pRightBottomTextComponent);
	pRightBottomText->transform.SetPosition(Point2f{ center.x - 300.f, center.y });
	pRightBottomText->SetIsActive(false);
	AddGameObject("RightBottomText", pRightBottomText);

	GameObject* pLeftBottomText{ new GameObject{} };
	pLeftBottomText->SetTag("Text");
	TextComponent* pLeftBottomTextComponent{ new TextComponent{ pLeftBottomText, "assign a button for left bottom movement", "Resources/Fonts/QbertFont.ttf", 15, RGBColour{255.f, 255.f, 0.f} } };
	pLeftBottomText->AddComponent(pLeftBottomTextComponent);
	pLeftBottomText->transform.SetPosition(Point2f{ center.x - 300.f, center.y });
	pLeftBottomText->SetIsActive(false);
	AddGameObject("LeftBottomText", pLeftBottomText);

	GameObject* pLeftTopText{ new GameObject{} };
	pLeftTopText->SetTag("Text");
	TextComponent* pLeftTopTextComponent{ new TextComponent{ pLeftTopText, "assign a button for left bottom movement", "Resources/Fonts/QbertFont.ttf", 15, RGBColour{255.f, 255.f, 0.f} } };
	pLeftTopText->AddComponent(pLeftTopTextComponent);
	pLeftTopText->transform.SetPosition(Point2f{ center.x - 300.f, center.y });
	pLeftTopText->SetIsActive(false);
	AddGameObject("LeftTopText", pLeftTopText);

	GameObject* pKeyboardButtonHandler{ new GameObject{} };
	KeyboardExplanationFSM* pFSM{ new KeyboardExplanationFSM{pKeyboardButtonHandler} };
	pKeyboardButtonHandler->AddComponent(pFSM);
	pKeyboardButtonHandler->AddComponent(pFSM->CreateKeyboardFSM());
	AddGameObject("KeyboardButtonHandler", pKeyboardButtonHandler);
}
