#include "IntegrianPCH.h" // precompiled header
#include "FPSComponent.h" // Header 
#include "TextComponent.h" // text component
#include "Timer.h" // Timer

Integrian::FPSComponent::FPSComponent(TextComponent* pTextComponent)
	: m_pTextComponent{ pTextComponent }
{
}

void Integrian::FPSComponent::Update(const float)
{
	m_pTextComponent->SetTextToRender("FPS: " + std::to_string(Timer::GetInstance().GetFPS()));
}

void Integrian::FPSComponent::SetFPS(const int value)
{
	m_pTextComponent->SetTextToRender("FPS: " + std::to_string(value));
}
