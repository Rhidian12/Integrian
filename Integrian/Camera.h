#pragma once

#ifndef INTEGRIAN_CAMERA_H
#define INTEGRIAN_CAMERA_H

namespace Integrian
{
	class Camera
	{
	public:
		Camera(const uint32_t windowWidth, const uint32_t windowHeight);
		virtual ~Camera() = default;

		virtual Point2f Transform(const Rectf&) = 0;

	protected:
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;
	};
}

#endif // !INTEGRIAN_CAMERA_H