#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================

#ifndef INTEGRIAN_POINT2_H
#define INTEGRIAN_POINT2_H

#include "Point.h" // Point 
#include "Vector.h" // Vector

namespace Integrian
{
	// == Point2f (Point Specialisation) ==
	template<typename Type>
	struct Point<2, Type>
	{
#pragma region Constructors
		Point<2, Type>()
			: x{}
			, y{}
		{}
		Point<2, Type>(const Type x, const Type y)
			: x{ x }
			, y{ y }
		{}
		Point<2, Type>(const Point<2, Type>& p)
			: x{ p.x }
			, y{ p.y }
		{}
		Point<2, Type>(Point<2, Type>&& other)
			: x{ std::move(other.x) }
			, y{ std::move(other.y) }
		{}
#pragma endregion

#pragma region Copy and Move operator
		Point<2, Type>& operator=(const Point<2, Type>& p)
		{
			x = p.x;
			y = p.y;
			return *this;
		}
		Point<2, Type>& operator=(Point<2, Type>&& p)
		{
			x = std::move(p.x);
			y = std::move(p.y);
			return *this;
		}
#pragma endregion

#pragma region Member Variables
		Type x, y;
#pragma endregion

#pragma region Arithmetic Operators
		// == Arithmetic Operators ==
		Vector<2, Type> operator-(const Point<2, Type>& rhs) const noexcept
		{
			return Vector<2, Type>{x - rhs.x, y - rhs.y};
		}
		Point<2, Type> operator-(const Vector<2, Type>& rhs) const noexcept
		{
			return Point<2, Type>{x - rhs.x, y - rhs.y};
		}
		Vector<2, Type> operator+(const Point<2, Type>& rhs) const noexcept
		{
			return Vector<2, Type>{x + rhs.x, y + rhs.y};
		}
		Point<2, Type> operator+(const Vector<2, Type>& rhs) const noexcept
		{
			return Point<2, Type>{x + rhs.x, y + rhs.y};
		}
		Point<2, Type> operator*(const Point<2, Type>& rhs) const noexcept
		{
			return Point<2, Type>{x* rhs.x, y* rhs.y};
		}
#pragma endregion

#pragma region Compound Assignment Operators
		// == Compound Assignment Operators ==
		Point<2, Type>& operator+=(const Vector<2, Type>& rhs) noexcept
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		Point<2, Type>& operator-=(const Vector<2, Type>& rhs) noexcept
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}
		Point<2, Type>& operator*=(const Vector<2, Type>& rhs) noexcept
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}
		Point<2, Type>& operator/=(const Vector<2, Type>& rhs) noexcept
		{
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}
#pragma endregion

#pragma region Relational Operators
		// == Relational Operators
		bool operator==(const Point<2, Type>& other) const noexcept
		{
			constexpr float epsilon{ std::numeric_limits<float>::epsilon() };
			return (abs(x - other.x) <= epsilon) && (abs(y - other.y) <= epsilon);
		}
		bool operator!=(const Point<2, Type>& other) const noexcept
		{
			return !(*this == other);
		}
#pragma endregion

#pragma region Miscellaneous Operators
		friend std::ostream& operator<<(std::ostream& os, const Point<2, Type>& point) noexcept
		{
			os << point.x << ", " << point.y;
			return os;
		}
#pragma endregion
	};
}

#endif // !ENGINE_POINT2_H