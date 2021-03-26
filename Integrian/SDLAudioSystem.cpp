#include "pch.h" // includes SDL_Mixer.h
#include "SDLAudioSystem.h" // header
#include "Logger.h" // Logger
#include <string> // std::to_string
#include <future> // std::async
#include "ThreadManager.h"

#include "VisualBenchmark.h" // TODO: REMOVE THIS

extern bool g_IsLooping;

Integrian::SDLAudioSystem::SDLAudioSystem()
{
	for (uint16_t i{}; i < Mix_AllocateChannels(-1); ++i)
		m_Channels.push_back(Channel{ i });
}

Integrian::SDLAudioSystem::~SDLAudioSystem()
{
	for (const SoundPair& soundPair : m_Sounds)
		Mix_FreeChunk(soundPair.second);

	for (const MusicPair& musicPair : m_Music)
		Mix_FreeMusic(musicPair.second);
}

bool Integrian::SDLAudioSystem::OnEvent(const Event& event)
{
	TIME();

	switch (event.GetEvent())
	{
	case Events::PlaySound:
	{
		auto data{ event.GetData<SoundID, bool, int, int>() };
		ThreadManager::GetInstance().AssignThread([this, data]()
			{
				PlaySound(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
			});
		return true;
	}
	break;
	case Events::PlayMusic:
	{
		auto data{ event.GetData<MusicID, bool, int, int>() };
		ThreadManager::GetInstance().AssignThread([this, data]()
			{
				PlaySound(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
			});
		return true;
	}
	break;
	default:
		return false;
		break;
	}
}

Integrian::AudioSystem::SoundID Integrian::SDLAudioSystem::AddSound(const std::string& filePath)
{
#ifdef _DEBUG
	SoundID newSoundID{};

	if (m_Sounds.empty())
		newSoundID = 0;
	else
		newSoundID = ((m_Sounds.end()--)->first) + 1;

	Mix_Chunk* pTemp{ Mix_LoadWAV(filePath.c_str()) };
	if (pTemp == nullptr)
	{
		Logger::LogError(filePath + " did not contain a sound file\n" + Mix_GetError());
		return -1;
	}
	else
	{
		m_Sounds.insert(std::make_pair(newSoundID, pTemp));
		return newSoundID;
	}
#else
	SoundID newSoundID{};

	if (m_Sounds.empty())
		newSoundID = 0;
	else
		newSoundID = ((m_Sounds.end()--)->first) + 1;

	if (m_Sounds.empty())
		m_Sounds.insert(std::make_pair(newSoundID, Mix_LoadWAV(filePath.c_str())));
	else
		m_Sounds.insert(std::make_pair(newSoundID, Mix_LoadWAV(filePath.c_str())));

	return newSoundID;
#endif // _DEBUG
}

Integrian::AudioSystem::MusicID Integrian::SDLAudioSystem::AddMusic(const std::string& filePath)
{
#ifdef _DEBUG
	MusicID newMusicID{};

	if (m_Music.empty())
		newMusicID = 0;
	else
		newMusicID = ((m_Music.end()--)->first) + 1;

	Mix_Music* pTemp{ Mix_LoadMUS(filePath.c_str()) };
	if (pTemp == nullptr)
	{
		Logger::LogError(filePath + " did not contain a music file\n");
		return -1;
	}
	else
	{
		m_Music.insert(std::make_pair(newMusicID, pTemp));
		return newMusicID;
	}
#else
	MusicID newMusicID{};

	if (m_Music.empty())
		newMusicID = 0;
	else
		newMusicID = ((m_Music.end()--)->first) + 1;

	if (m_Music.empty())
		m_Music.insert(std::make_pair(newMusicID, Mix_LoadMUS(filePath.c_str())));
	else
		m_Music.insert(std::make_pair(newMusicID, Mix_LoadWAV(filePath.c_str())));

	return newMusicID;
#endif // _DEBUG
}

void Integrian::SDLAudioSystem::Update(const float dt)
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

				Logger::LogNoWarning("Channel " + std::to_string(channel.channelIndex) + " is ready for use again\n");
			}
		}
	}
}

