#pragma once
#ifndef INTEGRIAN_MOUSE_H
#define INTEGRIAN_MOUSE_H

#include "GameInput.h" // GameInput
#include <unordered_map> // std::unordered_map
#include "ListenerInterface.h" // IListener
#include <vector> // std::vector

namespace Integrian
{
	class Mouse final : public IListener
	{
	public:
		~Mouse();

		virtual bool OnEvent(const Event& event) override;

	private:
		Mouse() = default;
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&& other);
		Mouse& operator=(const Mouse&) = delete;
		friend class InputManager;

		void AddCommand(const MouseButton mouseButton, const State keyState, const std::function<void()>& pCommand);
		void ExecuteCommands();

		[[nodiscard]] bool IsPressed(const MouseButton gameInput) const;
		bool WasPressed(const State previousState) const;
		State GetKeystate(const MouseButton mouseButton, const State previousState) const;
		[[nodiscard]] const std::unordered_map<MouseButton, std::vector<CommandAndButton>>& GetCommands() const;
		
		void RemoveCommand(const std::function<void()>& pCommand);

		std::unordered_map<MouseButton, std::vector<CommandAndButton>> m_MouseCommands{};
		std::vector<MouseButton> m_KeysToBeRemoved{};

		using CommandPair = std::pair<MouseButton, std::vector<CommandAndButton>>;
		using UMapIterator = std::unordered_map<MouseButton, std::vector<CommandAndButton>>::iterator;
	
		inline Mouse& operator=(Mouse&& other) noexcept
		{
			m_MouseCommands = other.m_MouseCommands;
			other.m_MouseCommands.clear();

			return *this;
		}
	};
}

#endif // !INTEGRIAN_MOUSE_H