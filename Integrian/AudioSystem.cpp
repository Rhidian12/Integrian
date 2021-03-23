#include "AudioSystem.h"
#include "Logger.h"

Integrian::AudioSystem::AudioSystem()
{
	for (uint16_t i{}; i < Mix_AllocateChannels(-1); ++i)
		m_Channels.push_back(Channel{ i });
}

Integrian::AudioSystem::~AudioSystem()
{
	m_pCurrentPlayingMusic = nullptr;
}

void Integrian::AudioSystem::Cleanup()
{
	for (const SoundPair& soundPair : m_Sounds)
		Mix_FreeChunk(soundPair.second);

	for (const MusicPair& musicPair : m_Music)
		Mix_FreeMusic(musicPair.second);
}

void Integrian::AudioSystem::AddSound(const SoundID uniqueSoundID, const std::string& filePath)
{
#ifdef _DEBUG
	if (m_Sounds.find(uniqueSoundID) != m_Sounds.cend())
		Logger::LogWarning("SoundID: " + std::to_string(uniqueSoundID) + " was already used and has not been added\n"); // this soundID has already been used
	else
	{
		Mix_Chunk* pTemp{ Mix_LoadWAV(filePath.c_str()) };
		if (pTemp == nullptr)
			Logger::LogError(filePath + " did not contain a sound file\n" + Mix_GetError());
		else
			m_Sounds.insert(std::make_pair(uniqueSoundID, pTemp));
	}
#else
	m_Sounds.insert(std::make_pair(uniqueSoundID, Mix_LoadWAV(filePath.c_str())));
#endif // _DEBUG
}

void Integrian::AudioSystem::AddMusic(const MusicID uniqueMusicID, const std::string& filePath)
{
#ifdef _DEBUG
	if (m_Music.find(uniqueMusicID) != m_Music.cend())
		Logger::LogWarning("MusicID: " + std::to_string(uniqueMusicID) + " was already used and has not been added\n"); // this MusicID has already been used
	else
	{
		Mix_Music* pTemp{ Mix_LoadMUS(filePath.c_str()) };
		if (pTemp == nullptr)
			Logger::LogError(filePath + " did not contain a Music file\n" + Mix_GetError());
		else
			m_Music.insert(std::make_pair(uniqueMusicID, pTemp));
	}
#else
	m_Music.insert(std::make_pair(uniqueMusicID, Mix_LoadMUS(filePath.c_str())));
#endif // _DEBUG
}

Integrian::AudioSystem::Channel& Integrian::AudioSystem::GetFirstAvailableChannel()
{
	return (*std::find_if(m_Channels.begin(), m_Channels.end(), [](Channel& c)->bool
		{
			return !c.isInUse;
		}));
}

float Integrian::AudioSystem::GetChunkTimeInSeconds(Mix_Chunk* pChunk) const
{
	Uint32 points = 0;
	Uint32 frames = 0;
	int freq = 0;
	Uint16 fmt = 0;
	int chans = 0;
	/* Chunks are converted to audio device format… */
	if (Mix_QuerySpec(&freq, &fmt, &chans) == 0)
	{
		Logger::LogError(std::string{ "GetChunkTimeInMilliSeconds() failed: " } + SDL_GetError());
		return 0;
	}

	/* bytes / samplesize == sample points */
	points = (pChunk->alen / ((fmt & 0xFF) / 8));

	/* sample points / channels == sample frames */
	frames = (points / chans);

	/* (sample frames * 1000) / frequency == play length in ms */
	return float(frames) / float(freq);
}

int Integrian::AudioSystem::RemapVolumeToSDL(const int volumeInPercentage) const
{
	return ((volumeInPercentage * m_SDLMixerMaxVolume) / 100);

	//NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
	// Reference: https://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
}

int Integrian::AudioSystem::RemapVolumeToIntegrian(const int volumeInSDL) const
{
	return ((volumeInSDL * 100) / m_SDLMixerMaxVolume);

	//NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
	// Reference: https://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
}
