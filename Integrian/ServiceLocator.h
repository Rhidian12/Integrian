#pragma once
#ifndef INTEGRIAN_SERVICELOCATOR_H
#define INTEGRIAN_SERVICELOCATOR_H

#include "Singleton.h"
#include "InputManager.h"
#include "CommandManager.h"
#include "PrinterManager.h"
#include "TextureManager.h"

namespace Integrian
{
	class ServiceLocator final : public Singleton<ServiceLocator>
	{
	public:
		InputManager m_Inputmanager{ __FILE__, __LINE__ };
		CommandManager m_CommandManager{ __FILE__, __LINE__ };
		PrinterManager m_PrinterManager{ __FILE__, __LINE__ };
		TextureManager m_TextureManager{ __FILE__, __LINE__ };

	private:
		friend class Singleton<ServiceLocator>;
	};
}

#endif // !INTEGRIAN_SERVICELOCATOR_H