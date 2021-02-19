#include "Command.h"

Integrian::Command::Command()
	: Command{ nullptr }
{
}

Integrian::Command::Command(GameObject* actor)
	: m_Actor{ actor }
{
}
