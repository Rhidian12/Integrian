#include "pch.h"
#include "InputManager.h"
#include <optional>

extern bool g_IsLooping;

Integrian::InputManager::InputManager()
	: m_MousePosition{}
	, m_WindowWidth{}
	, m_WindowHeight{}
	, m_AmountOfControllers{ uint32_t(SDL_NumJoysticks()) }
	, m_pControllers{}
{
	for(uint32_t i{}; i < m_AmountOfControllers; ++i)
	{
		if (SDL_IsGameController(i))
		{
			m_pControllers[i] = SDL_GameControllerOpen(i);

			if (!m_pControllers[i])
			{
				Logger::GetInstance().Log("Error in controllers: ", ErrorLevel::error);
				Logger::GetInstance().Log(SDL_GetError(), ErrorLevel::error);
			}
		}
	}
}


Integrian::InputManager::~InputManager()
{
	m_pCommands.clear();
	// Below code SHOULD work, but does not work. Throws read access violations, even though this is the exact
	// way SDL defines this
	// TODO: figure out why this is happening
	/*for (SDL_GameController* pController : m_pControllers) 
		if (pController)
		{
			SDL_GameControllerClose(pController);
			pController = nullptr;
		}*/
}

void Integrian::InputManager::AddCommand(const GameInput& gameInput, Command* pCommand, const State keyState)
{
	m_pCommands[gameInput].push_back(CommandAndButton{ pCommand,keyState });
}

void Integrian::InputManager::HandleInput()
{
	// http://scottmeyers.blogspot.com/2015/09/should-you-be-using-something-instead.html
	// Searching linearly through an unsorted vector is faster than a map / unordered map
	
	int x{}, y{};
	const Uint32 mouseState = SDL_GetMouseState(&x, &y);

	m_MousePosition = Point2f{ float(x),float(m_WindowHeight - y) };

	SDL_Event e;
	while (SDL_PollEvent(&e) > 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g_IsLooping = false;
			break;
		case SDL_KEYUP:
			for (const InputCommandPair& inputCommandPair : m_pCommands)
				for (const CommandAndButton& commandAndButton : inputCommandPair.second)
					if (commandAndButton.keyState == State::OnRelease)
						if (inputCommandPair.first.keyboardInput != KeyboardInput::INVALID && static_cast<SDL_Scancode>(inputCommandPair.first.keyboardInput) == e.key.keysym.scancode)
							commandAndButton.pCommand->Execute();
			break;
		case SDL_MOUSEBUTTONDOWN:
			for (const InputCommandPair& inputCommandPair : m_pCommands)
				for (const CommandAndButton& commandAndButton : inputCommandPair.second)
					if (commandAndButton.keyState == State::OnHeld)
						if (inputCommandPair.first.mouseButton != MouseButton::INVALID && static_cast<std::underlying_type<MouseButton>::type>(inputCommandPair.first.mouseButton) & mouseState)
							commandAndButton.pCommand->Execute();
			break;
		case SDL_MOUSEBUTTONUP:
			for (const InputCommandPair& inputCommandPair : m_pCommands)
				for (const CommandAndButton& commandAndButton : inputCommandPair.second)
					if (commandAndButton.keyState == State::OnRelease)
						if (inputCommandPair.first.mouseButton != MouseButton::INVALID && static_cast<std::underlying_type<MouseButton>::type>(inputCommandPair.first.mouseButton) & mouseState)
							commandAndButton.pCommand->Execute();
			break;
		case SDL_JOYBUTTONUP:
			for(SDL_GameController* pController : m_pControllers)
				for (const InputCommandPair& inputCommandPair : m_pCommands)
					for (const CommandAndButton& commandAndButton : inputCommandPair.second)
						if (commandAndButton.keyState == State::OnRelease)
							if (inputCommandPair.first.controllerInput != ControllerInput::INVALID && SDL_GameControllerGetButton(pController, static_cast<SDL_GameControllerButton>(inputCommandPair.first.controllerInput)))
								commandAndButton.pCommand->Execute();
			break;
		default:
			break;
		}
	}

	const Uint8* const pStates = SDL_GetKeyboardState(nullptr);

	for (const InputCommandPair& inputCommandPair : m_pCommands)
		for (const CommandAndButton& commandAndButton : inputCommandPair.second)
			if (commandAndButton.keyState == State::OnHeld)
				if (inputCommandPair.first.keyboardInput != KeyboardInput::INVALID && pStates[static_cast<SDL_Scancode>(inputCommandPair.first.keyboardInput)])
					commandAndButton.pCommand->Execute();


	for (SDL_GameController* pController : m_pControllers)
		for (const InputCommandPair& inputCommandPair : m_pCommands)
			for (const CommandAndButton& commandAndButton : inputCommandPair.second)
				if (commandAndButton.keyState == State::OnHeld)
					if (inputCommandPair.first.controllerInput != ControllerInput::INVALID && SDL_GameControllerGetButton(pController, static_cast<SDL_GameControllerButton>(inputCommandPair.first.controllerInput)))
						commandAndButton.pCommand->Execute();
}

void Integrian::InputManager::SetWindowSize(const uint32_t width, const uint32_t height)
{
	m_WindowWidth = width;
	m_WindowHeight = height;
}

bool Integrian::InputManager::IsKeyboardKeyPressed(const KeyboardInput gameInput) const
{
	return SDL_GetKeyboardState(nullptr)[static_cast<SDL_Scancode>(gameInput)];
}
bool Integrian::InputManager::IsMouseButtonPressed(const MouseButton gameInput) const
{
	return static_cast<std::underlying_type<MouseButton>::type>(gameInput) & SDL_GetMouseState(NULL, NULL);
}
bool Integrian::InputManager::IsControllerButtonPressed(const ControllerInput gameInput, const uint32_t index) const
{
	return SDL_GameControllerGetButton(m_pControllers[index], static_cast<SDL_GameControllerButton>(gameInput));
}

const Integrian::Point2f& Integrian::InputManager::GetMousePosition() const
{
	return m_MousePosition;
}
