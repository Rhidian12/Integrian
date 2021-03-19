#pragma once

#ifndef INTEGRIAN_AUDIOSYSTEM_H
#define INTEGRIAN_AUDIOSYSTEM_H

#include <cstdint> // uint64_t
#include <SDL_mixer.h> // Mix_Chunk, Mix_Music, more SDL_Mixer related functionality
#include <string> // std::string
#include <unordered_map> // std::unordered_map

namespace Integrian
{
	class AudioSystem abstract
	{
	public:
		using SoundID = uint64_t;

		virtual ~AudioSystem() = default;

		void AddSound(const SoundID uniqueSoundID, const std::string& filePath);
		void AddMusic(const SoundID uniqueMusicID, const std::string& filePath);

		virtual void PlaySound(const SoundID, const float = 100.f) = 0;

	private:
		std::unordered_map<SoundID, Mix_Chunk*> m_Sounds;
		std::unordered_map<SoundID, Mix_Music*> m_Music;
	};
}

#endif // !INTEGRIAN_AUDIOSYSTEM_H