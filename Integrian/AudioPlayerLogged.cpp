#include "pch.h" // includes SDL_Mixer.h
#include "AudioPlayerLogged.h" // header
#include "Logger.h" // Logger
#include <string> // std::to_string

void Integrian::AudioPlayerLogged::PlaySound(const SoundID soundID, const bool infiniteLoop, const int amountOfLoops, const int volume)
{
	Logger& logger{ Logger::GetInstance() };
	if (m_Sounds.find(soundID) != m_Sounds.cend())
	{
		int loops{ amountOfLoops };
		if (infiniteLoop)
			loops = -1;

		Mix_VolumeChunk(m_Sounds[soundID], volume);
		if (Mix_PlayChannel(-1, m_Sounds[soundID], loops) == -1) // just take the first available channel
		{
			// something went wrong
			logger.Log("Sound with sound ID: ", ErrorLevel::error); // TODO: I M P R O V E T H I S 
			logger.Log(std::to_string(soundID), ErrorLevel::error);
			logger.Log(" could not be played ", ErrorLevel::error);
			logger.Log(Mix_GetError(), ErrorLevel::error);
			logger.Log("\n", ErrorLevel::error);
		}
		else
		{
			logger.Log("Sound with sound ID: ", ErrorLevel::noWarning);
			logger.Log(std::to_string(soundID), ErrorLevel::noWarning);
			logger.Log(" was played\n", ErrorLevel::noWarning);
		}
	}
#ifdef _DEBUG
	else
	{
		logger.Log("Sound with sound ID: ", ErrorLevel::error); // TODO: I M P R O V E T H I S 
		logger.Log(std::to_string(soundID), ErrorLevel::error);
		logger.Log(" was not found\n", ErrorLevel::error);
	}
#endif
}

void Integrian::AudioPlayerLogged::PlayMusic(const SoundID musicID, const bool infiniteLoop, const int amountOfLoops, const int volume)
{
	Logger& logger{ Logger::GetInstance() };
	if (m_Music.find(musicID) != m_Music.cend())
	{
		int loops{ amountOfLoops + 1 };
		if (infiniteLoop)
			loops = -1;

		// Mix_PlayingMusic() returns 1 if music is playing, but does not check if something has been paused
		if (m_pCurrentPlayingMusic && Mix_PlayingMusic() == 1) 
		{
			// if music is playing, stop the music
			Mix_HaltMusic();
		}

		//(void)volume;
		Mix_VolumeMusic(volume);
		if (Mix_PlayMusic(m_Music[musicID], loops) == -1)
		{
			// something went wrong
			logger.Log("Music with music ID: ", ErrorLevel::error); // TODO: I M P R O V E T H I S 
			logger.Log(std::to_string(musicID), ErrorLevel::error);
			logger.Log(" could not be played ", ErrorLevel::error);
			logger.Log(Mix_GetError(), ErrorLevel::error);
			logger.Log("\n", ErrorLevel::error);
		}
		else
		{
			m_pCurrentPlayingMusic = m_Music[musicID];
			logger.Log("Music with music ID: ", ErrorLevel::noWarning);
			logger.Log(std::to_string(musicID), ErrorLevel::noWarning);
			logger.Log(" was played\n", ErrorLevel::noWarning);
		}
	}
#ifdef _DEBUG
	else
	{
		logger.Log("Music with music ID: ", ErrorLevel::error); // TODO: I M P R O V E T H I S 
		logger.Log(std::to_string(musicID), ErrorLevel::error);
		logger.Log(" was not found\n", ErrorLevel::error);
	}
#endif
}
