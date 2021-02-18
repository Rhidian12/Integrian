#include "Command.h"

Integrian::Command::Command()
	: Command{ GameObject{} }
{
}

Integrian::Command::Command(const GameObject& actor)
	: m_Actor{ actor }
{
}
