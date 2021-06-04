#include "IntegrianPCH.h" // precompiled header
#include "Keyboard.h" // Header
#include "Logger.h" // Logger

Integrian::Keyboard::Keyboard(Keyboard&& other) noexcept
{
	m_KeyboardCommands = other.m_KeyboardCommands;
	other.m_KeyboardCommands.clear();
}


Integrian::Keyboard::~Keyboard()
{
	m_KeyboardCommands.clear();
}

bool Integrian::Keyboard::OnEvent(const Event& event)
{
	const std::string eventName{ event.GetEvent() };

	return false;
}

void Integrian::Keyboard::AddCommand(const KeyboardInput keyboardInput, const State keyState, const std::function<void()>& pCommand)
{
	m_KeyboardCommands[keyboardInput].push_back(CommandAndButton{ pCommand,keyState });
}

void Integrian::Keyboard::ExecuteCommands()
{
	for (std::pair<const KeyboardInput, std::vector<CommandAndButton>>& commandPair : m_KeyboardCommands)
	{
		for (CommandAndButton& commandAndButton : commandPair.second)
		{
			const State currentKeystate{ GetKeystate(commandPair.first, commandAndButton.previousKeystate) };
			if (currentKeystate == commandAndButton.wantedKeystate)
			{
				commandAndButton.pCommand();
			}
			commandAndButton.previousKeystate = currentKeystate;
		}
	}
}

void Integrian::Keyboard::ResetInputs()
{
	for (std::pair<const KeyboardInput, std::vector<CommandAndButton>>& commandPair : m_KeyboardCommands)
		for (CommandAndButton& commandAndButton : commandPair.second)
			commandAndButton.previousKeystate = State::NotPressed;
}

bool Integrian::Keyboard::IsPressed(const KeyboardInput gameInput) const
{
	if (gameInput == KeyboardInput::INVALID)
		return false;

	return SDL_GetKeyboardState(nullptr)[static_cast<SDL_Scancode>(gameInput)];
}

bool Integrian::Keyboard::WasPressed(const State previousState) const
{
	return (previousState == State::OnPress || previousState == State::OnHeld);
}

Integrian::State Integrian::Keyboard::GetKeystate(const KeyboardInput keyboardInput, const State previousState) const
{
	if (WasPressed(previousState))
	{
		if (IsPressed(keyboardInput))
			return State::OnHeld;

		else
			return State::OnRelease;
	}

	if (IsPressed(keyboardInput))
		return State::OnPress;

	return State::NotPressed;
}

const std::unordered_map<Integrian::KeyboardInput, std::vector<Integrian::CommandAndButton>>& Integrian::Keyboard::GetCommands() const
{
	return m_KeyboardCommands;
}

Integrian::KeyboardInput Integrian::Keyboard::GetWhichKeyIsPressed() const noexcept
{
	const Uint8* pKeyboardState{ SDL_GetKeyboardState(nullptr) };

	for (int i{ static_cast<int>(SDL_SCANCODE_A) }; i <= SDL_SCANCODE_AUDIOFASTFORWARD; ++i) // SDL_NUM_SCANCODES is incorrect?
		if (pKeyboardState[static_cast<SDL_Scancode>(i)])
			if (AllPossibleKeyboardEnumCheck::isValue(static_cast<KI>(i)))
				return static_cast<KI>(i);

	return KI::INVALID;
}

void Integrian::Keyboard::RemoveCommand(const std::function<void()>& pCommand)
{
	for (const CommandPair& commandPair : m_KeyboardCommands)
		for (const CommandAndButton& commandAndButton : commandPair.second)
			if (commandAndButton.pCommand.target_type().hash_code() == pCommand.target_type().hash_code())
				m_KeyboardCommands.erase(commandPair.first);
}