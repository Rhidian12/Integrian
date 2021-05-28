#pragma once

#ifndef INTEGRIAN_MATRIX3x3_H
#define INTEGRIAN_MATRIX3x3_H

#include "MatrixDivisionNotPossibleException.h" // MatrixDivisionNotPossibleException
#include "Matrix2x2.h" // Matrix2x2 and Matrix
#include "Vector3f.h"
#include <iostream> // std::ostream

namespace Integrian
{
	// Matrix3x3 (Matrix Specialisation)
	template<typename Type>
	struct Matrix<3, Type>
	{

#pragma region Member Variables
		//Type(*matrix)[3]{ new Type[3][3] };
		Type matrix[3][3];
#pragma endregion

#pragma region Constructors
		Matrix<3, Type>() noexcept
		{
			matrix[0][0] = 0.f;
			matrix[0][1] = 0.f;
			matrix[0][2] = 0.f;
			matrix[1][0] = 0.f; // [ A B C ] 
			matrix[1][1] = 0.f; // [ D E F ]
			matrix[1][2] = 0.f; // [ G H I ]
			matrix[2][0] = 0.f;
			matrix[2][1] = 0.f;
			matrix[2][2] = 0.f;
		}
		Matrix<3, Type>(const Type a, const Type b, const Type c, const Type d, const Type e, const Type f, const Type g, const Type h, const Type i) noexcept
		{
			matrix[0][0] = a;
			matrix[0][1] = b;
			matrix[0][2] = c;
			matrix[1][0] = d; // [ A B C ] 
			matrix[1][1] = e; // [ D E F ]
			matrix[1][2] = f; // [ G H I ]
			matrix[2][0] = g;
			matrix[2][1] = h;
			matrix[2][2] = i;
		}
		Matrix<3, Type>(const Matrix<3, Type>& other) noexcept
		{
			matrix[0][0] = other.matrix[0][0];
			matrix[0][1] = other.matrix[0][1];
			matrix[0][2] = other.matrix[0][2];
			matrix[1][0] = other.matrix[1][0]; // [ A B C ] 
			matrix[1][1] = other.matrix[1][1]; // [ D E F ]
			matrix[1][2] = other.matrix[1][2]; // [ G H I ]
			matrix[2][0] = other.matrix[2][0];
			matrix[2][1] = other.matrix[2][1];
			matrix[2][2] = other.matrix[2][2];
		}
		Matrix<3, Type>(Matrix<3, Type>&& other) noexcept
		{
			matrix[0][0] = std::move(other.matrix[0][0]);
			matrix[0][1] = std::move(other.matrix[0][1]);
			matrix[0][2] = std::move(other.matrix[0][2]);
			matrix[1][0] = std::move(other.matrix[1][0]); // [ A B C ] 
			matrix[1][1] = std::move(other.matrix[1][1]); // [ D E F ]
			matrix[1][2] = std::move(other.matrix[1][2]); // [ G H I ]
			matrix[2][0] = std::move(other.matrix[2][0]);
			matrix[2][1] = std::move(other.matrix[2][1]);
			matrix[2][2] = std::move(other.matrix[2][2]);
		}
		~Matrix<3, Type>()
		{
			//delete[] matrix;
		}
#pragma endregion

#pragma region Member Functions
		Matrix<3, Type> Inverse() const noexcept
		{
			// Guide to pain: https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
			// == Matrix of Minors ==
			Matrix<3, Type> matrixOfMinors{};
			Type determinant{};
			for (int row{}; row < 3; ++row)
			{
				for (int column{}; column < 3; ++column)
				{
					// ignore current row and column, create a 2x2 matrix out of the remaining values
					Matrix<2, Type> tempMatrix{};

					tempMatrix[0][0] = matrix[(row + 1) % 3][(column + 1) % 3];
					tempMatrix[0][1] = matrix[(row + 1) % 3][(column + 2) % 3];
					tempMatrix[1][0] = matrix[(row + 2) % 3][(column + 1) % 3];
					tempMatrix[1][1] = matrix[(row + 2) % 3][(column + 2) % 3];

					matrixOfMinors[row][column] = tempMatrix.GetDeterminant();

					if (row == static_cast<Type>(0.f))
						determinant += matrixOfMinors[row][column] * tempMatrix[row][column];
				}
			}

			// == Matrix of Cofactors ==
			int counter{};
			for (int row{}; row < 3; ++row)
				for (int column{}; column < 3; ++column)
					if (counter++ % 2 != 0)
						matrix[row][column] = -matrix[row][column]; // apply negative to it

			// == Transpose The Matrix ==
			matrixOfMinors = matrixOfMinors.Transpose();

			return (static_cast<Type>(1.f) / determinant) * matrixOfMinors;
		}

