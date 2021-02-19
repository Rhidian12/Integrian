#include "pch.h"
#include "InputManager.h"

extern bool g_IsLooping;

Integrian::InputManager::InputManager()
	: m_MousePosition{}
	, m_WindowWidth{}
	, m_WindowHeight{}
{
}


Integrian::InputManager::~InputManager()
{
	//m_KeyDownKeybindCommands.clear();
	//m_KeyUpKeybindCommands.clear();
	//m_MouseDownMouseCommands.clear();
	//m_MouseUpMouseCommands.clear();
	m_pCommands.clear();
}

void Integrian::InputManager::AddCommand(const GameInput gameInput, Command* pCommand, const State keyState)
{
	m_pCommands[gameInput].push_back(CommandAndButton{ pCommand,keyState });
}

void Integrian::InputManager::HandleInput()
{
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
			//for (const KeybindFunctionWrapperPair& functionwrapper : m_KeyUpKeybindCommands)
			//	if (e.key.keysym.scancode == functionwrapper.first)
			//		for (Command* pCommand : functionwrapper.second)
			//			pCommand->Execute();
			for (const InputCommandPair& inputCommandPair : m_pCommands)
				for (const CommandAndButton& commandAndButton : inputCommandPair.second)
					if (commandAndButton.keyState == State::OnPress)
						if (static_cast<SDL_Scancode>(inputCommandPair.first.keyboardInput) == e.key.keysym.scancode)
							commandAndButton.pCommand->Execute();
			break;
		case SDL_MOUSEBUTTONDOWN:
			//for (const MouseFunctionWrapperPair& functionWrapper : m_MouseDownMouseCommands)
			//{
			//	switch (functionWrapper.first)
			//	{
			//	case MouseButton::LMB:
			//		if constexpr (SDL_BUTTON(1) == SDL_BUTTON_LEFT)
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	case MouseButton::MMB:
			//		if constexpr (SDL_BUTTON(2) == SDL_BUTTON_MIDDLE)
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	case MouseButton::RMB:
			//		if constexpr (SDL_BUTTON(3) == SDL_BUTTON_RIGHT)
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	case MouseButton::LMBAndMMB:
			//		if constexpr ((SDL_BUTTON(1) == SDL_BUTTON_LEFT) && (SDL_BUTTON(2) == SDL_BUTTON_MIDDLE))
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	case MouseButton::LMBAndRMB:
			//		if constexpr ((SDL_BUTTON(1) == SDL_BUTTON_LEFT) && (SDL_BUTTON(3) == SDL_BUTTON_RIGHT))
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	case MouseButton::RMBandMMB:
			//		if constexpr ((SDL_BUTTON(2) == SDL_BUTTON_MIDDLE) && (SDL_BUTTON(3) == SDL_BUTTON_RIGHT))
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	default:
			//		break;
			//	}
			//}
			for (const InputCommandPair& inputCommandPair : m_pCommands)
				for (const CommandAndButton& commandAndButton : inputCommandPair.second)
					if (commandAndButton.keyState == State::OnHeld)
						if (static_cast<std::underlying_type<MouseButton>::type>(inputCommandPair.first.mouseButton) & mouseState)
							commandAndButton.pCommand->Execute();
			break;
		case SDL_MOUSEBUTTONUP:
			//for (const MouseFunctionWrapperPair& functionWrapper : m_MouseUpMouseCommands)
			//{
			//	switch (functionWrapper.first)
			//	{
			//	case MouseButton::LMB:
			//		if constexpr (SDL_BUTTON(1) == SDL_BUTTON_LEFT)
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	case MouseButton::MMB:
			//		if constexpr (SDL_BUTTON(2) == SDL_BUTTON_MIDDLE)
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	case MouseButton::RMB:
			//		if constexpr (SDL_BUTTON(3) == SDL_BUTTON_RIGHT)
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	case MouseButton::LMBAndMMB:
			//		if constexpr ((SDL_BUTTON(1) == SDL_BUTTON_LEFT) && (SDL_BUTTON(2) == SDL_BUTTON_MIDDLE))
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	case MouseButton::LMBAndRMB:
			//		if constexpr ((SDL_BUTTON(1) == SDL_BUTTON_LEFT) && (SDL_BUTTON(3) == SDL_BUTTON_RIGHT))
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	case MouseButton::RMBandMMB:
			//		if constexpr ((SDL_BUTTON(2) == SDL_BUTTON_MIDDLE) && (SDL_BUTTON(3) == SDL_BUTTON_RIGHT))
			//			for (Command* pFunction : functionWrapper.second)
			//				pFunction->Execute();
			//		break;
			//	default:
			//		break;
			//	}
			//}
			for (const InputCommandPair& inputCommandPair : m_pCommands)
				for (const CommandAndButton& commandAndButton : inputCommandPair.second)
					if (commandAndButton.keyState == State::OnHeld)
						if (static_cast<std::underlying_type<MouseButton>::type>(inputCommandPair.first.mouseButton) & mouseState)
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
				if (pStates[static_cast<SDL_Scancode>(inputCommandPair.first.keyboardInput)])
					commandAndButton.pCommand->Execute();
	//for (const KeybindFunctionWrapperPair& functionwrapper : m_KeyDownKeybindCommands)
	//	if (pStates[functionwrapper.first])
	//		for (Command* pFunction : functionwrapper.second)
	//			pFunction->Execute();
}

void Integrian::InputManager::SetWindowSize(const uint32_t width, const uint32_t height)
{
	m_WindowWidth = width;
	m_WindowHeight = height;
}

const Integrian::Point2f& Integrian::InputManager::GetMousePosition() const
{
	return m_MousePosition;
}