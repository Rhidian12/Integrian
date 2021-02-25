#pragma once
#ifndef INTEGRIAN_PRINTER_H
#define INTEGRIAN_PRINTER_H

#include <string>
#include "Structs.h"

namespace Integrian
{
	class Texture;
	class Printer final
	{
	public:
		void Render(const Point2f& leftBottom, const std::string& textToRender) const;

		[[nodiscard]] Texture* GetTexture() const;

	private:
		friend class PrinterManager;
		Printer(Texture* pFont);
		~Printer() = default;
		[[nodiscard]] Rectf GetSourceRect(const char c) const;

		Texture* m_pFont;
		const float m_CharWidth;
	};
}

#endif // INTEGRIAN_PRINTER_H