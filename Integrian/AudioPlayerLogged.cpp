#include "pch.h" // includes SDL_Mixer.h
#include "AudioPlayerLogged.h" // header
#include "Logger.h" // Logger
#include <string> // std::to_string
#include <future> // std::async
#include <algorithm> // std::find

#include "VisualBenchmark.h" // TODO: REMOVE THIS

bool Integrian::AudioPlayerLogged::OnEvent(const Event& event)
{
	TIME();

	switch (event.GetEvent())
	{
	case Events::PlaySound:
	{
		auto data{ event.GetData<int, bool, int, int>() };
		auto future = std::async(std::launch::async, [&data, this]()
			{
				PlaySound(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
			});
		return true;
	}
	break;
	case Events::PlayMusic:
	{
		auto data{ event.GetData<MusicID, bool, int, int>() };
		auto future = std::async(std::launch::async, [&data, this]()
			{
				PlayMusic(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
			});
		return true;
	}
	break;
	default:
		return false;
		break;
	}
}

void Integrian::AudioPlayerLogged::Update(const float dt)
{
	for (Channel& channel : m_Channels)
	{
		if (channel.isInUse)
		{
			channel.timeInUse += dt;
			if (channel.timeInUse >= channel.expectedTimeInUse && Mix_Playing(channel.channelIndex) == 0) 
			{
				// if both SDL_Mixer and the calculations agree that the sound is no longer playing, set the channel to be used again
				channel.isInUse = false;
				channel.expectedTimeInUse = 0;
				channel.timeInUse = 0;
				channel.soundIDOfChunk = std::numeric_limits<int>::max();
			}
		}
	}
}

void Integrian::AudioPlayerLogged::PlaySound(const SoundID soundID, const bool infiniteLoop, const int amountOfLoops, const int volume)
{
	if (m_Sounds.find(soundID) != m_Sounds.cend())
	{
		int loops{ amountOfLoops };
		if (infiniteLoop)
			loops = -1;

		Mix_VolumeChunk(m_Sounds[soundID], volume);
		Channel& channel{ GetFirstAvailableChannel() };
		if (Mix_PlayChannel(channel.channelIndex, m_Sounds[soundID], loops) == -1)
		{
			// something went wrong
			Logger::LogError((("Sound with sound ID: " + std::to_string(soundID)) + " could not be played: ") + Mix_GetError() + "\n");
		}
		else
		{
			Logger::LogNoWarning("Sound with sound ID: " + std::to_string(soundID) + " was played\n");
			channel.isInUse = true;
			channel.expectedTimeInUse = GetChunkTimeInMilliseconds(m_Sounds[soundID]);
			channel.soundIDOfChunk = soundID;
		}
	}
#ifdef _DEBUG
	else
		Logger::LogError("Sound with sound ID: " + std::to_string(soundID) + " was not found\n");
#endif
}

void Integrian::AudioPlayerLogged::PlayMusic(const MusicID musicID, const bool infiniteLoop, const int amountOfLoops, const int volume)
{
	if (m_Music.find(musicID) != m_Music.cend())
	{
		int loops{ amountOfLoops + 1 };
		if (infiniteLoop)
			loops = -1;

		// Mix_PlayingMusic() returns 1 if music is playing, but does not check if a CHANNEL has been paused
		if (m_pCurrentPlayingMusic && Mix_PlayingMusic() == 1)
		{
			// if music is playing, stop the music
			Mix_HaltMusic();
		}

		Mix_VolumeMusic(volume);
		if (Mix_PlayMusic(m_Music[musicID], loops) == -1)
			// something went wrong
			Logger::LogError((("Music with Music ID: " + std::to_string(musicID)) + " could not be played: ") + Mix_GetError() + "\n");
		else
		{
			m_pCurrentPlayingMusic = m_Music[musicID];
			Logger::LogNoWarning("Music with Music ID: " + std::to_string(musicID) + " was played\n");
		}
	}
#ifdef _DEBUG
	else
		Logger::LogError("Music with Music ID: " + std::to_string(musicID) + " was not found\n");
#endif
}

void Integrian::AudioPlayerLogged::PauseMusic()
{
	Mix_PauseMusic();
}

void Integrian::AudioPlayerLogged::PauseSound(const SoundID soundID)
{
	for (const Channel& channel : m_Channels)
		if (channel.soundIDOfChunk == soundID)
			return Mix_Pause(channel.channelIndex);

	Logger::LogWarning("The SoundID provided to IsSoundPlaying() was not found\n");
}

void Integrian::AudioPlayerLogged::RewindMusic()
{
	Mix_RewindMusic();
}

void Integrian::AudioPlayerLogged::SetMusicPosition(double time)
{
	switch (Mix_GetMusicType(m_pCurrentPlayingMusic))
	{
	case MUS_OGG:
	case MUS_MOD:
		if (Mix_SetMusicPosition(time) == -1)
			Logger::LogError(std::string{ "SetMusicPosition() failed: " } + Mix_GetError() + "\n");
		else
			Logger::LogNoWarning("Music position set to: " + std::to_string(time) + "\n");
		break;
	case MUS_MP3:
		RewindMusic();
		if (Mix_SetMusicPosition(time) == -1)
			Logger::LogError(std::string{ "SetMusicPosition() failed: " } + Mix_GetError() + "\n");
		else
			Logger::LogNoWarning("Music position set to: " + std::to_string(time) + "\n");
		break;
	default:
		Logger::LogWarning("SetMusicPosition() only supports .mp3, .ogg and .mod music formats\n");
	}
}

bool Integrian::AudioPlayerLogged::IsMusicPlaying() const
{
	return Mix_PlayingMusic() == 1;
}

bool Integrian::AudioPlayerLogged::IsSoundPlaying(const SoundID soundID) const
{
	for (const Channel& channel : m_Channels)
		if (channel.soundIDOfChunk == soundID)
			return Mix_Playing(channel.channelIndex) == 1;

	Logger::LogWarning("The SoundID provided to IsSoundPlaying() was not found\n");
	return false;
}
