#pragma once

#ifndef INTEGRIAN_AUDIOPLAYERLOGGED_H
#define INTEGRIAN_AUDIOPLAYERLOGGED_H

#include "AudioSystem.h"
#include "ListenerInterface.h"

namespace Integrian
{
	class AudioPlayerLogged : public AudioSystem, public IListener // Not final since NullService inherits
	{
	public:
		AudioPlayerLogged() = default;
		virtual ~AudioPlayerLogged() = default;

		virtual bool OnEvent(const Event& event) override;

		virtual void PlaySound(const SoundID soundID, const bool infiniteLoop = false, const int amountOfLoops= 0, const int volume = 100) override;
		virtual void PlayMusic(const MusicID soundID, const bool infiniteLoop = false, const int amountOfLoops= 0, const int volume = 100) override;

		// TODO: Expand this class to be able to do more than just play a sound and music
	private:
	};
}

#endif // !INTEGRIAN_AUDIOPLAYERLOGGED_H