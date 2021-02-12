#pragma once
#ifndef INTEGRIAN_PRINTER_H
#define INTEGRIAN_PRINTER_H

#include <string>
#include "Structs.h"

namespace Integrian
{
	class Texture;
	class Printer final // TODO: Put this in a manager which checks if this particular printer has already been made
	{
	public:
		Printer(const std::string& textToRender);
		Printer(const std::string& filePath, const std::string& textToRender);
		Printer(const std::string& filePath, const std::string& textToRender, const int size, const RGBColour& colour);
		~Printer() = default;

		void Render(const Point2f& leftBottom) const;

	private:
		//std::unique_ptr<Texture> m_pFont; // TODO: Figure out why I cannot forward declare Texture in a unique pointer
		Texture* m_pFont;
	};
}

#endif // INTEGRIAN_PRINTER_H