#pragma once

#ifndef INTEGRIAN_AUDIOSYSTEM_H
#define INTEGRIAN_AUDIOSYSTEM_H

#include <SDL_mixer.h> // Mix_Chunk, Mix_Music, more SDL_Mixer related functionality
#include "ListenerInterface.h" // IListener

namespace Integrian
{
	class INTEGRIAN_API AudioSystem : public IListener
	{
	public:
		using SoundID = int;
		using MusicID = int;

		AudioSystem() = default;
		virtual ~AudioSystem() = default;

		/*
		This function is used internally and SHOULD NOT BE CALLED MANUALLY
		*/
		virtual bool OnEvent(const Event&) = 0;

		/*
		Add a Sound to the AudioSystem. This function returns the SoundID provided to the Sound.
		Difference between Sound and Music is the difference in between. Sound Effects should be loaded in as Sounds,
		while longer MP3 songs should be loaded in as Music.
		Many Sounds can be played at the same time, however only one Music can play simultaneously.
		Parameters:
		1 > const char* pFilePath > Filepath to the Sound.
		*/
		virtual SoundID AddSound(const char*) = 0;

		/*
		Add Music to the AudioSystem. This function returns the MusicID provided to the Music.
		Difference between Sound and Music is the difference in between. Sound Effects should be loaded in as Sounds,
		while longer MP3 songs should be loaded in as Music.
		Many Sounds can be played at the same time, however only one Music can play simultaneously.
		Parameters:
		1 > const char* pFilePath > Filepath to the Music.
		*/
		virtual MusicID AddMusic(const char*) = 0;

		/*
		This function is used internally and SHOULD NOT BE CALLED MANUALLY
		*/
		virtual void Update(const float) = 0;

		/*
		Plays a Sound.
		Parameters:
		1 > const SoundID soundID > ID of Sound to play.
		2 > const bool infiniteLoop > Should the Sound infinitely loop.
		3 > const int amountOfLoops > How many times should the Sound be played (Sounds are played n + 1 times)
		4 > const int volume > Volume of Sound (in range [0, 100])
		*/
		virtual void PlaySound(const SoundID, const bool = false, const int = 0, const int = 100) = 0;

		/*
		Plays Music.
		Parameters:
		1 > const MusicID musicID > ID of Music to play.
		2 > const bool infiniteLoop > Should the Music infinitely loop.
		3 > const int amountOfLoops > How many times should the Music be played (Music is played n + 1 times)
		4 > const int volume > Volume of Music (in range [0, 100])
		*/
		virtual void PlayMusic(const MusicID, const bool = false, const int = 0, const int = 100) = 0;

		/*
		Pauses the currently playing Music.
		*/
		virtual void PauseMusic() = 0;

		/*
		Pauses the Sound with the given SoundID.
		Parameters:
		1 > const SoundID soundID > SoundID of Sound to pause.
		*/
		virtual void PauseSound(const SoundID) = 0;

		/*
		Rewind currently playing Music to the beginning.
		*/
		virtual void RewindMusic() = 0;

		/*
		Set the timer of the Music to a specific position.
		Parameters:
		1 > double time > absolute position in seconds.
		*/
		virtual void SetMusicPosition(double) = 0;

		/*
		Sets the Volume of a Sound with the given SoundID.
		Parameters:
		1 > const SoundID soundID > SoundID of Sound to change volume of.
		2 > const int volume > New volume of Sound.
		*/
		virtual void SetSoundVolume(const SoundID, const int) = 0;

		/*
		Sets the Volume of the currently playing Music.
		Parameters:
		1 > const int volume > New volume of Music.
		*/
		virtual void SetMusicVolume(const int) = 0;

		/*
		Returns whether or not Music is currently playing.
		*/
		virtual [[nodiscard]] bool IsMusicPlaying() const = 0;

		/*
		Returns whether or not a Sound with the given SoundID is currently playing.
		Parameters:
		1 > const SoundID soundID > SoundID of Sound to check whether it is playing.
		*/
		virtual [[nodiscard]] bool IsSoundPlaying(const SoundID) const = 0;

		/*
		Returns the Volume of a Sound with the given SoundID.
		Parameters:
		1 > const SoundID soundID > SoundID of Sound to get the Volume of.
		*/
		virtual [[nodiscard]] int GetSoundVolume(const SoundID) const = 0;

		/*
		Returns the Volume of the currently playing Music.
		*/
		virtual [[nodiscard]] int GetMusicVolume() const = 0;

	protected:
	};
}

#endif // !INTEGRIAN_AUDIOSYSTEM_H