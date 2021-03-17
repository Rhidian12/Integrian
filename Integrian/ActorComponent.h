#pragma once
#ifndef INTEGRIAN_ACTORCOMPONENT_H
#define INTEGRIAN_ACTORCOMPONENT_H

#include "Component.h"
#include "GameInput.h"
#include <memory>
#include "Observer.h"
#include "Subject.h"

namespace Integrian
{
	class Command;
	class ActorComponent : public Component
	{
	public:
		ActorComponent();
		virtual ~ActorComponent() = default;

		template<typename ... Args>
		void AddObserver(Observer<Args...>* pObserver)
		{
			m_pSubject->AddObserver(pObserver);
		}

		void Invoke(const std::string& event);

	private:
		std::unique_ptr<Subject> m_pSubject;
	};
}

#endif // !INTEGRIAN_ACTORCOMPONENT_H