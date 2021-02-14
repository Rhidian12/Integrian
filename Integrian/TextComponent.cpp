#include "pch.h"
#include "TextComponent.h"
#include "Printer.h"

Integrian::TextComponent::TextComponent(const std::string& textToBeRendered)
	: m_TextToBeRendered{ textToBeRendered }
	, m_pPrinter{ new Printer{textToBeRendered} }
{
}

Integrian::TextComponent::~TextComponent()
{
	SAFE_DELETE(m_pPrinter);
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
