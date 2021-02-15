#pragma once
#ifndef INTEGRIAN_TEXTCOMPONENT_H
#define INTEGRIAN_TEXTCOMPONENT_H

#include "Component.h"

namespace Integrian
{
	class Printer;
	class Texture;
	class TextComponent : public Component  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		TextComponent();
		TextComponent(const int size, const RGBColour& colour);
		TextComponent(const std::string& textToBeRendered);
		TextComponent(const std::string& textToRender, const int size, const RGBColour& colour);
		virtual ~TextComponent() = default;

		virtual void Render(const Point2f& pos) const override;

		void SetTextToRender(const std::string& string);

		[[nodiscard]] float GetWidth() const;
		[[nodiscard]] float GetHeight() const;

	private:
		std::string m_TextToBeRendered;
		Printer* m_pPrinter;
	};
}

#endif //INTEGRIAN_TEXTCOMPONENT_H