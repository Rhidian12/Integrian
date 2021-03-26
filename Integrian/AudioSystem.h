#pragma once

#ifndef INTEGRIAN_AUDIOSYSTEM_H
#define INTEGRIAN_AUDIOSYSTEM_H

#include <SDL_mixer.h> // Mix_Chunk, Mix_Music, more SDL_Mixer related functionality
#include <string> // std::string
#include "ListenerInterface.h" // IListener

namespace Integrian
{
	class AudioSystem abstract : public IListener
	{
	public:
		using SoundID = int;
		using MusicID = int;

		AudioSystem() = default;
		virtual ~AudioSystem() = default;

		virtual bool OnEvent(const Event&) = 0;

		virtual SoundID AddSound(const std::string&) = 0;
		virtual MusicID AddMusic(const std::string&) = 0;

		virtual void Update(const float) = 0;

		virtual void PlaySound(const SoundID, const bool = false, const int = 0, const int = 100) = 0;
		virtual void PlayMusic(const MusicID, const bool = false, const int = 0, const int = 100) = 0;

		virtual void PauseMusic() = 0;
		virtual void PauseSound(const SoundID) = 0;

		virtual void RewindMusic() = 0;
		virtual void SetMusicPosition(double) = 0;

		virtual void SetSoundVolume(const SoundID, const int) = 0;
		virtual void SetMusicVolume(const int) = 0;

		virtual [[nodiscard]] bool IsMusicPlaying() const = 0;
		virtual [[nodiscard]] bool IsSoundPlaying(const SoundID) const = 0;

		virtual [[nodiscard]] int GetSoundVolume(const SoundID) const = 0;
		virtual [[nodiscard]] int GetMusicVolume() const = 0;

	protected:
	};
}

#endif // !INTEGRIAN_AUDIOSYSTEM_H