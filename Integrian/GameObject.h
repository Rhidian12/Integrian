#pragma once
#ifndef INTEGRIAN_GAMEOBJECT_H
#define INTEGRIAN_GAMEOBJECT_H

#include <vector>

namespace Integrian
{
	class Component;
	class GameObject final  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		GameObject() = default;
		~GameObject() = default;

		void AddComponent(Component* pComponent);

	private:
		std::vector<Component*> m_pComponents; // TODO: Decide this should be a map / vector
	};
}
#endif // INTEGRIAN_GAMEOBJECT_H