#pragma once

#ifndef INTEGRIAN_SHAPE_H
#define INTEGRIAN_SHAPE_H

#include <variant> // std::variant

namespace Integrian
{
	enum class TypeOfShape : uint8_t
	{
		Point		= 0,
		Rectangle	= 1,
		Circle		= 2
	};

	class Shape final
	{
	using VariantShape = std::variant<Point2f, Rectf, Circlef>;
	public:
		Shape(const TypeOfShape shape = TypeOfShape::Point);

		void SetShape(const TypeOfShape shape) noexcept;

		VariantShape&& operator[](const uint8_t index) const noexcept;

	private:
		union ActiveShape
		{
			Point2f m_Point;
			Rectf m_Rectangle;
			Circlef m_Circle;

			VariantShape&& operator[](const TypeOfShape index) const noexcept
			{
				VariantShape variant{};

				switch (index)
				{
				case TypeOfShape::Point:
					variant = m_Point;
					break;
				case TypeOfShape::Rectangle:
					variant = m_Rectangle;
					break;
				case TypeOfShape::Circle:
					variant = m_Circle;
					break;
				default:
					break;
				}

				return std::move(variant);
			}
		};

		ActiveShape m_Shapes;
		TypeOfShape m_TypeOfShape;
	};
}

#endif // !INTEGRIAN_SHAPE_H