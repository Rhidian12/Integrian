#include "pch.h"
#include "Printer.h"
#include "Texture.h"

Integrian::Printer::Printer(const std::string& textToRender)
	: Printer{ "../Data/Fonts/RobotoMono-Regular.ttf", textToRender }
{
}

Integrian::Printer::Printer(const std::string& filePath, const std::string& textToRender)
	: Printer{ filePath, textToRender, 20, RGBColour{255.f,255.f,255.f} }
{
}

Integrian::Printer::Printer(const std::string& filePath, const std::string& textToRender, const int size, const RGBColour& colour)
	: m_pFont{ new Texture{textToRender,filePath,size,colour} }
{
}

void Integrian::Printer::Render(const Point2f& leftBottom) const
{
	m_pFont->Draw(leftBottom);
}