void Integrian::SDLAudioSystem::PlaySound(const SoundID soundID, const bool infiniteLoop, const int amountOfLoops, const int volume)
{
	if (m_Sounds.find(soundID) != m_Sounds.cend())
	{
		int loops{ amountOfLoops };
		if (infiniteLoop)
			loops = -1;

		Mix_VolumeChunk(m_Sounds[soundID], RemapVolumeToSDL(volume));
		Channel& channel{ GetFirstAvailableChannel(m_Channels) };
		if (Mix_PlayChannel(channel.channelIndex, m_Sounds[soundID], loops) == -1)
		{
			// something went wrong
			Logger::LogError((("Sound with sound ID: " + std::to_string(soundID)) + " could not be played: ") + Mix_GetError() + "\n");
		}
		else
		{
			Logger::LogNoWarning("Sound with sound ID: " + std::to_string(soundID) + " was played on channel "
				+ std::to_string(channel.channelIndex) + "\n");
			channel.isInUse = true;
			channel.expectedTimeInUse = GetChunkTimeInSeconds(m_Sounds[soundID]);
			channel.soundIDOfChunk = soundID;
		}
	}
#ifdef _DEBUG
	else
		Logger::LogError("Sound with sound ID: " + std::to_string(soundID) + " was not found\n");
#endif
}

void Integrian::SDLAudioSystem::PlayMusic(const MusicID musicID, const bool infiniteLoop, const int amountOfLoops, const int volume)
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

void Integrian::SDLAudioSystem::PauseMusic()
{
	Mix_PauseMusic();
}

void Integrian::SDLAudioSystem::PauseSound(const SoundID soundID)
{
	for (const Channel& channel : m_Channels)
		if (channel.soundIDOfChunk == soundID)
			return Mix_Pause(channel.channelIndex);

	Logger::LogWarning("The SoundID provided to PauseSound() was not found\n");
}

void Integrian::SDLAudioSystem::RewindMusic()
{
	Mix_RewindMusic();
}

void Integrian::SDLAudioSystem::SetMusicPosition(double time)
{
	switch (Mix_GetMusicType(m_pCurrentPlayingMusic))
	{
	case MUS_OGG:
	case MUS_MOD:
		if (Mix_SetMusicPosition(time) == -1)
			Logger::LogError(std::string{ "SetMusicPosition() failed: " } + Mix_GetError() + "\n");
		break;
	case MUS_MP3:
		RewindMusic();
		if (Mix_SetMusicPosition(time) == -1)
			Logger::LogError(std::string{ "SetMusicPosition() failed: " } + Mix_GetError() + "\n");
		break;
	default:
		Logger::LogWarning("SetMusicPosition() only supports .mp3, .ogg and .mod music formats\n");
	}
}

void Integrian::SDLAudioSystem::SetSoundVolume(const SoundID soundID, const int volume)
{
	if (m_Sounds.find(soundID) != m_Sounds.cend())
		Mix_VolumeChunk(m_Sounds[soundID], RemapVolumeToSDL(volume));
	else
		Logger::LogWarning("GetSoundVolume was called with a not-used SoundID\n");
}

void Integrian::SDLAudioSystem::SetMusicVolume(const int volume)
{
	Mix_VolumeMusic(RemapVolumeToSDL(volume));
}

bool Integrian::SDLAudioSystem::IsMusicPlaying() const
{
	return Mix_PlayingMusic() == 1;
}

bool Integrian::SDLAudioSystem::IsSoundPlaying(const SoundID soundID) const
{
	for (const Channel& channel : m_Channels)
		if (channel.soundIDOfChunk == soundID)
			return Mix_Playing(channel.channelIndex) == 1;

	Logger::LogWarning("The SoundID provided to IsSoundPlaying() was not found\n");
	return false;
}

int Integrian::SDLAudioSystem::GetSoundVolume(const SoundID soundID) const
{
	if (m_Sounds.find(soundID) != m_Sounds.cend())
		return RemapVolumeToIntegrian(Mix_VolumeChunk(m_Sounds.find(soundID)->second, -1));
	else
		Logger::LogWarning("GetSoundVolume was called with a not-used SoundID\n");
	return 0;
}

int Integrian::SDLAudioSystem::GetMusicVolume() const
{
	return RemapVolumeToIntegrian(Mix_VolumeMusic(-1));
}

Integrian::SDLAudioSystem::Channel& Integrian::SDLAudioSystem::GetFirstAvailableChannel(std::vector<Channel>& channels)
{
	return (*std::find_if(channels.begin(), channels.end(), [](Channel& c)->bool
		{
			return !c.isInUse;
		}));
}

float Integrian::SDLAudioSystem::GetChunkTimeInSeconds(Mix_Chunk* pChunk) const
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

int Integrian::SDLAudioSystem::RemapVolumeToSDL(const int volumeInPercentage) const
{
	return ((volumeInPercentage * m_SDLMixerMaxVolume) / 100);

	//NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
	// Reference: https://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
}

int Integrian::SDLAudioSystem::RemapVolumeToIntegrian(const int volumeInSDL) const
{
	return ((volumeInSDL * 100) / m_SDLMixerMaxVolume);

	//NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
	// Reference: https://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
}
