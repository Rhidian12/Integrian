#include "IntegrianPCH.h" // precompiled header
#include "MathFunctions.h" // header 
#include <cmath> // atan
#include <algorithm> // std::min_element
#include <limits> // std::numeric_limits
const float Integrian::CalculateAngle(const Point2f& line1Start, const Point2f& line1End, const Point2f& line2Start, const Point2f& line2End) noexcept
{
	const float slopeLine1{ line1End.y - line1Start.y / line1End.x - line1Start.x };
	const float slopeLine2{ line2End.y - line2Start.y / line2End.x - line2Start.x };
	const float inclineLine1{ atan(slopeLine1) };
	const float inclineLine2{ atan(slopeLine2) };
	return abs(inclineLine1 - inclineLine2);
}
const float Integrian::ToDegrees(const float radians) noexcept
{
	return radians * 180.f / float(M_PI);
}
const double Integrian::ToDegrees(const double radians) noexcept
{
	return radians * 180.0 / M_PI;
}
const float Integrian::ToRadians(const float degrees) noexcept
{
	return degrees * float(M_PI) / 180.f;
}
const double Integrian::ToRadians(const double degrees) noexcept
{
	return degrees * M_PI / 180.0;
}
bool Integrian::AreEqual(const float a, const float b, const float epsilon) noexcept
{
	return abs(a - b) <= epsilon;
}
bool Integrian::AreEqual(const double a, const double b, const double epsilon) noexcept
{
	return abs(a - b) <= epsilon;
}

bool Integrian::IsOverlapping(const Rectf& r1, const Rectf& r2) noexcept
{
	// If one rectangle is on left side of the other
	if ((r1[VertexLocation::LeftBottom].x + r1.width) < r2[VertexLocation::LeftBottom].x || (r2[VertexLocation::LeftBottom].x + r2.width) < r1[VertexLocation::LeftBottom].x)
		return false;

	// If one rectangle is under the other
	if (r1[VertexLocation::LeftBottom].y > (r2[VertexLocation::LeftBottom].y + r2.height) || r2[VertexLocation::LeftBottom].y > (r1[VertexLocation::LeftBottom].y + r1.height))
		return false;

	return true;
}

bool Integrian::IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b) noexcept
{
	Vector2f ap{ a, p }, bp{ b, p };
	// If not on same line, return false
	if (abs(ap.Cross(bp)) > 0.001f)
	{
		return false;
	}

	// Both vectors must point in opposite directions if p is between a and b
	if (ap.Dot(bp) > 0)
	{
		return false;
	}

	return true;
}

bool Integrian::IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon) noexcept
{
	bool intersecting{ false };

	Vector2f p1p2{ p1, p2 };
	Vector2f q1q2{ q1, q2 };

	// Cross product to determine if parallel
	float denom = p1p2.Cross(q1q2);

	// Don't divide by zero
	if (std::abs(denom) > epsilon)
	{
		intersecting = true;

		Vector2f p1q1{ p1, q1 };

		float num1 = p1q1.Cross(q1q2);
		float num2 = p1q1.Cross(p1p2);
		outLambda1 = num1 / denom;
		outLambda2 = num2 / denom;
	}
	else // are parallel
	{
		// Connect start points
		Vector2f p1q1{ p1, q1 };

		// Cross product to determine if segments and the line connecting their start points are parallel, 
		// if so, than they are on a line
		// if not, then there is no intersection
		if (std::abs(p1q1.Cross(q1q2)) > epsilon)
		{
			return false;
		}

		// Check the 4 conditions
		outLambda1 = 0;
		outLambda2 = 0;
		if (Integrian::IsPointOnLineSegment(p1, q1, q2) ||
			Integrian::IsPointOnLineSegment(p2, q1, q2) ||
			Integrian::IsPointOnLineSegment(q1, p1, p2) ||
			Integrian::IsPointOnLineSegment(q2, p1, p2))
		{
			intersecting = true;
		}
	}
	return intersecting;
}

bool Integrian::Raycast(const std::vector<Point2f>& vertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo) noexcept
{
	return Integrian::Raycast(vertices.data(), vertices.size(), rayP1, rayP2, hitInfo);
}

bool Integrian::Raycast(const Point2f* vertices, const size_t nrVertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo) noexcept
{
	if (nrVertices == 0)
	{
		return false;
	}

	std::vector<HitInfo> hits;

	Rectf r1, r2;
	// r1: minimal AABB rect enclosing the ray
	r1[VertexLocation::LeftBottom].x		= std::min(rayP1.x, rayP2.x);
	r1[VertexLocation::LeftBottom].y		= std::min(rayP1.y, rayP2.y);
	r1.width								= std::max(rayP1.x, rayP2.x) - r1[VertexLocation::LeftBottom].x;
	r1.height								= std::max(rayP1.y, rayP2.y) - r1[VertexLocation::LeftBottom].y;

	// Line-line intersections.
	for (size_t idx{ 0 }; idx <= nrVertices; ++idx)
	{
		// Consider line segment between 2 consecutive vertices
		// (modulo to allow closed polygon, last - first vertice)
		Point2f q1 = vertices[(idx + 0) % nrVertices];
		Point2f q2 = vertices[(idx + 1) % nrVertices];

		// r2: minimal AABB rect enclosing the 2 vertices
		r2[VertexLocation::LeftBottom].x		= std::min(q1.x, q2.x);
		r2[VertexLocation::LeftBottom].y		= std::min(q1.y, q2.y);
		r2.width								= std::max(q1.x, q2.x) - r2[VertexLocation::LeftBottom].x;
		r2.height								= std::max(q1.y, q2.y) - r2[VertexLocation::LeftBottom].y;

		if (IsOverlapping(r1, r2))
		{
			float lambda1{};
			float lambda2{};
			if (IntersectLineSegments(rayP1, rayP2, q1, q2, lambda1, lambda2))
			{
				if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
				{
					HitInfo linesHitInfo{};
					linesHitInfo.lambda = lambda1;
					linesHitInfo.intersectPoint = Point2f{ rayP1.x + ((rayP2.x - rayP1.x) * lambda1), rayP1.y + ((rayP2.y - rayP1.y) * lambda1) };
					linesHitInfo.normal = GetNormalized(Vector2f{ q2 - q1 }.Orthogonal());
					hits.push_back(linesHitInfo);
				}
			}
		}
	}

	if (hits.size() == 0)
	{
		return false;
	}

	// Get closest intersection point and copy it into the hitInfo parameter
	hitInfo = *std::min_element
	(
		hits.begin(), hits.end(),
		[](const HitInfo& first, const HitInfo& last)
		{
			return first.lambda < last.lambda;
		}
	);
	return true;
}