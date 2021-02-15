#include "pch.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "Timer.h"

Integrian::FPSComponent::FPSComponent(TextComponent* pTextComponent)
	: m_pTextComponent{ pTextComponent }
{
}

void Integrian::FPSComponent::Update(const float)
{
	m_pTextComponent->SetTextToRender("FPS: " + std::to_string(Timer::GetInstance().GetFPS()));
}
