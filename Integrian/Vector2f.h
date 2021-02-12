#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef ENGINE_VECTOR2_H
#define ENGINE_VECTOR2_H

#include "Vector.h"
#include "Point.h"
#include <iostream>
namespace Integrian
{
	// == Vector2f (Vector specialisation) ==
	template<typename Type>
	struct Vector<2, Type>
	{
		Vector<2, Type>() = default;
		Vector<2, Type>(const Type x, const Type y)
			: x{ x }
			, y{ y }
		{
		}
		Vector<2, Type>(const Point<2, Type>& from, const Point<2, Type>& to)
			: x{ to.x - from.x }
			, y{ to.y - from.y }
		{
		}
		Vector<2, Type>(const Vector<2, Type>& v1)
			: x{ v1.x }
			, y{ v1.y }
		{
		}

		Type x, y;

#pragma region Arithmetic Operators
		// == Arithmetic Operators ==
		Vector<2, Type> operator+(const Vector<2, Type>& rhs) const
		{
			return Vector<2, Type>{x + rhs.x, y + rhs.y};
		}
		Vector<2, Type> operator-(const Vector<2, Type>& rhs) const
		{
			return Vector<2, Type>{x - rhs.x, y - rhs.y};
		}
		Vector<2, Type> operator*(const Type& rhs) const
		{
			return Vector<2, Type>{x* rhs, y* rhs};
		}
#pragma endregion

#pragma region Compound Assignment Operators
		// == Compound Assignment Operators ==
		Vector<2, Type> operator+=(const Vector<2, Type>& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		Vector<2, Type> operator-=(const Vector<2, Type>& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}
		Vector<2, Type> operator/=(const Vector<2, Type>& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}
		Vector<2, Type> operator/=(const Type& rhs)
		{
			x /= rhs;
			y /= rhs;
			return *this;
		}
		Vector<2, Type> operator*=(const Vector<2, Type>& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}
		Vector<2, Type> operator*=(const Type& rhs)
		{
			x *= rhs;
			y *= rhs;
			return *this;
		}
#pragma endregion

#pragma region Relational Operators
		// == Relational Operators
		bool operator==(const Vector<2, Type>& other) const
		{
			return AreEqual(x, other.x) && AreEqual(y, other.y);
		}

		bool operator!=(const Vector<2, Type>& other) const
		{
			return !operator==(other);
		}
#pragma endregion

#pragma region Member Functions
		Type Dot(const Vector<2, Type>& other) const
		{
			return x * other.x + y * other.y;
		}

		Type Cross(const Vector<2, Type>& other) const
		{
			return x * other.y - y * other.x;
		}

		Vector<2, Type> Orthogonal() const
		{
			return Vector<2, Type>{ -y, x };
		}
#pragma endregion

#pragma region Miscellaneous Operators
		friend std::ostream& operator<<(std::ostream& os, const Vector<2, Type>& vector)
		{
			os << vector.x << ", " << vector.y << std::endl;
			return os;
		}
#pragma endregion
	};
}

#endif // !ENGINE_VECTOR2_H