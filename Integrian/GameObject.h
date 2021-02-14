#pragma once
#ifndef INTEGRIAN_GAMEOBJECT_H
#define INTEGRIAN_GAMEOBJECT_H

#include <unordered_map>
#include "TransformComponent.h"

namespace Integrian
{
	class Component;
	class GameObject final  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		GameObject() = default;
		~GameObject();

		void AddComponent(const std::string& name, Component* pComponent);

		void Update(const float elapsedSeconds);
		void FixedUpdate(const float elapsedSeconds);
		void LateUpdate(const float elapsedSeconds);
		
		void Render() const;

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
		
		TransformComponent transform{};
	
	private:
		std::unordered_map<std::string, Component*> m_pComponents;
	};
}
#endif // INTEGRIAN_GAMEOBJECT_H