#pragma once
#ifndef INTEGRIAN_GAMEOBJECT_H
#define INTEGRIAN_GAMEOBJECT_H

#include <unordered_map>

namespace Integrian
{
	class Component;
	class GameObject final  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		GameObject() = default;
		~GameObject() = default;

		void AddComponent(const std::string& name, Component* pComponent);

		template<typename Type>
		inline Type* GetComponentByType() const
		{
			for (const std::pair<std::string, Component*>& pair : m_pComponents)
			{
				if (typeid(*pair.second) == typeid(Type))
					return static_cast<Type*>(pair.second);
			}

			// TODO: Make Logger print a message saying this returned nothing
			return nullptr;
		}
		inline void* GetComponentByName(const std::string& name) const
		{
			for (const std::pair<std::string, Component*>& pair : m_pComponents)
			{
				if (pair.first == name)
					return pair.second;
			}

			// TODO: Make Logger print a message saying this returned nothing
			return nullptr;
		}
		[[nodiscard]] const std::unordered_map<std::string, Component*>& GetComponents() const; // TODO: Check if this is necessary, if not, remove it

	private:
		std::unordered_map<std::string, Component*> m_pComponents;
	};
}
#endif // INTEGRIAN_GAMEOBJECT_H