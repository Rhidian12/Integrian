#pragma once

#ifndef INTEGRIAN_GAMEOBJECTINFORMATION_H
#define INTEGRIAN_GAMEOBJECTINFORMATION_H

#include <string>

namespace Integrian
{
	class GameObjectInformation final
	{
	public:
		std::string m_Identifier;
		unsigned int m_ID;

		bool operator==(const GameObjectInformation& a) const noexcept
		{
			return m_Identifier == a.m_Identifier;
		}

	private:
		friend class App;
		GameObjectInformation(const std::string& identifier, const unsigned int id);
		GameObjectInformation(const std::string& identifier);
	};

	struct GameObjectInformationComparer
	{
		bool operator()(const GameObjectInformation& a, const GameObjectInformation& b) const noexcept
		{
			return a.m_ID < b.m_ID;
		}
	};
}

#endif // !INTEGRIAN_GAMEOBJECTINFORMATION_H