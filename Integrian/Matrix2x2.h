#pragma once

#ifndef INTEGRIAN_MATRIX2x2_H
#define INTEGRIAN_MATRIX2x2_H

#include "Matrix.h" // Matrix

namespace Integrian
{
	// Matrix2x2 (Matrix Specialisation)
	template<typename Type>
	struct Matrix<2, Type>
	{
#pragma region Constructors
		Matrix<2, Type>() noexcept
			: matrix{}
		{}
		Matrix<2, Type>(const Type a, const Type b, const Type c, const Type d) noexcept
			: matrix{}
		{
			matrix[0][0] = a;
			matrix[1][0] = b; // [ A B ]
			matrix[1][0] = c; // [ C D ]
			matrix[1][1] = d;
		}
		Matrix<2, Type>(const Matrix<2, Type>& other) noexcept
			: matrix{ other.matrix }
		{}
		Matrix<2, Type>(Matrix<2, Type>&& other) noexcept
			: matrix{ other.matrix }
		{
			other.matrix = nullptr;
		}
#pragma endregion

#pragma region Special Member Variables
		inline static Matrix<2, Type> identityMatrix{ static_cast<Type>(1.f), static_cast<Type>(0.f), static_cast<Type>(0.f), static_cast<Type>(1.f) };
#pragma endregion

#pragma region Member Functions
		Matrix<2, Type> Inverse(const Matrix<2, Type>& other) const noexcept
		{
			const Type determinant{ static_cast<Type>(1.f) / (other.matrix[0][0] * other.matrix[1][1] - other.matrix[0][1] * other.matrix[1][0]) };
			return determinant * other;
		}
#pragma endregion

#pragma region Miscellaneous Operators
		Matrix<2, Type>& operator-() noexcept
		{
			for (int i{}; i < 2; ++i)
				for (int j{}; j < 2; ++j)
					matrix[i][j] = -matrix[i][j];
		}
#pragma endregion

#pragma region Arithmetic Operators
		Matrix<2, Type> operator+(const Matrix<2, Type>& rhs) const noexcept
		{
			return Matrix<2, Type>{
				matrix[0][0] + rhs.matrix[0][0],
					matrix[0][1] + rhs.matrix[0][1],
					matrix[1][0] + rhs.matrix[1][0],
					matrix[1][1] + rhs.matrix[1][1] };
		}
		Matrix<2, Type> operator-(const Matrix<2, Type>& rhs) const noexcept
		{
			return Matrix<2, Type>{
				matrix[0][0] - rhs.matrix[0][0],
					matrix[0][1] - rhs.matrix[0][1],
					matrix[1][0] - rhs.matrix[1][0],
					matrix[1][1] - rhs.matrix[1][1] };
		}
		Matrix<2, Type> operator*(const Matrix<2, Type>& rhs) const noexcept
		{
			return Matrix<2, Type>{
				matrix[0][0] * rhs.matrix[0][0] + matrix[0][1] * rhs.matrix[1][0],
					matrix[0][0] * rhs.matrix[0][1] + matrix[0][1] * rhs.matrix[1][1], // [ A B ] * [ E F ] == [ A*E + B*G  |  A*F + B*H ]
					matrix[1][0] * rhs.matrix[0][0] + matrix[1][1] * rhs.matrix[1][0], // [ C D ] * [ G H ] == [ C*E + D*G  |  C*F + D*H ]
					matrix[1][0] * rhs.matrix[0][1] + matrix[1][1] * rhs.matrix[1][1] };
		}
		Matrix<2, Type> operator*(const Matrix<2, Type>& lhs, const Type constant) const noexcept
		{
			return Matrix<2, Type>{
				lhs.matrix[0][0] * constant,
				lhs.matrix[0][1] * constant,
				lhs.matrix[1][0] * constant,
				lhs.matrix[1][1] * constant };
		}
		Matrix<2, Type> operator*(const Type constant, const Matrix<2, Type>& rhs) const noexcept
		{
			return rhs * constant;
		}
		Matrix<2, Type> operator/(const Matrix<2, Type>& lhs, const Matrix<2, Type>& rhs) const
		{

		}
#pragma endregion

#pragma region Compound Assignment Operators
		Matrix<2, Type> opr
#pragma endregion
	};
}

#endif // !INTEGRIAN_MATRIX2x2_H
