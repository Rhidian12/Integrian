#include "pch.h"
#include "Keyboard.h"
#include "Command.h"
#include "ServiceLocator.h"

Integrian::Keyboard::Keyboard(Keyboard&& other)
{
	m_KeyboardCommands = other.m_KeyboardCommands;
	other.m_KeyboardCommands.clear();
}


Integrian::Keyboard::~Keyboard()
{
	m_KeyboardCommands.clear();
}

void Integrian::Keyboard::AddCommand(const KeyboardInput keyboardInput, const State keyState, Command* pCommand)
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
				commandAndButton.pCommand->Execute();
			}
			commandAndButton.previousKeystate = currentKeystate;
		}
	}
}

bool Integrian::Keyboard::IsPressed(const KeyboardInput gameInput) const
{
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

void Integrian::Keyboard::RemoveInput(const KeyboardInput keyboardInput)
{
#ifdef _DEBUG
	UMapIterator it{ m_KeyboardCommands.find(keyboardInput) };
	if (it != m_KeyboardCommands.end())
		m_KeyboardCommands.erase(it);
	else
	{
		// TODO: Come up with a better logging system, this is ridicilous
		const Logger& logger{ ServiceLocator::GetInstance().GetLogger() };
		logger.Log("Tried to remove a non-existing input, ", ErrorLevel::severeError);
		logger.Log("In file and at line: ", ErrorLevel::severeError);
		logger.Log(__FILE__, ErrorLevel::severeError);
		logger.Log(std::to_string(__LINE__), ErrorLevel::severeError);
		logger.Log("\n", ErrorLevel::severeError);
	}
#else
	try
	{
		m_KeyboardCommands.erase(keyboardInput);
	}
	catch (const std::exception&)
	{
		// TODO: Make this print to a file
		std::cerr << "Tried to remove a non-existent input" << std::endl;
	}
#endif
}

void Integrian::Keyboard::RemoveCommandFromInput(const KeyboardInput keyboardInput, Command* pCommand)
{
	std::vector<CommandAndButton>& commands{ m_KeyboardCommands.find(keyboardInput)->second };

#ifdef _DEBUG
	std::vector<CommandAndButton>::iterator it{ std::remove_if(commands.begin(),commands.end(),[pCommand](const CommandAndButton& commandAndButton)->bool
		{
			return commandAndButton.pCommand == pCommand;
		}) };

	if (it != commands.end())
		commands.erase(it, commands.end());
	else
	{
		Logger& logger{ ServiceLocator::GetInstance().GetLogger() };
		logger.Log("Tried to remove a non-existing command, ", ErrorLevel::severeError);
		logger.Log("In file and at line: ", ErrorLevel::severeError);
		logger.Log(__FILE__, ErrorLevel::severeError);
		logger.Log(std::to_string(__LINE__), ErrorLevel::severeError);
		logger.Log("\n", ErrorLevel::severeError);
	}
#else
	try
	{
		commands.erase(std::remove_if(commands.begin(), commands.end(), [pCommand](const CommandAndButton& commandAndButton)->bool
			{
				return commandAndButton.pCommand == pCommand;
			}));
	}
	catch (const std::exception&)
	{
		// TODO: Make this print something to a log file
		std::cerr << "Tried to remove non-existing command" << std::endl;
	}
#endif
}
