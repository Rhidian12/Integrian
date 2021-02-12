#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef ENGINE_STRUCTS_H
#define ENGINE_STRUCTS_H

#include <math.h>
#include "Point.h"
#include "Vector.h"
namespace Engine
{
	// == Structs ==
	struct Rectf
	{
		explicit Rectf()
			: leftBottom{}
			, width{}
			, height{}
		{
		}
		explicit Rectf(const Point2f& leftBottom, const float width, const float height)
			: leftBottom{ leftBottom }
			, width{ width }
			, height{ height }
		{
		}
		explicit Rectf(const float left, const float bottom, const float width, const float height)
			: leftBottom{ left, bottom }
			, width{ width }
			, height{ height }
		{
		}

		bool operator==(const Rectf& other) const
		{
			const float epsilon{ 0.001f };
			if (fabs(static_cast<double>(leftBottom.x) - other.leftBottom.x) > epsilon)
				return false;
			if (fabs(static_cast<double>(leftBottom.y) - other.leftBottom.y) > epsilon)
				return false;
			if (fabs(static_cast<double>(width) - other.width) > epsilon)
				return false;
			if (fabs(static_cast<double>(height) - other.height) > epsilon)
				return false;
			return true;
		}
		bool operator!=(const Rectf& other) const
		{
			return !Rectf::operator==(other);
		}
		void operator=(const Rectf& other)
		{
			leftBottom = other.leftBottom;
			width = other.width;
			height = other.height;
		}

		Point2f leftBottom;
		float width;
		float height;
	};
	struct Circlef
	{
		explicit Circlef()
			: center{}
			, radius{}
		{
		}
		explicit Circlef(const Point2f& center, const float radius)
			: center{ center }
			, radius{ radius }
		{
		}

		bool operator==(const Circlef& other) const
		{
			const float epsilon{ 0.1f };
			if (fabs(static_cast<double>(center.x) - other.center.x) > epsilon)
				return false;
			if (fabs(static_cast<double>(center.y) - other.center.y) > epsilon)
				return false;
			if (fabs(static_cast<double>(radius) - other.radius) > epsilon)
				return false;
			return true;
		}
		void operator=(const Circlef& other)
		{
			center = other.center;
			radius = other.radius;
		}

		Point2f center;
		float radius;
	};
	struct RGBColour
	{
		explicit RGBColour()
			: r{}
			, g{}
			, b{}
		{
		}
		explicit RGBColour(const float r, const float g, const float b)
			: r{ r }
			, g{ g }
			, b{ b }
		{
		}

		bool operator==(const RGBColour& other) const
		{
			const float epsilon{ 0.1f };
			if (fabs(static_cast<double>(r) - other.r) > epsilon)
				return false;
			if (fabs(static_cast<double>(g) - other.g) > epsilon)
				return false;
			if (fabs(static_cast<double>(b) - other.b) > epsilon)
				return false;
			return true;
		}
		void operator=(const RGBColour& other)
		{
			r = other.r;
			g = other.g;
			b = other.b;
		}

		float r, g, b;
	};
	struct TextureLocation
	{
		explicit TextureLocation()
			: destRect{}
			, srcRect{}
		{
		}
		explicit TextureLocation(const Rectf& destRect, const Rectf& srcRect)
			: destRect{ destRect }
			, srcRect{ srcRect }
		{
		}

		Rectf destRect, srcRect;
	};

	// == Non-Member Struct Operators ==
}

#endif // !ENGINE_STRUCTS_H