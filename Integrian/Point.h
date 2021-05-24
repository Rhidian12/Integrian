#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef INTEGRIAN_POINT_H
#define INTEGRIAN_POINT_H

#include <cmath> //
#include "Vector.h" // Vector
namespace Integrian
{
	template<int P, typename Type>
	struct Point
	{
		Type x, y;

	};

	// == Non-Member Functions That Are Useful For All Points ==
	template<int P, typename Type>
	Type DistanceSquared(const Point<P, Type>& p1, const Point<P, Type>& p2)
	{
		const Vector<P, Type> vector{ p1, p2 };
		return static_cast<Type>(MagnitudeSquared(vector));
	}
	template<int P, typename Type>
	Type Distance(const Point<P, Type>& p1, const Point<P, Type>& p2)
	{
		const Vector<P, Type> vector{ p1, p2 };
		return static_cast<Type>(sqrt(MagnitudeSquared(vector)));
	}
	template<int P, typename Type>
	bool AreEqual(const Point<P, Type>& p1, const Point<P, Type>& p2, const float epsilon = std::numeric_limits<float>::epsilon())
	{
		return (abs(p1.x - p2.x) <= epsilon) && (abs(p1.y - p2.y) <= epsilon);
	}
}

#endif // !ENGINE_POINT_H