#pragma once
#ifndef INTEGRIAN_COMPONENT_H
#define INTEGRIAN_COMPONENT_H

#include <string>
#include <vector>

namespace Integrian
{
	class Component abstract
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void Render() const = 0;

		// TextComponent <== Component
		// TextComponent* pointer = GetComponent<TextComponent>();

		template<typename Type>
		inline Type* GetComponent() const
		{
			for(Component* pComponent : m_pComponents)
			{
				if (typeid(*pComponent) == typeid(Type))
					return static_cast<Type*>(pComponent);
			}

			// TODO: Make Logger print a message saying this returned nothing
			return nullptr;
		}

	protected:
		std::vector<Component*> m_pComponents;

	private:
	};
}

#endif //!INTEGRIAN_COMPONENT_H