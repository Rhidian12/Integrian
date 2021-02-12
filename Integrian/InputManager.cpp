#include "pch.h"
#include "InputManager.h"
extern bool g_IsLooping;

InputManager* InputManager::m_pInstance{ nullptr };
InputManager* InputManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new InputManager{};

	return m_pInstance;
}

InputManager::~InputManager()
{
	m_KeyDownKeybindFunctions.clear();
	m_KeyUpKeybindFunctions.clear();
	m_MouseDownMouseFunctions.clear();
	m_MouseUpMouseFunctions.clear();
}

void InputManager::Cleanup()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

void InputManager::HandleInput(const float dt)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) > 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			g_IsLooping = false;
			break;
		case SDL_KEYUP:
			for (const KeybindFunctionWrapperPair& functionwrapper : m_KeyUpKeybindFunctions)
				if (e.key.keysym.scancode == functionwrapper.first)
					for (const KeybindFunction& function : functionwrapper.second)
						function(dt);
			break;
		case SDL_MOUSEBUTTONDOWN:
			for (const MouseFunctionWrapperPair& functionWrapper : m_MouseDownMouseFunctions)
			{
				switch (functionWrapper.first)
				{
				case MouseButton::LMB:
					if (SDL_BUTTON(1))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				case MouseButton::MMB:
					if (SDL_BUTTON(2))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				case MouseButton::RMB:
					if (SDL_BUTTON(3))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				case MouseButton::LMBAndMMB:
					if (SDL_BUTTON(1) & SDL_BUTTON(2))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				case MouseButton::LMBAndRMB:
					if (SDL_BUTTON(1) & SDL_BUTTON(3))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				case MouseButton::RMBandMMB:
					if (SDL_BUTTON(2) & SDL_BUTTON(3))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				default:
					break;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			for (const MouseFunctionWrapperPair& functionWrapper : m_MouseUpMouseFunctions)
			{
				switch (functionWrapper.first)
				{
				case MouseButton::LMB:
					if (SDL_BUTTON(1))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				case MouseButton::MMB:
					if (SDL_BUTTON(2))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				case MouseButton::RMB:
					if (SDL_BUTTON(3))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				case MouseButton::LMBAndMMB:
					if (SDL_BUTTON(1) & SDL_BUTTON(2))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				case MouseButton::LMBAndRMB:
					if (SDL_BUTTON(1) & SDL_BUTTON(3))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				case MouseButton::RMBandMMB:
					if (SDL_BUTTON(2) & SDL_BUTTON(3))
						for (const MouseFunction& function : functionWrapper.second)
							function();
					break;
				default:
					break;
				}
			}
		}
	}

	int x{}, y{};
	Uint32 mouseState = SDL_GetMouseState(&x, &y);
	m_MousePosition = Engine::Point2f{ float(x),m_WindowHeight - float(y) };

	const Uint8* pStates = SDL_GetKeyboardState(NULL);

	for (const KeybindFunctionWrapperPair& functionwrapper : m_KeyDownKeybindFunctions)
		if (pStates[functionwrapper.first])
			for (const KeybindFunction& function : functionwrapper.second)
				function(dt);
}

void InputManager::SetWindowSize(const uint32_t width, const uint32_t height)
{
	m_WindowWidth = width;
	m_WindowHeight = height;
}

const Engine::Point2f& InputManager::GetMousePosition() const
{
	return m_MousePosition;
}
