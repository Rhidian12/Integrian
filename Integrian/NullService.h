#pragma once

#ifndef INTEGRIAN_NULLSERVICE_H
#define INTEGRIAN_NULLSERVICE_H

#include "AudioPlayerLogged.h"

namespace Integrian
{
	class NullService final : public AudioPlayerLogged
	{
	public:
		virtual void PlaySound(const SoundID, const bool = false, const int = 0, const int = 100) override {}
		virtual void PlayMusic(const MusicID, const bool = false, const int = 0, const int = 100) override {}

		virtual void PauseMusic() override {}
		virtual void PauseSound() override {}

		virtual void RewindMusic() override {}
		virtual void SetMusicPosition(double) override {}

		virtual [[nodiscard]] bool IsMusicPlaying() const override { return false; }
		virtual [[nodiscard]] bool IsSoundPlaying() const override { return false; }
	};
}

#endif // !INTEGRIAN_NULLSERVICE_H