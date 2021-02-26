#include "pch.h"
#include "InputManager.h"
#include <algorithm>
#include "GameController.h"
#include "Keyboard.h"
#include "Mouse.h"

extern bool g_IsLooping;

Integrian::InputManager::InputManager()
	: m_MousePosition{}
	, m_WindowWidth{}
	, m_WindowHeight{}
	, m_AmountOfControllers{ uint8_t(SDL_NumJoysticks()) }
	, m_Controllers{}
{
	for (uint32_t i{}; i < m_MaxAmountOfControllers; ++i)
		m_Controllers[i] = std::move(GameController{ uint8_t(i) });

	m_Keyboard = std::move(Keyboard{});

	m_Mouse = std::move(Mouse{});
}

void Integrian::InputManager::AddCommand(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex)
{
	if (gameInput.controllerInput != ControllerInput::INVALID)
		m_Controllers[controllerIndex].AddCommand(gameInput.controllerInput, keyState, pCommand);

	else if (gameInput.mouseButton != MouseButton::INVALID)
		m_Mouse.AddCommand(gameInput.mouseButton, keyState, pCommand);

	else /*if (gameInput.keyboardInput != KeyboardInput::INVALID)*/
		m_Keyboard.AddCommand(gameInput.keyboardInput, keyState, pCommand);
}

void Integrian::InputManager::HandleInput()
{
	// http://scottmeyers.blogspot.com/2015/09/should-you-be-using-something-instead.html
	// Searching linearly through an unsorted vector is faster than a map / unordered map

	int x{}, y{};
	const Uint32 mouseState = SDL_GetMouseState(&x, &y);

	m_MousePosition = Point2f{ float(x),float(m_WindowHeight - y) };

	// does not actually work surprisingly enough
	//m_AmountOfControllers = uint8_t(SDL_NumJoysticks()); // check if controllers have been added / removed

	SDL_Event e;
	while (SDL_PollEvent(&e) > 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g_IsLooping = false;
			break;
		default:
			break;
		}
	}

	m_Keyboard.ExecuteCommands();
	m_Mouse.ExecuteCommands();

	for (uint32_t i{}; i < m_AmountOfControllers; ++i)
		m_Controllers[i].ExecuteCommands();
}

void Integrian::InputManager::SetWindowSize(const uint32_t width, const uint32_t height)
{
	m_WindowWidth = width;
	m_WindowHeight = height;
}

bool Integrian::InputManager::IsKeyboardKeyPressed(const KeyboardInput gameInput) const
{
	return m_Keyboard.IsPressed(gameInput);
}

bool Integrian::InputManager::IsMouseButtonPressed(const MouseButton gameInput) const
{
	return m_Mouse.IsPressed(gameInput);
}

bool Integrian::InputManager::IsControllerButtonPressed(const ControllerInput gameInput, const uint8_t playerIndex) const
{
	return m_Controllers[playerIndex].IsPressed(gameInput);
}

const Integrian::Point2f& Integrian::InputManager::GetMousePosition() const
{
	return m_MousePosition;
}
