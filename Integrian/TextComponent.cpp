#include "pch.h"
#include "TextComponent.h"
#include "Printer.h"
#include "Texture.h"
#include "PrinterManager.h"

Integrian::TextComponent::TextComponent()
	: TextComponent{ "" }
{
}

Integrian::TextComponent::TextComponent(const int size, const RGBColour& colour)
	: TextComponent{ "",size,colour }
{
}

Integrian::TextComponent::TextComponent(const std::string& textToBeRendered)
	: TextComponent{ textToBeRendered, 20, RGBColour{} } // default colour is white
{
}

Integrian::TextComponent::TextComponent(const std::string& textToRender, const int size, const RGBColour& colour)
	: m_TextToBeRendered{ textToRender }
	, m_pPrinter{ PrinterManager::GetInstance().AddPrinter(textToRender,size,colour) }
{
}

void Integrian::TextComponent::Render(const Point2f& pos) const
{
	m_pPrinter->Render(pos);
}

void Integrian::TextComponent::SetTextToRender(const std::string& string)
{
	m_TextToBeRendered = string;
	m_pPrinter->SetTextToRender(m_TextToBeRendered);
}

float Integrian::TextComponent::GetHeight() const
{
	return m_pPrinter->GetTexture()->GetHeight();
}
