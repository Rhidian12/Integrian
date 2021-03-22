#pragma once

#ifndef INTEGRIAN_AUDIOSYSTEM_H
#define INTEGRIAN_AUDIOSYSTEM_H

#include <cstdint> // uint64_t
#include <SDL_mixer.h> // Mix_Chunk, Mix_Music, more SDL_Mixer related functionality
#include <string> // std::string
#include <unordered_map> // std::unordered_map
#include "ServiceInterface.h" // IService
#include <vector> // std::vector

namespace Integrian
{
	class AudioSystem abstract : public IService
	{
	public:
		using SoundID = int;
		using MusicID = int;

		AudioSystem();
		virtual ~AudioSystem();

		void AddSound(const SoundID uniqueSoundID, const std::string& filePath);
		void AddMusic(const MusicID uniqueMusicID, const std::string& filePath);

		virtual void PlaySound(const SoundID, const bool = false, const int = 0, const int = 100) = 0;
		virtual void PlayMusic(const MusicID, const bool = false, const int = 0, const int = 100) = 0;

		virtual void PauseMusic() = 0;
		virtual void PauseSound() = 0;

		virtual void RewindMusic() = 0;
		virtual void SetMusicPosition(double) = 0;

		virtual [[nodiscard]] bool IsMusicPlaying() const = 0;
		virtual [[nodiscard]] bool IsSoundPlaying() const = 0;

	protected:
		struct Channel final
		{
			Channel(const uint16_t index)
				: channelIndex{ index }
			{
			}

			bool isInUse{ false };
			uint16_t channelIndex; // uint16_t because the range is [0 - 7]
		};

		Channel& GetFirstAvailableChannel();

		std::unordered_map<SoundID, Mix_Chunk*> m_Sounds;
		std::unordered_map<MusicID, Mix_Music*> m_Music;

		inline static std::vector<Channel> m_Channels{};

		Mix_Music* m_pCurrentPlayingMusic{};

		using SoundPair = std::pair<SoundID, Mix_Chunk*>;
		using MusicPair = std::pair<MusicID, Mix_Music*>;
	};
}

#endif // !INTEGRIAN_AUDIOSYSTEM_H