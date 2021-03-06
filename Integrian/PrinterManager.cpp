#include "IntegrianPCH.h" // precompiled header
#include "PrinterManager.h" // header

#include "PossibleCharacters.h" // possible characters
#include "Printer.h" // printer
#include "TextureManager.h" // texture manager

Integrian::PrinterManager::~PrinterManager()
{
	for (Printer* pPrinter : m_pPrinters)
		SafeDelete(pPrinter);
}

Integrian::Printer* Integrian::PrinterManager::AddPrinter(const int size, const RGBColour& colour)
{
	const std::string name{ m_FilePath + std::to_string(size) + colour.ToString() };
	const std::unordered_map<std::string, Texture*>::const_iterator hasPrinterBeenMade = TextureManager::GetInstance().GetTextures().find(name);
	if (hasPrinterBeenMade == TextureManager::GetInstance().GetTextures().cend())
	{
		TextureManager::GetInstance().AddTexture(name, m_FilePath, PossibleCharacters::possibleChars, size, colour);
		Printer* pPrinter{ new Printer{TextureManager::GetInstance().GetTextures().find(name)->second} };
		m_pPrinters.push_back(pPrinter);
		return pPrinter;
	}
	else
	{
		const std::vector<Printer*>::const_iterator existingPrinter = std::find_if(m_pPrinters.cbegin(), m_pPrinters.cend(), [&hasPrinterBeenMade](Printer* pPrinter)->bool
			{
				return hasPrinterBeenMade->second == pPrinter->GetTexture();
			});

		return *existingPrinter;
	}
}

Integrian::Printer* Integrian::PrinterManager::AddPrinter(const std::string& fontPath, const int size, const RGBColour& colour)
{
	const std::string name{ fontPath + std::to_string(size) + colour.ToString() };
	const std::unordered_map<std::string, Texture*>::const_iterator hasPrinterBeenMade = TextureManager::GetInstance().GetTextures().find(name);
	if (hasPrinterBeenMade == TextureManager::GetInstance().GetTextures().cend())
	{
		TextureManager::GetInstance().AddTexture(name, fontPath, PossibleCharacters::possibleChars, size, colour);
		Printer* pPrinter{ new Printer{TextureManager::GetInstance().GetTextures().find(name)->second} };
		m_pPrinters.push_back(pPrinter);
		return pPrinter;
	}
	else
	{
		const std::vector<Printer*>::const_iterator existingPrinter = std::find_if(m_pPrinters.cbegin(), m_pPrinters.cend(), [&hasPrinterBeenMade](Printer* pPrinter)->bool
			{
				return hasPrinterBeenMade->second == pPrinter->GetTexture();
			});

		return *existingPrinter;
	}
}

Integrian::Printer* Integrian::PrinterManager::AddPrinter(Texture* pFont)
{
	const std::string name{ TextureManager::GetInstance().GetTextureName(pFont) };
	const std::vector<Printer*>::const_iterator hasPrinterBeenMade = std::find_if(m_pPrinters.cbegin(), m_pPrinters.cend(), [pFont](Printer* pPrinter)
		{
			return pPrinter->GetTexture() == pFont;
		});
	if (hasPrinterBeenMade == m_pPrinters.cend())
	{
		Printer* pPrinter{ new Printer{pFont} };
		m_pPrinters.push_back(pPrinter);
		return pPrinter;
	}
	else
	{
		const std::vector<Printer*>::const_iterator existingPrinter = std::find_if(m_pPrinters.cbegin(), m_pPrinters.cend(), [&hasPrinterBeenMade](Printer* pPrinter)->bool
			{
				return (*hasPrinterBeenMade)->GetTexture() == pPrinter->GetTexture();
			});

		return *existingPrinter;
	}
}
