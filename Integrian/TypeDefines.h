#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef INTEGRIAN_TYPEDEFINES_H
#define INTEGRIAN_TYPEDEFINES_H

#include "Point.h" // Point
#include "Point2f.h" // Point<2, Type>
#include "Vector.h" // Vector
#include "Vector2f.h" // Vector<2, Type>
#include "Matrix.h" // Matrix
#include "Matrix2x2.h" // Matrix<2, Type>
#include "Matrix3x3.h" // Matrix<3, Type>
namespace Integrian
{
	typedef Vector<2, float> Vector2f;
	typedef Point<2, float> Point2f;
	typedef Matrix<2, float> Matrix2f;
	typedef Matrix<3, float> Matrix3f;
}

#endif // !ENGINE_TYPEDEFINES_H