#pragma once

#ifndef INTEGRIAN_ANIMATIONCOMPONENT_H
#define INTEGRIAN_ANIMATIONCOMPONENT_H

#include "Component.h"

namespace Integrian
{
	class GameObject;
	class Texture;
	class AnimationComponent final : public Component
	{
	public:
		AnimationComponent(GameObject* pParent);
		AnimationComponent(GameObject* pParent, const int nrOfFrames, const int framesPerSec, Texture* pTexture);
		AnimationComponent(GameObject* pParent, const int nrOfFrames, const int framesPerSec, const float frameWidth, const float frameHeight, Texture* pTexture);

		virtual void Initialize() override;
		
		virtual void Update(const float elapsedSeconds) override;

		virtual void Render() const override;

	private:
		Texture* m_pTexture;
		int m_NrOfFrames;
		int m_FramesPerSec;
		float m_CurrentTime;
		float m_FrameWidth;
		float m_FrameHeight;
		int m_CurrentFrame;
	};
}

#endif // !INTEGRIAN_ANIMATIONCOMPONENT_H