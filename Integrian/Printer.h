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
		void Render(const Point2f& leftBottom) const;

		void SetTextToRender(const std::string& string);

		[[nodiscard]] Texture* GetTexture() const;

	private:
		friend class PrinterManager;
		Printer(Texture* pFont, const std::string& textToRender);
		~Printer() = default;
		[[nodiscard]] Rectf GetSourceRect(const char c) const;

		Texture* m_pFont;
		const float m_CharWidth;
		std::string m_TextToRender;
	};
}

#endif // INTEGRIAN_PRINTER_H