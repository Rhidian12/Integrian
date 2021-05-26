#pragma once

#ifndef INTEGRIAN_SHAPE_H
#define INTEGRIAN_SHAPE_H

namespace Integrian
{
	enum class TypeOfShape
	{
		Point		= 0,
		Rectangle	= 1,
		Circle		= 2
	};

	class Shape final
	{
	public:
		Shape(const TypeOfShape shape);

	private:
		union
		{
			Point2f m_Point;
			Rectf m_Rectangle;
			Circlef m_Circle;
		};

		TypeOfShape m_TypeOfShape;
	};
}

#endif // !INTEGRIAN_SHAPE_H