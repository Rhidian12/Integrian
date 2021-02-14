#pragma once
#ifndef INTEGRIAN_TEXTCOMPONENT_H
#define INTEGRIAN_TEXTCOMPONENT_H

#include "Component.h"

namespace Integrian
{
	class Printer;
	class TextComponent final : public Component  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		TextComponent(const std::string& textToBeRendered);
		// TODO: Add constructor that just takes component name and text to be renderered and transform
		// Resourcemanager should take ownership of fonts 
		~TextComponent();

		virtual void Render(const Point2f& pos) const override;

		void SetTextToRender(const std::string& string);

	private:
		std::string m_TextToBeRendered;
		Printer* m_pPrinter;
	};
}

#endif //INTEGRIAN_TEXTCOMPONENT_H