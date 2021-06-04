#pragma once
#include <Component.h>
#include <PossibleInputs.h>
#include <ListenerInterface.h>
#include <array>

namespace Integrian
{
	class GameObject;
	class FiniteStateMachineComponent;
}

enum KeybindMovementDirection
{
	RightTop = 0,
	RightBottom = 1,
	LeftBottom = 2,
	LeftTop = 3
};

struct KeybindMovement final
{
	using Type = std::underlying_type_t<Integrian::KeyboardInput>;

	
	KeybindMovement(const Integrian::KeyboardInput input = Integrian::KeyboardInput::INVALID)
		: value{ static_cast<Type>(input) }
	{}

	constexpr operator Integrian::KeyboardInput() const noexcept
	{
		return static_cast<Integrian::KeyboardInput>(value);
	}

	Type value;
};

class QbertFSM final : public Integrian::Component, public Integrian::IListener
{
public:
	QbertFSM(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	virtual bool OnEvent(const Integrian::Event& event) override;

private:
	Integrian::FiniteStateMachineComponent* m_pFSM;
	std::array<KeybindMovement, 4> m_Keybinds;
};

