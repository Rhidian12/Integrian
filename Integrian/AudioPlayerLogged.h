#pragma once

#ifndef INTEGRIAN_AUDIOPLAYERLOGGED_H
#define INTEGRIAN_AUDIOPLAYERLOGGED_H

#include "AudioSystem.h"
#include "ListenerInterface.h"

namespace Integrian
{
	class AudioPlayerLogged : public AudioSystem // Not final since NullService inherits
	{
	public:
		AudioPlayerLogged() = default;
		virtual ~AudioPlayerLogged() = default;

		virtual bool OnEvent(const Event& event) override;

		virtual void Update(const float dt) override;

		virtual void PlaySound(const SoundID soundID, const bool infiniteLoop = false, const int amountOfLoops= 0, const int volume = 100) override;
		virtual void PlayMusic(const MusicID soundID, const bool infiniteLoop = false, const int amountOfLoops= 0, const int volume = 100) override;

		virtual void PauseMusic() override;
		virtual void PauseSound(const SoundID soundID) override;

		virtual void RewindMusic() override;
		virtual void SetMusicPosition(double time) override;

		virtual [[nodiscard]] bool IsMusicPlaying() const override;
		virtual [[nodiscard]] bool IsSoundPlaying(const SoundID soundID) const override;

		// TODO: Expand this class to be able to do more than just play a sound and music
	private:
	};
}

#endif // !INTEGRIAN_AUDIOPLAYERLOGGED_H