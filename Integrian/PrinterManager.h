#pragma once
#ifndef INTEGRIAN_PRINTERMANAGER_H
#define INTEGRIAN_PRINTERMANAGER_H

#include "Singleton.h" // Singleton
#include <vector> // std::vector

namespace Integrian
{
	class Printer;
	class PrinterManager final : public Singleton<PrinterManager>
	{
	public:
		virtual ~PrinterManager();

		Printer* AddPrinter(const int size, const RGBColour& colour);

	private:
		PrinterManager() = default;
		friend class Singleton<PrinterManager>;

		const std::string m_FilePath{ "Fonts/RobotoMono-Regular.ttf" };
		std::vector<Printer*> m_pPrinters;
	};
}

#endif // INTEGRIAN_PRINTERMANAGER_H