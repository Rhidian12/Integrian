#include "IntegrianPCH.h"
#include "GameObjectInformation.h"

Integrian::GameObjectInformation::GameObjectInformation(const std::string& identifier, const unsigned int id)
	: m_Identifier{ identifier }
	, m_ID{ id }
{
}
Integrian::GameObjectInformation::GameObjectInformation(const std::string& identifier)
	: m_Identifier{ identifier }
	, m_ID{}
{
}