#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: January 2021
// ====================================
#ifndef INTEGRIAN_MATH_FUNCTIONS_H
#define INTEGRIAN_MATH_FUNCTIONS_H

#include <vector> // std::vector
#include "Structs.h"
#include "TypeDefines.h"

namespace Integrian
{
#pragma region General Math Functions
	// == General Math Functions ==
	const float CalculateAngle(const Point2f& line1Start, const Point2f& line1End, const Point2f& line2Start, const Point2f& line2End) noexcept;
	const float ToDegrees(const float radians) noexcept;
	const double ToDegrees(const double radians) noexcept;
	const float ToRadians(const float degrees) noexcept;
	const double ToRadians(const double degrees) noexcept;
	bool AreEqual(const float a, const float b, const float epsilon = std::numeric_limits<float>::epsilon()) noexcept;
	bool AreEqual(const double a, const double b, const double epsilon = std::numeric_limits<double>::epsilon()) noexcept;
#pragma endregion

#pragma region Collisions
	// == Collisions ==
	// These functions were made by Bart Uyttenhove
	struct HitInfo final
	{
		float lambda;
		Point2f intersectPoint;
		Vector2f normal;
	};
	bool IsOverlapping(const Rectf& r1, const Rectf& r2) noexcept;
	bool IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b) noexcept;
	bool IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon = 1e-6) noexcept;
	bool Raycast(const std::vector<Point2f>& vertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo) noexcept;
	bool Raycast(const Point2f* vertices, const size_t nrVertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo) noexcept;
#pragma endregion

	template<typename Type>
	Type Square(const Type& t) noexcept
	{
		return t * t;
	}
}

#endif // !ENGINE_MATH_FUNCTIONS_H