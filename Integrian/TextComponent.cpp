#include "IntegrianPCH.h" // precompiled header
#include "TextComponent.h" // header
#include "Printer.h" // printer
#include "Texture.h" // texture
#include "PrinterManager.h" // printermanager
#include "GameObject.h" // GameObject

Integrian::TextComponent::TextComponent(GameObject* pParent)
	: TextComponent{ pParent, "" }
{
}

Integrian::TextComponent::TextComponent(GameObject* pParent, const int size, const RGBColour& colour)
	: TextComponent{ pParent, "",size,colour }
{
}

Integrian::TextComponent::TextComponent(GameObject* pParent, const std::string& textToBeRendered)
	: TextComponent{ pParent, textToBeRendered, 20, RGBColour{} } // default colour is white
{
}

Integrian::TextComponent::TextComponent(GameObject* pParent, const std::string& textToRender, const int size, const RGBColour& colour)
	: Component{ pParent }
	, m_TextToBeRendered{ textToRender }
	, m_pPrinter{ PrinterManager::GetInstance().AddPrinter(size,colour) }
{
}

void Integrian::TextComponent::Render() const
{
	m_pPrinter->Render(m_pParent->transform.GetPosition(), m_TextToBeRendered);
}

void Integrian::TextComponent::SetTextToRender(const std::string& string)
{
	m_TextToBeRendered = string;
}

const std::string& Integrian::TextComponent::GetTextToRender() const
{
	return m_TextToBeRendered;
}

float Integrian::TextComponent::GetWidth() const
{
	return m_pPrinter->GetTexture()->GetWidth();
}

float Integrian::TextComponent::GetHeight() const
{
	return m_pPrinter->GetTexture()->GetHeight();
}
