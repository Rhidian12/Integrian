#include "IntegrianPCH.h" // precompiled header
#include "InputManager.h" // header

extern std::atomic<bool> volatile g_IsLooping;

Integrian::InputManager::InputManager()
	: m_MousePosition{}
	, m_WindowWidth{}
	, m_WindowHeight{}
	, m_AmountOfControllers{ uint8_t(SDL_NumJoysticks()) }
	, m_Controllers{}
{
	for (uint32_t i{}; i < m_AmountOfControllers; ++i)
	{
		m_Controllers[i] = std::move(GameController{ uint8_t(i) });
		EventQueue::GetInstance().AddListener(&m_Controllers[i]);
	}

	m_Keyboard = std::move(Keyboard{});
	EventQueue::GetInstance().AddListener(&m_Keyboard);

	m_Mouse = std::move(Mouse{});
	EventQueue::GetInstance().AddListener(&m_Mouse);
}

void Integrian::InputManager::RemoveCommandFromInput(const GameInput& input, std::function<void()>& pCommand, const uint8_t controllerIndex)
{
	if (input.mouseButton != MouseButton::INVALID)
		m_Mouse.RemoveCommand(pCommand);

	else if (input.keyboardInput != KeyboardInput::INVALID)
		m_Keyboard.RemoveCommand(pCommand);

	else
		m_Controllers[controllerIndex].RemoveCommand(pCommand);
}

void Integrian::InputManager::RemoveCommand(const std::function<void()>& pCommand, const uint8_t controllerIndex)
{
	m_Mouse.RemoveCommand(pCommand);
	m_Keyboard.RemoveCommand(pCommand);
	m_Controllers[controllerIndex].RemoveCommand(pCommand);
}

void Integrian::InputManager::RemoveAllCommands()
{
	for (uint8_t i{}; i < 4; ++i)
		m_Controllers[i].m_pCommands.clear();

	m_Keyboard.m_KeyboardCommands.clear();
	
	m_Mouse.m_MouseCommands.clear();
}

void Integrian::InputManager::SetControllerCommands(std::unordered_map<ControllerInput, std::vector<CommandAndButton>> commands, const uint8_t index)
{
	m_Controllers[index].m_pCommands = commands;
}

void Integrian::InputManager::SetKeyboardCommands(std::unordered_map<KeyboardInput, std::vector<CommandAndButton>> commands)
{
	m_Keyboard.m_KeyboardCommands = commands;
}

void Integrian::InputManager::SetMouseCommands(std::unordered_map<MouseButton, std::vector<CommandAndButton>> commands)
{
	m_Mouse.m_MouseCommands = commands;
}

void Integrian::InputManager::AddCommand(const GameInput& gameInput, const std::function<void()>& pCommand, const State keyState, const uint8_t controllerIndex)
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
			g_IsLooping.store(false);
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

double Integrian::InputManager::GetJoystickMovement(const ControllerInput axis, const uint8_t playerIndex) const
{
	return m_Controllers[playerIndex].GetJoystickMovement(axis);
}

double Integrian::InputManager::GetTriggerMovement(const ControllerInput axis, const uint8_t playerIndex) const
{
	return m_Controllers[playerIndex].GetTriggerMovement(axis);
}

const std::unordered_map<Integrian::KeyboardInput, std::vector<Integrian::CommandAndButton>>& Integrian::InputManager::GetKeyboardCommands() const
{
	return m_Keyboard.GetCommands();
}

const std::unordered_map<Integrian::MouseButton, std::vector<Integrian::CommandAndButton>>& Integrian::InputManager::GetMouseCommands() const
{
	return m_Mouse.GetCommands();
}

const std::unordered_map<Integrian::ControllerInput, std::vector<Integrian::CommandAndButton>>& Integrian::InputManager::GetControllerCommands(const uint8_t index) const
{
	return m_Controllers[index].GetCommands();
}