		Matrix<3, Type> Transpose() const noexcept
		{
			Matrix<3, Type> tempMatrix{ *this };

			for (int row{}; row < 3; ++row)
			{
				for (int column{}; column < 3; ++column)
				{
					if (row == column)
						continue;

					if (row - 1 == column)
						continue;
					else
					{
						const Type tempValue{ tempMatrix[row][column] };		 // [ A B C ] == [ A D G ]
						tempMatrix[row][column] = tempMatrix[column][row];		 // [ D E F ] == [ B E H ]
						tempMatrix[column][row] = tempValue;					 // [ G H I ] == [ D F I ]
						break;
					}
				}
			}

			return tempMatrix;
		}
#pragma endregion

#pragma region Arithmetic Operators
		Matrix<3, Type> operator+(const Matrix<3, Type>& rhs) const noexcept
		{
			return Matrix<3, Type>{
				matrix[0][0] + rhs.matrix[0][0],
					matrix[0][1] + rhs.matrix[0][1],
					matrix[0][2] + rhs.matrix[0][2],
					matrix[1][0] + rhs.matrix[1][0],
					matrix[1][1] + rhs.matrix[1][1],
					matrix[1][2] + rhs.matrix[1][2],
					matrix[2][0] + rhs.matrix[2][0],
					matrix[2][1] + rhs.matrix[2][1],
					matrix[2][2] + rhs.matrix[2][2] };
		}
		Matrix<3, Type> operator-(const Matrix<3, Type>& rhs) const noexcept
		{
			return Matrix<3, Type>{
				matrix[0][0] - rhs.matrix[0][0],
					matrix[0][1] - rhs.matrix[0][1],
					matrix[0][2] - rhs.matrix[0][2],
					matrix[1][0] - rhs.matrix[1][0],
					matrix[1][1] - rhs.matrix[1][1],
					matrix[1][2] - rhs.matrix[1][2],
					matrix[2][0] - rhs.matrix[2][0],
					matrix[2][1] - rhs.matrix[2][1],
					matrix[2][2] - rhs.matrix[2][2] };
		}
		Matrix<3, Type> operator*(const Matrix<3, Type>& rhs) const noexcept
		{
			// [ A B C ] * [ J K L ] == [ A*J + B*M + C*P | A*K + B*N + C*Q | A*L + B*O + C*R ]
			// [ D E F ] * [ M N O ] == [ D*J + E*M + F*P | D*K + E*N + F*Q | D*L + E*O + F*R ]
			// [ G H I ] * [ P Q R ] == [ G*J + H*M + I*P | G*K + H*N + I*Q | G*L + H*O + I*R ]
			Matrix<3, Type> tempMatrix{};
			for (int row{}; row < 3; ++row)
			{
				for (int column{}; column < 3; ++column)
				{
					for (int secondColumn{}; secondColumn < 3; ++secondColumn)
					{
						tempMatrix[row][column] += matrix[row][secondColumn] * rhs.matrix[secondColumn][column];
					}
				}
			}
			return tempMatrix;
		}
		Matrix<3, Type> operator*(const Type constant) const noexcept
		{
			return Matrix<3, Type>{
				matrix[0][0] * constant,
					matrix[0][1] * constant,
					matrix[0][2] * constant,
					matrix[1][0] * constant,
					matrix[1][1] * constant,
					matrix[1][2] * constant,
					matrix[2][0] * constant,
					matrix[2][1] * constant,
					matrix[2][2] * constant };
		}
		Matrix<3, Type> operator/(const Matrix<3, Type>& rhs) const
		{
			Matrix<3, Type> inverse{ rhs.Inverse() };

			if (rhs * inverse != GetIdentity())
				throw MatrixDivisionNotPossibleException{};

			return matrix * inverse;
		}
		Vector<3, Type> operator*(const Vector<3, Type>& rhs) const noexcept
		{
			Vector<3, Type> vector{};
			for (int row{}; row < 3; ++row)
				for (int column{}; column < 3; ++column)
					vector[row] += matrix[row][column] * rhs[row];

			return vector;
		}
		Point<3, Type> operator*(const Point<3, Type>& rhs) const noexcept
		{
			Point<3, Type> vector{};
			for (int row{}; row < 3; ++row)
				for (int column{}; column < 3; ++column)
					vector[row] += matrix[row][column] * rhs[row];

			return vector;
		}
#pragma endregion

#pragma region Compound Assignment Operators
		Matrix<3, Type>& operator+=(const Matrix<3, Type>& rhs) noexcept
		{
			matrix[0][0] += rhs.matrix[0][0];
			matrix[0][1] += rhs.matrix[0][1];
			matrix[0][2] += rhs.matrix[0][2];
			matrix[1][0] += rhs.matrix[1][0];
			matrix[1][1] += rhs.matrix[1][1];
			matrix[1][2] += rhs.matrix[1][2];
			matrix[2][0] += rhs.matrix[2][0];
			matrix[2][1] += rhs.matrix[2][1];
			matrix[2][2] += rhs.matrix[2][2];
			return *this;
		}
		Matrix<3, Type>& operator-=(const Matrix<3, Type>& rhs) noexcept
		{
			matrix[0][0] -= rhs.matrix[0][0];
			matrix[0][1] -= rhs.matrix[0][1];
			matrix[0][2] -= rhs.matrix[0][2];
			matrix[1][0] -= rhs.matrix[1][0];
			matrix[1][1] -= rhs.matrix[1][1];
			matrix[1][2] -= rhs.matrix[1][2];
			matrix[2][0] -= rhs.matrix[2][0];
			matrix[2][1] -= rhs.matrix[2][1];
			matrix[2][2] -= rhs.matrix[2][2];
			return *this;
		}
		Matrix<3, Type>& operator*=(const Matrix<3, Type>& rhs) noexcept
		{
			// [ A B C ] * [ J K L ] == [ A*J + B*M + C*P | A*K + B*N + C*Q | A*L + B*O + C*R ]
			// [ D E F ] * [ M N O ] == [ D*J + E*M + F*P | D*K + E*N + F*Q | D*L + E*O + F*R ]
			// [ G H I ] * [ P Q R ] == [ G*J + H*M + I*P | G*K + H*N + I*Q | G*L + H*O + I*R ]
			Matrix<3, Type> tempMatrix{};
			for (int row{}; row < 3; ++row)
			{
				for (int column{}; column < 3; ++column)
				{
					for (int secondColumn{}; secondColumn < 3; ++secondColumn)
					{
						tempMatrix[row][column] += matrix[row][secondColumn] * rhs.matrix[secondColumn][column];
					}
				}
			}
			matrix = std::move(tempMatrix);
			return *this;
		}
		Matrix<3, Type>& operator*=(const Type constant) const noexcept
		{
			matrix[0][0] *= constant;
			matrix[0][1] *= constant;
			matrix[0][2] *= constant;
			matrix[1][0] *= constant;
			matrix[1][1] *= constant;
			matrix[1][2] *= constant;
			matrix[2][0] *= constant;
			matrix[2][1] *= constant;
			matrix[2][2] *= constant;
			return *this;
		}
		Matrix<3, Type>& operator/=(const Matrix<3, Type>& rhs) const
		{
			Matrix<3, Type> inverse{ rhs.Inverse() };

			if (rhs * inverse != GetIdentity())
				throw MatrixDivisionNotPossibleException{};

			matrix *= inverse;
			return *this;
		}
#pragma endregion

#pragma region Relational Operators
		bool operator==(const Matrix<3, Type>& rhs) const noexcept
		{
			for (int i{}; i < 3; ++i)
				for (int j{}; j < 3; ++j)
					if (matrix[i][j] != rhs.matrix[i][j])
						return false;

			return true;
		}
		bool operator!=(const Matrix<3, Type>& rhs) const noexcept
		{
			return !(matrix == rhs.matrix);
		}
#pragma endregion

#pragma region Access Operators
		Vector<3, Type>& operator[](const int row) noexcept
		{
			return *((Vector<3, Type>*)matrix[row]);
		}
#pragma endregion

#pragma region Miscellaneous Operators
		Matrix<3, Type>& operator-() noexcept
		{
			for (int i{}; i < 3; ++i)
				for (int j{}; j < 3; ++j)
					matrix[i][j] = -matrix[i][j];
		}

		friend std::ostream& operator<<(std::ostream& os, const Matrix<3, Type>& rhs) noexcept
		{
			for (int i{}; i < 3; ++i)
			{
				for (int j{}; j < 3; ++j)
				{
					os << matrix[i][j] << ", ";
				}
				os << std::endl;
			}
			return os;
		}
#pragma endregion

#pragma region Static Member Functions
		static Matrix<3, Type> GetIdentity();
#pragma endregion
	};

	template<typename Type>
	inline Matrix<3, Type> Matrix<3, Type>::GetIdentity()
	{
		return Matrix<3, Type>{
			static_cast<Type>(1.f), static_cast<Type>(0.f), static_cast<Type>(0.f),
			static_cast<Type>(0.f), static_cast<Type>(1.f), static_cast<Type>(0.f),
			static_cast<Type>(0.f), static_cast<Type>(0.f), static_cast<Type>(1.f)
		};
	}
}

#endif // !INTEGRIAN_MATRIX3x3_H
