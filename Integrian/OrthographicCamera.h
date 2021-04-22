#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: February 2021
// ====================================
#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

namespace Integrian
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(const uint32_t windowWidth, const uint32_t windowHeight, const Rectf& levelBoundaries = Rectf{});
		~OrthographicCamera() = default;

		Point2f Transform(const Rectf& target);

		void SetLevelBoundaries(const Rectf& levelBoundaries);
	
	private:
		Point2f Track(const Rectf& target);
		void Clamp(Point2f& bottomLeftPos) const;

		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;
		Rectf m_LevelBoundaries;
	};
}

#endif // !ENGINE_CAMERA_H