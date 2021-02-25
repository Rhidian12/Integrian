#pragma once
#ifndef INTEGRIAN_ACTORCOMPONENT_H
#define INTEGRIAN_ACTORCOMPONENT_H

#include "Component.h"
#include "GameInput.h"
#include <memory>

namespace Integrian
{
	class Command;
	class Subject;
	class Observer;
	class ActorComponent : public Component
	{
	public:
		ActorComponent();
		virtual ~ActorComponent() = default;

		void AddCommand(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex = 0);
		void AddObserver(std::weak_ptr<Observer> pObserver);
		void Invoke(const std::string& event);

	private:
		std::unique_ptr<Subject> m_pSubject;
	};
}

#endif // !INTEGRIAN_ACTORCOMPONENT_H