#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef ENGINE_UTILITYFUNCTIONS_H
#define ENGINE_UTILITYFUNCTIONS_H

#include "pch.h"
#include <cstdlib> // rand()
#include <random>

namespace Integrian
{
	// == Draw Functions ==
	void DrawRectangle(const Rectf& rect);
	void DrawRectangle(const Rectf& rect, const RGBColour& colour);
	void DrawFilledRectangle(const Rectf& rect);
	void DrawFilledRectangle(const Rectf& rect, const RGBColour& colour);
	void DrawCircle(const Circlef& circle);
	void DrawFilledCircle(const Circlef& circle, const RGBColour& colour);
	void DrawTriangle(const Point2f& top, const Point2f& left, const Point2f& right);
	void DrawFilledTriangle(const Point2f& top, const Point2f& left, const Point2f& right);
	void DrawLine(const Point2f& start, const Point2f& end, const RGBColour& colour, const float lineWidth = 1.f);

	// == Templated Utility Functions ==
	template<typename Type>
	Type GetRandomNumber(const Type min, const Type max)
	{
		return static_cast<Type>(rand() % (int(max) - int(min) + 1) + int(min));
	}
	template<>
	inline float GetRandomNumber<float>(const float min, const float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		const std::uniform_real_distribution<float> dis(min, max);
		return dis(gen);
	}
	template<>
	inline double GetRandomNumber<double>(const double min, const double max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		const std::uniform_real_distribution<> dis(min, max);
		return dis(gen);
	}

	template<typename Type>
	Type Clamp(const Type& clamp, const Type& min, const Type& max)
	{
		Type clampedValue{ clamp };
		if (clampedValue < min)
			clampedValue += (min - clampedValue);
		if (clampedValue > max)
			clampedValue -= (clampedValue - max);
		return clampedValue;
	}
}

#endif // !ENGINE_UTILITYFUNCTIONS_H