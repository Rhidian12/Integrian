#pragma once
#include <Component.h>
#include <string>

namespace Integrian
{
	class GameObject;
}

class ButtonComponent final : public Integrian::Component
{
public:
	ButtonComponent(Integrian::GameObject* pParent, const std::string& event);

	virtual void PostInitialize() override;

	void SetIsSelected(bool isSelected);
	const bool GetIsSelected() const noexcept;

private:
	std::string m_Event;
	bool m_IsSelected;
};

