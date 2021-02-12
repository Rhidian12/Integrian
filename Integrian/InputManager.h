#pragma once
// ====================================
// Author: Rhidian De Wit
// January 2021
// ====================================
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <iostream>
// Reference: https://stackoverflow.com/questions/25963966/c-function-pointer-callback-without-inheritance
enum class MouseButton
{
	LMB = 0,
	MMB = 1,
	RMB = 2,
	LMBAndRMB = 3,
	LMBAndMMB = 4,
	RMBandMMB = 5,
};
class InputManager final
{
	using KeybindFunction = std::function<void(const float)>;
	using MouseFunction = std::function<void()>;
	using KeybindFunctionWrapperPair = std::pair<Uint8, std::vector<KeybindFunction>>;
	using MouseFunctionWrapperPair = std::pair<MouseButton, std::vector<MouseFunction>>;
public:
	static InputManager* GetInstance();
	~InputManager();
	static void Cleanup();

	template<typename Type>
	inline void AddMemberFunctionWrapper(const Uint8 key, Type* pObject, void(Type::* pMemberFunction)(const float), bool continuousCall)
	{
		if (continuousCall)
			m_KeyDownKeybindFunctions[key].push_back(std::bind(pMemberFunction, pObject, std::placeholders::_1));
		else
			m_KeyUpKeybindFunctions[key].push_back(std::bind(pMemberFunction, pObject, std::placeholders::_1));
	}
	template<typename Type>
	inline void AddMemberFunctionWrapper(const MouseButton& key, Type* pObject, void(Type::* pMemberFunction)(), bool mouseDown)
	{
		if (mouseDown)
			m_MouseDownMouseFunctions[key].push_back(std::bind(pMemberFunction, pObject));
		else
			m_MouseUpMouseFunctions[key].push_back(std::bind(pMemberFunction, pObject));
	}
	inline void AddFunctionWrapper(const Uint8& key, void function(const float), bool continousCall)
	{
		if(continousCall)
			m_KeyDownKeybindFunctions[key].push_back(function);
		else
			m_KeyUpKeybindFunctions[key].push_back(function);
	}

	void HandleInput(const float dt);

	void SetWindowSize(const uint32_t width, const uint32_t height);

	const Integrian::Point2f& GetMousePosition() const;

private:
	InputManager() = default;
	static InputManager* m_pInstance;

	std::unordered_map<Uint8, std::vector<KeybindFunction>> m_KeyDownKeybindFunctions;
	std::unordered_map<Uint8, std::vector<KeybindFunction>> m_KeyUpKeybindFunctions;
	std::unordered_map<MouseButton, std::vector<MouseFunction>> m_MouseDownMouseFunctions;
	std::unordered_map<MouseButton, std::vector<MouseFunction>> m_MouseUpMouseFunctions;
	
	Integrian::Point2f m_MousePosition{};
	uint32_t m_WindowWidth{};
	uint32_t m_WindowHeight{};
};

#endif // !INPUTMANAGER_H