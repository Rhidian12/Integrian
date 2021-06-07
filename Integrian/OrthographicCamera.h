#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: February 2021
// ====================================
#ifndef ENGINE_ORTOGRAPHICCAMERA_H
#define ENGINE_ORTOGRAPHICCAMERA_H

#include "Camera.h" // Camera base class

namespace Integrian
{
	class OrthographicCamera final : public Camera
	{
	public:
		OrthographicCamera(const uint32_t windowWidth, const uint32_t windowHeight, const Rectf& levelBoundaries = Rectf{});
		virtual ~OrthographicCamera() = default;

		virtual Point2f Transform(const Rectf& target) override;

		void SetLevelBoundaries(const Rectf& levelBoundaries);
	
	private:
		Point2f Track(const Rectf& target);
		void Clamp(Point2f& bottomLeftPos) const;

		Rectf m_LevelBoundaries;
	};
}

#endif // !ENGINE_ORTOGRAPHICCAMERA_H