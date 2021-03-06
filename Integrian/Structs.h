#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef INTEGRIAN_STRUCTS_H
#define INTEGRIAN_STRUCTS_H

#include "TypeDefines.h" // Point2f && Vector2f
#include <cmath> //
#include <string> // std::string
#include <array> // std::array

namespace Integrian
{
	enum class VertexLocation : uint8_t
	{
		LeftBottom = 0,
		RightBottom = 1,
		RightTop = 2,
		LeftTop = 3
	};
	// == Structs ==
	struct Rectf final
	{
		explicit Rectf()
			: vertices{}
			, width{}
			, height{}
		{
		}
		explicit Rectf(const float left, const float bottom, const float width, const float height)
			: Rectf{ { left, bottom }, width, height }
		{
		}
		explicit Rectf(const Point2f& leftBottom, const float width, const float height)
			: vertices{}
			, width{ width }
			, height{ height }
		{
			vertices[static_cast<std::underlying_type_t<VertexLocation>>(VertexLocation::LeftBottom)] = leftBottom;
			vertices[static_cast<std::underlying_type_t<VertexLocation>>(VertexLocation::LeftTop)] = { leftBottom.x, leftBottom.y + height };
			vertices[static_cast<std::underlying_type_t<VertexLocation>>(VertexLocation::RightTop)] = { leftBottom.x + width, leftBottom.y + height };
			vertices[static_cast<std::underlying_type_t<VertexLocation>>(VertexLocation::RightBottom)] = { leftBottom.x + width, leftBottom.y };
		}

#pragma region RectfOperators
		Point2f& operator[](const VertexLocation vertexLocation) noexcept
		{
			return vertices[static_cast<std::underlying_type_t<VertexLocation>>(vertexLocation)];
		}
		const Point2f& operator[](const VertexLocation vertexLocation) const noexcept
		{
			return vertices[static_cast<std::underlying_type_t<VertexLocation>>(vertexLocation)];
		}
		bool operator==(const Rectf& other) const noexcept
		{
			const float epsilon{ 0.001f };
			for (uint8_t i{}; i < 4; ++i)
				if ((*this)[static_cast<VertexLocation>(i)] != other[static_cast<VertexLocation>(i)])
					return false;

			if (fabs(static_cast<double>(width) - other.width) > epsilon)
				return false;

			if (fabs(static_cast<double>(height) - other.height) > epsilon)
				return false;

			return true;
		}
		bool operator!=(const Rectf& other) const noexcept
		{
			return !Rectf::operator==(other);
		}
		void operator=(const Rectf& other) noexcept
		{
			vertices = other.vertices;
			width = other.width;
			height = other.height;
		}

#pragma endregion

		std::array<Point2f, 4> vertices;
		float width;
		float height;
	};
	struct Circlef final
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
	struct RGBColour final
	{
		explicit RGBColour()
			: RGBColour{ 255.f,255.f,255.f }
		{
		}
		explicit RGBColour(const float r, const float g, const float b)
			: RGBColour{ r,g,b,1.f }
		{
		}
		explicit RGBColour(const float r, const float g, const float b, const float a)
			: r{ r }
			, g{ g }
			, b{ b }
			, a{ a }
		{
			if (this->a > 1.f)
				this->a = 1.f;
			else if (this->a < 0.f)
				this->a = 0.f;
		}

#pragma region Compound Assignment Operators
		inline RGBColour& operator*=(const RGBColour& other)
		{
			r *= other.r;
			g *= other.g;
			b *= other.b;
			return *this;
		}
		inline RGBColour& operator/=(const RGBColour& other)
		{
			r /= other.r;
			g /= other.g;
			b /= other.b;
			return *this;
		}
		inline RGBColour& operator/=(const float f)
		{
			const float inverse{ 1.f / f };
			r *= inverse;
			g *= inverse;
			b *= inverse;
			return *this;
		}
#pragma endregion

		bool operator==(const RGBColour& other) const
		{
			const float epsilon{ 0.1f };
			if (fabs(static_cast<double>(r) - other.r) > epsilon)
				return false;
			if (fabs(static_cast<double>(g) - other.g) > epsilon)
				return false;
			if (fabs(static_cast<double>(b) - other.b) > epsilon)
				return false;
			if (fabs(static_cast<double>(a) - other.a) > epsilon)
				return false;
			return true;
		}
		void operator=(const RGBColour& other)
		{
			r = other.r;
			g = other.g;
			b = other.b;
			a = other.a;
		}
		[[nodiscard]] inline std::string ToString() const
		{
			std::string temp{ std::to_string(r) + std::to_string(g) + std::to_string(b) + std::to_string(a) };
			return temp;
		}
		inline void MaxToOne()
		{
			const float max{ std::max({ r ,g ,b }) };
			*this /= max;
		}

		float r, g, b, a;
	};
	struct TextureLocation final
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

		Integrian::Rectf destRect, srcRect;
	};

	// == Non-Member Struct Operators ==
}

#endif // !ENGINE_STRUCTS_H