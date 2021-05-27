#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef INTEGRIAN_VECTOR_H
#define INTEGRIAN_VECTOR_H

#include "MagnitudeZeroException.h"
#include <math.h>
#include <limits> // std::numeric_limits
namespace Integrian
{
	template<int V, typename Type>
	struct Vector
	{
		Type x, y, z;
	};

	// == Non-Member Methods That Are Useful For All Vectors ==
	template<int V, typename Type>
	Type MagnitudeSquared(const Vector<V, Type>& v1) noexcept
	{
		return v1.Dot(v1);
	}

	template<int V, typename Type>
	Type Magnitude(const Vector<V, Type>& v1) noexcept
	{
		return static_cast<Type>(sqrt(MagnitudeSquared(v1)));
	}

	template<int V, typename Type>
	Type Normalize(Vector<V, Type>& v1)
	{
		const Type magnitude{ Magnitude(v1) };

		if (magnitude == static_cast<Type>(0))
			throw MagnitudeZeroException{};

		v1 /= magnitude;
		return magnitude;
	}

	template<int V, typename Type>
	Vector<V, Type> GetNormalized(const Vector<V, Type>& v1)
	{
		Vector<V, Type> temp{ v1 };
		Normalize(temp);
		return temp;
	}
	
	//template<int V, typename Type>
	//Type Dot(const Vector<V, Type>& v1, const Vector<V, Type>& v2)
	//{
	//	return v1.x * v2.x + v1.y * v2.y;
	//}
	//
	//template<int V, typename Type>
	//Type Cross(const Vector<V, Type>& v1, const Vector<V, Type>& v2)
	//{
	//	return v1.x * v2.y - v1.y * v2.x;
	//}
}

#endif // !ENGINE_VECTOR_H