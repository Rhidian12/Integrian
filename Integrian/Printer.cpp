#include "pch.h"
#include "Printer.h"
#include "Texture.h"
#include "TextureManager.h"
#include "PossibleCharacters.h"

Integrian::Printer::Printer(Texture* pFont)
	: m_pFont(pFont)
	, m_CharWidth{ (m_pFont->GetWidth() / PossibleCharacters::sizeOfPossibleChars) }
{
}

void Integrian::Printer::Render(const Point2f& leftBottom, const std::string& textToRender) const
{
	for (size_t i{}; i < textToRender.size(); ++i)
	{
		const Rectf destRect{ leftBottom.x + m_CharWidth * i,leftBottom.y,m_CharWidth,m_pFont->GetHeight() };
		m_pFont->Draw(destRect, GetSourceRect(textToRender[i]));
	}
}

Integrian::Texture* Integrian::Printer::GetTexture() const
{
	return m_pFont;
}

Integrian::Rectf Integrian::Printer::GetSourceRect(const char c) const
{
	const size_t positionOfChar{ PossibleCharacters::possibleChars.find(c) };
	Rectf srcRect{ m_CharWidth * positionOfChar,0.f,m_CharWidth,m_pFont->GetHeight() };
	return srcRect;
}
