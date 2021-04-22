#pragma once
#ifndef INTEGRIAN_PRINTER_H
#define INTEGRIAN_PRINTER_H

#include <string> // std::string

namespace Integrian
{
	class Texture;
	class Printer final
	{
	public:
		~Printer() = default;
		void Render(const Point2f& leftBottom, const std::string& textToRender) const;

		[[nodiscard]] Texture* GetTexture() const;

	private:
		friend class PrinterManager;
		Printer(Texture* pFont);
		[[nodiscard]] Rectf GetSourceRect(const char c) const;

		Texture* m_pFont;
		const float m_CharWidth;
	};
}

#endif // INTEGRIAN_PRINTER_H