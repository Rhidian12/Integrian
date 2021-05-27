#pragma once

#ifndef INTEGRIAN_POINT3_H
#define INTEGRIAN_POINT3_H

#include "Point.h" // Point 
#include "Vector.h" // Vector
#include <iostream>

namespace Integrian
{
	// == Point3f (Point Specialisation) ==
	template<typename Type>
	struct Point<3, Type>
	{
#pragma region Constructors
		Point<3, Type>()
			: x{}
			, y{}
		{}
		Point<3, Type>(const Type x, const Type y, const Type z)
			: x{ x }
			, y{ y }
			, z{ z }
		{}
		Point<3, Type>(const Point<2, Type>& p)
			: x{ p.x }
			, y{ p.y }
			, z{}
		{}
		Point<3, Type>(const Point<3, Type>& p)
			: x{ p.x }
			, y{ p.y }
			, z{ p.z }
		{}
		Point<3, Type>(Point<3, Type>&& other)
			: x{ std::move(other.x) }
			, y{ std::move(other.y) }
			, z{ std::move(other.z) }
		{}
#pragma endregion

#pragma region Copy and Move operator
		Point<3, Type>& operator=(const Point<3, Type>& p)
		{
			x = p.x;
			y = p.y;
			z = p.z;
			return *this;
		}
		Point<3, Type>& operator=(Point<3, Type>&& p)
		{
			x = std::move(p.x);
			y = std::move(p.y);
			z = std::move(p.z);
			return *this;
		}
#pragma endregion

#pragma region Member Variables
		Type x, y, z;
#pragma endregion

#pragma region Arithmetic Operators
		// == Arithmetic Operators ==
		Vector<3, Type> operator-(const Point<3, Type>& rhs) const noexcept
		{
			return Vector<3, Type>{x - rhs.x, y - rhs.y, z - rhs.z};
		}
		Point<3, Type> operator-(const Vector<3, Type>& rhs) const noexcept
		{
			return Point<3, Type>{x - rhs.x, y - rhs.y, z - rhs.z};
		}
		Vector<3, Type> operator+(const Point<3, Type>& rhs) const noexcept
		{
			return Vector<3, Type>{x + rhs.x, y + rhs.y, z + rhs.z};
		}
		Point<3, Type> operator+(const Vector<3, Type>& rhs) const noexcept
		{
			return Point<3, Type>{x + rhs.x, y + rhs.y, z + rhs.z};
		}
		Point<3, Type> operator*(const Point<3, Type>& rhs) const noexcept
		{
			return Point<3, Type>{x* rhs.x, y* rhs.y, z* rhs.z};
		}
#pragma endregion

#pragma region Compound Assignment Operators
		// == Compound Assignment Operators ==
		Point<3, Type>& operator+=(const Vector<3, Type>& rhs) noexcept
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}
		Point<3, Type>& operator-=(const Vector<3, Type>& rhs) noexcept
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}
		Point<3, Type>& operator*=(const Vector<3, Type>& rhs) noexcept
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			return *this;
		}
		Point<3, Type>& operator/=(const Vector<3, Type>& rhs) noexcept
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			return *this;
		}
#pragma endregion

#pragma region Relational Operators
		// == Relational Operators
		bool operator==(const Point<3, Type>& other) const noexcept
		{
			constexpr float epsilon{ std::numeric_limits<float>::epsilon() };
			return (abs(x - other.x) <= epsilon) && (abs(y - other.y) <= epsilon) && (abs(z - other.z) <= epsilon);
		}
		bool operator!=(const Point<3, Type>& other) const noexcept
		{
			return !(*this == other);
		}
#pragma endregion

#pragma region Member Access Operators
		Type& operator[](const int element) noexcept
		{
			// TODO: Switch Point to use a Type[] array
			if (element == 0)
				return x;
			if (element == 1)
				return y;
			if (element == 2)
				return z;
			// TODO: Add an exception here
			return x;
		}
		const Type& operator[](const int element) const noexcept
		{
			// TODO: Switch Point to use a Type[] array
			if (element == 0)
				return x;
			if (element == 1)
				return y;
			if (element == 2)
				return z;
			// TODO: Add an exception here
			return x;
		}
#pragma endregion

#pragma region Miscellaneous Operators
		friend std::ostream& operator<<(std::ostream& os, const Point<3, Type>& point) noexcept
		{
			os << "X: " << point.x << ", Y: " << point.y << ", Z: " << point.z;
			return os;
		}
#pragma endregion
	};
}

#endif // !ENGINE_POINT2_H