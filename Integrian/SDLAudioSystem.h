#pragma once

#ifndef INTEGRIAN_SDLAUDIOSYSTEM_H
#define INTEGRIAN_SDLAUDIOSYSTEM_H

#include "AudioSystem.h" // AudioSystem
#include <map> // std::map

namespace Integrian
{
	class SDLAudioSystem final : public AudioSystem
	{
	public:
		SDLAudioSystem();
		virtual ~SDLAudioSystem();

		virtual bool OnEvent(const Event& event) override;

		virtual SoundID AddSound(const std::string& filePath) override;
		virtual MusicID AddMusic(const std::string& filePath) override;

		virtual void Update(const float dt) override;

		virtual void PlaySound(const SoundID soundID, const bool infiniteLoop = false, const int amountOfLoops= 0, const int volume = 100) override;
		virtual void PlayMusic(const MusicID soundID, const bool infiniteLoop = false, const int amountOfLoops= 0, const int volume = 100) override;

		virtual void PauseMusic() override;
		virtual void PauseSound(const SoundID soundID) override;

		virtual void RewindMusic() override;
		virtual void SetMusicPosition(double time) override;

		virtual void SetSoundVolume(const SoundID soundID, const int volume) override;
		virtual void SetMusicVolume(const int volume) override;

		virtual [[nodiscard]] bool IsMusicPlaying() const override;
		virtual [[nodiscard]] bool IsSoundPlaying(const SoundID soundID) const override;

		virtual [[nodiscard]] int GetSoundVolume(const SoundID soundID) const override;
		virtual [[nodiscard]] int GetMusicVolume() const override;

	private:
		struct Channel final
		{
			Channel(const uint16_t index)
				: channelIndex{ index }
			{
			}

			bool isInUse{ false };
			uint16_t channelIndex; // uint16_t because the range is [0 - 7]
			float timeInUse{};
			float expectedTimeInUse{};
			SoundID soundIDOfChunk{ std::numeric_limits<int>::max() }; // use max to minimize the possibility of it taking an existing ID
		};

		Channel& GetFirstAvailableChannel(std::vector<Channel>& channels);
		float GetChunkTimeInSeconds(Mix_Chunk* pChunk) const; // reference: https://discourse.libsdl.org/t/time-length-of-sdl-mixer-chunks/12852
		int RemapVolumeToSDL(const int volumeInPercentage) const;
		int RemapVolumeToIntegrian(const int volumeInSDL) const;

		std::map<SoundID, Mix_Chunk*> m_Sounds{}; // TODO: Make a wrapper for Mix_Chunk* and Mix_Music*
		std::map<MusicID, Mix_Music*> m_Music{};

		std::vector<Channel> m_Channels{};

		Mix_Music* m_pCurrentPlayingMusic{};

		const int m_SDLMixerMaxVolume{ MIX_MAX_VOLUME };

		using SoundPair = std::pair<SoundID, Mix_Chunk*>;
		using MusicPair = std::pair<MusicID, Mix_Music*>;
	};
}

#endif // !INTEGRIAN_SDLAUDIOSYSTEM_H