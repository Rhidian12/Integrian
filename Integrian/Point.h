#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef ENGINE_POINT_H
#define ENGINE_POINT_H

#include "pch.h"
#include <math.h>
#include "Vector.h"
namespace Engine
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
}

#endif // !ENGINE_POINT_H