#pragma once

#ifndef INTEGRIAN_NULLSERVICE_H
#define INTEGRIAN_NULLSERVICE_H

#include "AudioSystem.h"

namespace Integrian
{
	class NullService final : public AudioSystem
	{
	public:
		virtual bool OnEvent(const Event&) override { return false; }

		virtual void Update(const float) override {}

		virtual void PlaySound(const SoundID, const bool = false, const int = 0, const int = 100) override {}
		virtual void PlayMusic(const MusicID, const bool = false, const int = 0, const int = 100) override {}

		virtual void PauseMusic() override {}
		virtual void PauseSound(const SoundID) override {}

		virtual void RewindMusic() override {}
		virtual void SetMusicPosition(double) override {}

		virtual void SetSoundVolume(const SoundID, const int) override {}
		virtual void SetMusicVolume(const int) override {}

		virtual [[nodiscard]] bool IsMusicPlaying() const override { return false; }
		virtual [[nodiscard]] bool IsSoundPlaying(const SoundID) const override { return false; }

		virtual [[nodiscard]] int GetSoundVolume(const SoundID) const override { return 0; }
		virtual [[nodiscard]] int GetMusicVolume() const override { return 0; }
	};
}

#endif // !INTEGRIAN_NULLSERVICE_H