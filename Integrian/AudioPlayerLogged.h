#pragma once

#ifndef INTEGRIAN_AUDIOPLAYERLOGGED_H
#define INTEGRIAN_AUDIOPLAYERLOGGED_H

#include "AudioSystem.h"

namespace Integrian
{
	class AudioPlayerLogged : public AudioSystem // Not final since NullService inherits
	{
	public:
		AudioPlayerLogged() = default;
		virtual ~AudioPlayerLogged() = default;

		virtual void PlaySound(const SoundID soundID, const bool infiniteLoop = false, const int amountOfLoops= 0, const int volume = 100.f) override;
		virtual void PlayMusic(const SoundID soundID, const bool infiniteLoop = false, const int amountOfLoops= 0, const int volume = 100.f) override;

		// TODO: Expand this class to be able to do more than just play a sound and music
	private:
	};
}

#endif // !INTEGRIAN_AUDIOPLAYERLOGGED_H