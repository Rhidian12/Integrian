#pragma once
#ifndef INTEGRIAN_TEXTCOMPONENT_H
#define INTEGRIAN_TEXTCOMPONENT_H

#include "Component.h" // Component

namespace Integrian
{
	class GameObject;
	class Printer;
	class Texture;
	class TextComponent : public Component  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		TextComponent(GameObject* pParent);
		TextComponent(GameObject* pParent, const int size, const RGBColour& colour);
		TextComponent(GameObject* pParent, const std::string& textToBeRendered);
		TextComponent(GameObject* pParent, const std::string& textToRender, const int size, const RGBColour& colour);
		virtual ~TextComponent() = default;

		virtual void Render(const Point2f& pos) const override;

		void SetTextToRender(const std::string& string);
		const std::string& GetTextToRender() const;

		[[nodiscard]] float GetWidth() const;
		[[nodiscard]] float GetHeight() const;

	private:
		std::string m_TextToBeRendered;
		Printer* m_pPrinter;
	};
}

#endif //INTEGRIAN_TEXTCOMPONENT_H