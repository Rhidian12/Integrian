#pragma once
#ifndef INTEGRIAN_PRINTERMANAGER_H
#define INTEGRIAN_PRINTERMANAGER_H

#include "Singleton.h"
#include <vector>

namespace Integrian
{
	class Printer;
	class PrinterManager final
	{
	public:
		PrinterManager(const char* pFile, const int line);
		virtual ~PrinterManager();

		Printer* AddPrinter(const int size, const RGBColour& colour);

	private:
		inline static bool m_IsInstatiated{};

		const std::string m_FilePath{ "Fonts/RobotoMono-Regular.ttf" };
		std::vector<Printer*> m_pPrinters;
	};
}

#endif // INTEGRIAN_PRINTERMANAGER_H