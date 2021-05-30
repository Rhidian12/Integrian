#pragma once
#ifndef INTEGRIAN_GAMEOBJECT_H
#define INTEGRIAN_GAMEOBJECT_H

#include <vector> // std::vector
#include "TransformComponent.h" // transformcomponent
#include "Logger.h" // Logger
#include <type_traits> // std::is_base_of_v, std::enable_if_t

// http://scottmeyers.blogspot.com/2015/09/should-you-be-using-something-instead.html
// I dont think this will ever be necessary

namespace Integrian
{
	class Component;
	class Command;
	class GameObject final  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		GameObject() = default;
		~GameObject();

		void Initialize();
		void PostInitialize();

		void AddComponent(Component* pComponent);

		void Update(const float elapsedSeconds);
		void FixedUpdate(const float elapsedSeconds);
		void LateUpdate(const float elapsedSeconds);

		void Render() const;

		void SetIsActive(bool isActive) noexcept;
		void MarkForDeletion(bool markedForDeletion = true) noexcept;

		[[nodiscard]] bool GetIsActive() const noexcept;
		[[nodiscard]] bool GetIsMarkedForDeletion() const noexcept;

		template<typename Type, typename = std::enable_if_t<std::is_base_of_v<Component, Type>>> // sfinae
		inline [[nodiscard]] Type* GetComponentByType() const
		{
			for (Component* pComponent : m_pComponents)
				if (typeid(*pComponent) == typeid(Type))
					return static_cast<Type*>(pComponent);

			Logger::LogError("GetComponentByType returned a nullptr\n");
			return nullptr;
		}

		TransformComponent transform{ this };

	private:
		std::vector<Component*> m_pComponents;
		bool m_IsActive{ true };
		bool m_MarkedForDeletion{};
	};
}
#endif // INTEGRIAN_GAMEOBJECT_H