#include "LoggedAudioSystem.h" // header
#include "Logger.h" // Logger
#include <string> // std::string, std::to_string

Integrian::LoggedAudioSystem::LoggedAudioSystem(AudioSystem* pAudio)
	: m_pAudioSystem{ pAudio }
{
}

bool Integrian::LoggedAudioSystem::OnEvent(const Event& event)
{
	return m_pAudioSystem->OnEvent(event);
}

Integrian::AudioSystem::SoundID Integrian::LoggedAudioSystem::AddSound(const std::string& filePath)
{
	Logger::LogNoWarning("A sound was added\n");
	return m_pAudioSystem->AddSound(filePath);
}

Integrian::AudioSystem::MusicID Integrian::LoggedAudioSystem::AddMusic(const std::string& filePath)
{
	Logger::LogNoWarning("A music file was added\n");
	return m_pAudioSystem->AddMusic(filePath);
}

void Integrian::LoggedAudioSystem::Update(const float dt)
{
	m_pAudioSystem->Update(dt);
}

void Integrian::LoggedAudioSystem::PlaySound(const SoundID soundID, const bool infiniteLoop, const int amountOfLoops, const int volume)
{
	m_pAudioSystem->PlaySound(soundID, infiniteLoop, amountOfLoops, volume);
}

void Integrian::LoggedAudioSystem::PlayMusic(const MusicID musicID, const bool infiniteLoop, const int amountOfLoops, const int volume)
{
	m_pAudioSystem->PlayMusic(musicID, infiniteLoop, amountOfLoops, volume);
}

void Integrian::LoggedAudioSystem::PauseMusic()
{
	Logger::LogNoWarning("Music was paused\n");
	m_pAudioSystem->PauseMusic();
}

void Integrian::LoggedAudioSystem::PauseSound(const SoundID soundID)
{
	Logger::LogNoWarning("The sound with soundID: " + std::to_string(soundID) + " was paused\n");
	m_pAudioSystem->PauseSound(soundID);
}

void Integrian::LoggedAudioSystem::RewindMusic()
{
	Logger::LogNoWarning("The music was rewinded to the start\n");
	m_pAudioSystem->RewindMusic();
}

void Integrian::LoggedAudioSystem::SetMusicPosition(double time)
{
	Logger::LogNoWarning("The music time was set to time: " + std::to_string(time) + "\n");
	m_pAudioSystem->SetMusicPosition(time);
}

void Integrian::LoggedAudioSystem::SetSoundVolume(const SoundID soundID, const int volume)
{
	Logger::LogNoWarning("The volume of soundID: " + std::to_string(soundID) + " was set to: " + std::to_string(volume) + "\n");
	m_pAudioSystem->SetSoundVolume(soundID, volume);
}

void Integrian::LoggedAudioSystem::SetMusicVolume(const int volume)
{
	Logger::LogNoWarning("The volume of the music was set to: " + std::to_string(volume) + "\n");
	m_pAudioSystem->SetMusicVolume(volume);
}

bool Integrian::LoggedAudioSystem::IsMusicPlaying() const
{
	return m_pAudioSystem->IsMusicPlaying();
}

bool Integrian::LoggedAudioSystem::IsSoundPlaying(const SoundID soundID) const
{
	return m_pAudioSystem->IsSoundPlaying(soundID);
}

int Integrian::LoggedAudioSystem::GetSoundVolume(const SoundID soundID) const
{
	return m_pAudioSystem->GetSoundVolume(soundID);
}

int Integrian::LoggedAudioSystem::GetMusicVolume() const
{
	return m_pAudioSystem->GetMusicVolume();
}
