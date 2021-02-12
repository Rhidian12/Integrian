#include "pch.h"
#include "TextComponent.h"
#include "Printer.h"

Integrian::TextComponent::TextComponent(const std::string& textToBeRendered)
	: Component{ "TextComponent" }
	, m_TextToBeRendered{ textToBeRendered }
	, m_pPrinter{ new Printer{textToBeRendered} }
{
}

Integrian::TextComponent::~TextComponent()
{
	SAFE_DELETE(m_pPrinter);
}

void Integrian::TextComponent::Render() const
{
	m_pPrinter->Render(Point2f{});
}