#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: January 2021
// ====================================
#ifndef ENGINE_MATH_FUNCTIONS_H
#define ENGINE_MATH_FUNCTIONS_H

#include "Structs.h"
#include "TypeDefines.h"
#include <limits>
#include <vector>
namespace Engine
{
#pragma region General Math Functions
	// == General Math Functions ==
	const float CalculateAngle(const Point2f& line1Start, const Point2f& line1End, const Point2f& line2Start, const Point2f& line2End);
	const float ToDegrees(const float radians);
	const double ToDegrees(const double radians);
	const float ToRadians(const float degrees);
	const double ToRadians(const double degrees);
	bool AreEqual(const float a, const float b, const float epsilon = std::numeric_limits<float>::epsilon());
	bool AreEqual(const double a, const double b, const double epsilon = std::numeric_limits<double>::epsilon());
#pragma endregion

#pragma region Collisions
	// == Collisions ==
	struct HitInfo
	{
		float lambda;
		Point2f intersectPoint;
		Vector2f normal;
	};
	bool IsOverlapping(const Rectf& r1, const Rectf& r2);
	bool IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);
	bool IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon = 1e-6);
	bool Raycast(const std::vector<Point2f>& vertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo);
	bool Raycast(const Point2f* vertices, const size_t nrVertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo);
#pragma endregion

	template<typename Type>
	Type Square(const Type& t)
	{
		return t * t;
	}
}

#endif // !ENGINE_MATH_FUNCTIONS_H