#pragma once

#ifndef INTEGRIAN_MATRIX2x2_H
#define INTEGRIAN_MATRIX2x2_H

#include "MatrixDivisionNotPossibleException.h" // MatrixDivisionNotPossibleException
#include "Matrix.h" // Matrix
#include <iostream> // std::ostream

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
			matrix[0][1] = b; // [ A B ]
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
		~Matrix<2, Type>()
		{
			delete[] matrix;
		}
#pragma endregion

#pragma region Member Variables
		Type(*matrix)[2] { new Type[2][2] };

		inline static Matrix<2, Type> identityMatrix{ static_cast<Type>(1.f), static_cast<Type>(0.f), static_cast<Type>(0.f), static_cast<Type>(1.f) };
#pragma endregion

#pragma region Member Functions
		const Type GetDeterminant() const
		{
			if((matrix[0][0] == static_cast<Type>(0.f) || matrix[1][1] == static_cast<Type>(0.f)) && (matrix[0][1] == static_cast<Type>(0.f) || matrix[1][0] == static_cast<Type>(0.f)))
				throw MatrixDivisionNotPossibleException{};

			return static_cast<Type>(1.f) / (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
		}

		Matrix<2, Type> Inverse() const
		{
			return GetDeterminant() * (*this);
		}

		Matrix<2, Type> Transpose() const noexcept
		{
			Matrix<2, Type> tempMatrix{ *this };
			const Type tempValue{ tempMatrix[0][1] }; // [ A B ] == [ A C ]
			tempMatrix[0][1] = tempMatrix[1][0];	  // [ C D ] == [ B D ]
			tempMatrix[1][0] = tempValue;
			return tempMatrix;
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
		Matrix<2, Type> operator*(const Type constant) const noexcept
		{
			return Matrix<2, Type>{
					matrix[0][0] * constant,
					matrix[0][1] * constant,
					matrix[1][0] * constant,
					matrix[1][1] * constant };
		}
		Matrix<2, Type> operator/(const Matrix<2, Type>& rhs) const
		{
			Matrix<2, Type> inverse{ rhs.Inverse() };

			if (rhs * inverse != identityMatrix)
				throw MatrixDivisionNotPossibleException{};

			return matrix * inverse;
		}
#pragma endregion

#pragma region Compound Assignment Operators
		Matrix<2, Type>& operator+=(const Matrix<2, Type>& rhs) noexcept
		{
			matrix[0][0] += rhs.matrix[0][0];
			matrix[0][1] += rhs.matrix[0][1];
			matrix[1][0] += rhs.matrix[1][0];
			matrix[1][1] += rhs.matrix[1][1];
			return *this;
		}
		Matrix<2, Type>& operator-=(const Matrix<2, Type>& rhs) noexcept
		{
			matrix[0][0] -= rhs.matrix[0][0];
			matrix[0][1] -= rhs.matrix[0][1];
			matrix[1][0] -= rhs.matrix[1][0];
			matrix[1][1] -= rhs.matrix[1][1];
			return *this;
		}
		Matrix<2, Type>& operator*=(const Matrix<2, Type>& rhs) noexcept
		{
			matrix[0][0] *= rhs.matrix[0][0] + matrix[0][1] * rhs.matrix[1][0];
			matrix[0][0] *= rhs.matrix[0][1] + matrix[0][1] * rhs.matrix[1][1]; // [ A B ] * [ E F ] == [ A*E + B*G  |  A*F + B*H ]
			matrix[1][0] *= rhs.matrix[0][0] + matrix[1][1] * rhs.matrix[1][0]; // [ C D ] * [ G H ] == [ C*E + D*G  |  C*F + D*H ]
			matrix[1][0] *= rhs.matrix[0][1] + matrix[1][1] * rhs.matrix[1][1];
			return *this;
		}
		Matrix<2, Type>& operator*=(const Type constant) noexcept
		{
			matrix[0][0] * constant;
			matrix[0][1] * constant;
			matrix[1][0] * constant;
			matrix[1][1] * constant;
			return *this;
		}
		Matrix<2, Type>& operator/=(const Matrix<2, Type>& rhs) 
		{
			Matrix<2, Type> inverse{ rhs.Inverse() };

			if (rhs * inverse != identityMatrix)
				throw MatrixDivisionNotPossibleException{};

			matrix *= inverse;
			return *this;
		}
#pragma endregion

#pragma region Relational Operators
		bool operator==(const Matrix<2, Type>& rhs) const noexcept
		{
			for (int i{}; i < 2; ++i)
				for (int j{}; j < 2; ++j)
					if (matrix[i][j] != rhs.matrix[i][j])
						return false;

			return true;
		}
		bool operator!=(const Matrix<2, Type>& rhs) const noexcept
		{
			return !(matrix == rhs.matrix);
		}
#pragma endregion

#pragma region Miscellaneous Operators
		Matrix<2, Type>& operator-() noexcept
		{
			for (int i{}; i < 2; ++i)
				for (int j{}; j < 2; ++j)
					matrix[i][j] = -matrix[i][j];
		}

		friend std::ostream& operator<<(std::ostream& os, const Matrix<2, Type>& rhs) noexcept
		{
			for (int i{}; i < 2; ++i)
			{
				for (int j{}; j < 2; ++j)
				{
					os << matrix[i][j] << ", ";
				}
				os << std::endl;
			}
			return os;
		}
#pragma endregion
	};
}

#endif // !INTEGRIAN_MATRIX2x2_H
