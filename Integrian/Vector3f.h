#pragma once

#ifndef INTEGRIAN_VECTOR3_H
#define INTEGRIAN_VECTOR3_H

#include "Vector.h"
#include "Point.h"
#include <iostream>
#include "DivisionByZeroNotPossibleException.h"

namespace Integrian
{
	// == Vector3f (Vector specialisation) ==
	template<typename Type>
	struct Vector<3, Type>
	{
		Vector<3, Type>()
			: x{}
			, y{}
			, z{}
		{}
		Vector<3, Type>(const Type x, const Type y, const Type z)
			: x{ x }
			, y{ y }
			, z{ z }
		{}
		//Vector<2, Type>(const Point<2, Type>& from, const Point<2, Type>& to)
		//	: x{ to.x - from.x }
		//	, y{ to.y - from.y }
		//{}
		Vector<3, Type>(const Vector<3, Type>& v1)
			: x{ v1.x }
			, y{ v1.y }
			, z{ v1.z }
		{}

		Type x, y, z;

#pragma region Arithmetic Operators
		// == Arithmetic Operators ==
		Vector<3, Type> operator+(const Vector<3, Type>& rhs) const noexcept
		{
			return Vector<3, Type>{x + rhs.x, y + rhs.y, z + rhs.z};
		}
		Vector<3, Type> operator-(const Vector<3, Type>& rhs) const noexcept
		{
			return Vector<3, Type>{x - rhs.x, y - rhs.y, z - rhs.z};
		}
		Vector<3, Type> operator*(const Vector<3, Type>& rhs) const noexcept
		{
			return Vector<3, Type>{x* rhs.x, y* rhs.y, z* rhs.z};
		}
		Vector<3, Type> operator*(const Type constant) const noexcept
		{
			return Vector<3, Type>{x* constant, y* constant, z* constant};
		}
		Vector<3, Type> operator/(const Vector<3, Type>& rhs) const
		{
			if (rhs.x == static_cast<Type>(0.f) || rhs.y == static_cast<Type>(0.f) || rhs.z == static_cast<Type>(0.f))
				throw DivisionByZeroNotPossible{};

			return Vector<3, Type>{x / rhs.x, y / rhs.y, z / rhs.z};
		}
		Vector<3, Type> operator/(const Type constant) const
		{
			if (constant == static_cast<Type>(0.f))
				throw DivisionByZeroNotPossible{};

			return Vector<3, Type>{x / constant, y / constant, z / constant};
		}
#pragma endregion

#pragma region Compound Assignment Operators
		// == Compound Assignment Operators ==
		Vector<3, Type>& operator+=(const Vector<3, Type>& rhs) noexcept
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}
		Vector<3, Type>& operator-=(const Vector<3, Type>& rhs) noexcept
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}
		Vector<3, Type>& operator/=(const Vector<3, Type>& rhs) noexcept
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			return *this;
		}
		Vector<3, Type>& operator/=(const Type& rhs) noexcept
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}
		Vector<3, Type>& operator*=(const Vector<3, Type>& rhs) noexcept
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			return *this;
		}
		Vector<3, Type>& operator*=(const Type& rhs) noexcept
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}
#pragma endregion

#pragma region Relational Operators
		// == Relational Operators
		bool operator==(const Vector<3, Type>& other) const noexcept
		{
			constexpr float epsilon{ std::numeric_limits<float>::epsilon() };
			return (abs(x - other.x) <= epsilon) && (abs(y - other.y) <= epsilon) && (abs(z - other.z) <= epsilon);
		}

		bool operator!=(const Vector<3, Type>& other) const noexcept
		{
			return !operator==(other);
		}
#pragma endregion

#pragma region Member Functions
		Type Dot(const Vector<3, Type>& other) const noexcept
		{
			return x * other.x + y * other.y + z * other.z;
		}

		Vector<3, Type> Cross(const Vector<3, Type>& other) const noexcept
		{
			return Vector<3, Type>{
				y* other.z - z * other.y,
					z* other.x - x * other.z,
					x* other.y - y * other.x
			};
		}

		Vector<3, Type> Orthogonal() const noexcept
		{
			return Vector<3, Type>{static_cast<Type>(0.f), z, -y};
		}
#pragma endregion

#pragma region Miscellaneous Operators
		friend std::ostream& operator<<(std::ostream& os, const Vector<3, Type>& vector) noexcept
		{
			os << "X: " << vector.x << ", Y: " << vector.y << ", Z: " << vector.z;
			return os;
		}
#pragma endregion
	};
}

#endif // !ENGINE_VECTOR2_H