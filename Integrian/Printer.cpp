#include "pch.h"
#include "Printer.h"
#include "Texture.h"
#include "TextureManager.h"
#include "PossibleCharacters.h"

Integrian::Printer::Printer(const std::string& textToRender)
	: Printer{ "Data/Fonts/RobotoMono-Regular.ttf", textToRender }
{
}

Integrian::Printer::Printer(const std::string& filePath, const std::string& textToRender)
	: Printer{ filePath, textToRender, 20, RGBColour{255.f,255.f,255.f} }
{
}

Integrian::Printer::Printer(const std::string& filePath, const std::string& textToRender, const int size, const RGBColour& colour)
	: m_pFont{}
	, m_TextToRender{ textToRender }
{
	const std::string name{ filePath + std::to_string(size) + colour.ToString() };
	if (TextureManager::GetInstance().GetTextures().find(name) == TextureManager::GetInstance().GetTextures().end())
		TextureManager::GetInstance().AddTexture(name, filePath, PossibleCharacters::possibleChars, size, colour);

	m_pFont = TextureManager::GetInstance().GetTextures().find(name)->second;
}

void Integrian::Printer::Render(const Point2f& leftBottom) const
{
	const float charWidth{ (m_pFont->GetWidth() / PossibleCharacters::sizeOfPossibleChars) };
	for (size_t i{}; i < m_TextToRender.size(); ++i)
	{
		const Rectf destRect{ leftBottom.x + charWidth * i,leftBottom.y,charWidth,m_pFont->GetHeight() };
		m_pFont->Draw(destRect, GetSourceRect(m_TextToRender[i]));
	}
}

void Integrian::Printer::SetTextToRender(const std::string& string)
{
	m_TextToRender = string;
}

Integrian::Rectf Integrian::Printer::GetSourceRect(const char c) const
{
	const size_t positionOfChar{ PossibleCharacters::possibleChars.find(c) };
	const float charWidth{ (m_pFont->GetWidth() / PossibleCharacters::sizeOfPossibleChars) };
	Rectf srcRect{ charWidth * positionOfChar,0.f,charWidth,m_pFont->GetHeight() };
	return srcRect;
}
