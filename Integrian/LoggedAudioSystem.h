#pragma once

#ifndef INTEGRIAN_LOGGEDAUDIOSYSTEM_H
#define INTEGRIAN_LOGGEDAUDIOSYSTEM_H

#include "AudioSystem.h" // AudioSystem

namespace Integrian
{
	class LoggedAudioSystem final : public AudioSystem
	{
	public:
		LoggedAudioSystem(AudioSystem* pAudio);
		~LoggedAudioSystem() = default;

		virtual bool OnEvent(const Event& event) override;

		virtual SoundID AddSound(const std::string& filePath) override;
		virtual MusicID AddMusic(const std::string& filePath) override;

		virtual void Update(const float dt) override;

		virtual void PlaySound(const SoundID soundID, const bool infiniteLoop = false, const int amountOfLoops = 0, const int volume = 100) override;
		virtual void PlayMusic(const MusicID musicID, const bool infiniteLoop = false, const int amountOfLoops = 0, const int volume = 100) override;

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
		AudioSystem* m_pAudioSystem;
	};
}

#endif // !INTEGRIAN_LOGGEDAUDIOSYSTEM_H