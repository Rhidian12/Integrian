#include "AudioSystem.h"
#include "Logger.h"

Integrian::AudioSystem::~AudioSystem()
{
	for (const SoundPair& soundPair : m_Sounds)
		Mix_FreeChunk(soundPair.second);

	for (const MusicPair& musicPair : m_Music)
		Mix_FreeMusic(musicPair.second);
}

void Integrian::AudioSystem::AddSound(const SoundID uniqueSoundID, const std::string& filePath)
{
#ifdef _DEBUG
	Logger& logger{ Logger::GetInstance() };
	if (m_Sounds.find(uniqueSoundID) != m_Sounds.cend())
	{
		// this soundID has already been used
		logger.Log("SoundID: ", ErrorLevel::warning); // TODO: IMPROVE THIS RHIDIAN
		logger.Log(std::to_string(uniqueSoundID), ErrorLevel::warning);
		logger.Log(" was already used and has not been added\n", ErrorLevel::warning);
	}
	else
	{
		Mix_Chunk* pTemp{ Mix_LoadWAV(filePath.c_str()) };
		if (pTemp == nullptr)
		{
			logger.Log(filePath, ErrorLevel::error);
			logger.Log(" did not contain a sound file\n", ErrorLevel::error);
			logger.Log(Mix_GetError(), ErrorLevel::error);
		}
		else
		{
			m_Sounds.insert(std::make_pair(uniqueSoundID, pTemp));
		}
	}
#else
	m_Sounds.insert(std::make_pair(uniqueSoundID, Mix_LoadWAV(filePath.c_str())));
#endif // _DEBUG
}

void Integrian::AudioSystem::AddMusic(const MusicID uniqueMusicID, const std::string& filePath)
{
#ifdef _DEBUG
	Logger& logger{ Logger::GetInstance() };
	if (m_Music.find(uniqueMusicID) != m_Music.cend())
	{
		// this MusicID has already been used
		logger.Log("MusicID: ", ErrorLevel::warning); // TODO: IMPROVE THIS RHIDIAN
		logger.Log(std::to_string(uniqueMusicID), ErrorLevel::warning);
		logger.Log(" was already used and has not been added\n", ErrorLevel::warning);
	}
	else
	{
		Mix_Music* pTemp{ Mix_LoadMUS(filePath.c_str()) };
		if (pTemp == nullptr)
		{
			logger.Log(filePath, ErrorLevel::error);
			logger.Log(" did not contain a sound file\n", ErrorLevel::error);
		}
		else
		{
			m_Music.insert(std::make_pair(uniqueMusicID, pTemp));
		}
	}
#else
	m_Music.insert(std::make_pair(uniqueMusicID, Mix_LoadMUS(filePath.c_str())));
#endif // _DEBUG
}
