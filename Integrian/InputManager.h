#pragma once
// ====================================
// Author: Rhidian De Wit
// January 2021
// ====================================
#ifndef INTEGRIAN_INPUTMANAGER_H
#define INTEGRIAN_INPUTMANAGER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <iostream>

#include "Command.h"
#include "Timer.h"
#include "PossibleInputs.h"
// Reference: https://stackoverflow.com/questions/25963966/c-function-pointer-callback-without-inheritance

namespace Integrian
{
	class Command;
	
	enum class MouseButton
	{
		LMB = 0,
		MMB = 1,
		RMB = 2,
		LMBAndRMB = 3,
		LMBAndMMB = 4,
		RMBandMMB = 5,
	};

	class InputManager final : public Singleton<InputManager>
	{
		using KeybindFunctionWrapperPair	= std::pair<Uint8, std::vector<Command*>>;
		using MouseFunctionWrapperPair		= std::pair<MouseButton, std::vector<Command*>>;
	public:
		virtual ~InputManager();

		template<typename Type>
		inline void AddCommand(const Uint8 key, Type* pObject, void(Type::* pCommand)(), bool keyDown)
		{
			if (keyDown)
				m_KeyDownKeybindCommands[key].push_back(std::bind(pObject, pCommand));
			else
				m_KeyUpKeybindCommands[key].push_back(std::bind(pObject, pCommand));
		}
		template<typename Type>
		inline void AddCommand(const MouseButton key, Type* pObject, void(Type::* pCommand)(), bool mouseDown)
		{
			if (mouseDown)
				m_MouseDownMouseCommands[key].push_back(std::bind(pObject, pCommand));
			else
				m_MouseUpMouseCommands[key].push_back(std::bind(pObject, pCommand));
		}

		void HandleInput();

		void SetWindowSize(const uint32_t width, const uint32_t height);

		[[nodiscard]] const Point2f& GetMousePosition() const;

	private:
		InputManager();
		friend class Singleton<InputManager>;

		std::unordered_map<Uint8,		std::vector<Command*>>	m_KeyDownKeybindCommands;
		std::unordered_map<Uint8,		std::vector<Command*>>	m_KeyUpKeybindCommands;
		std::unordered_map<MouseButton, std::vector<Command*>>	m_MouseDownMouseCommands;
		std::unordered_map<MouseButton, std::vector<Command*>>	m_MouseUpMouseCommands;

		Point2f m_MousePosition;
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;
	};
}

#endif // !INTEGRIAN_INPUTMANAGER_H