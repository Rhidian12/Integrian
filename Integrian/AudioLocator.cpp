#include "pch.h"
#include "AudioLocator.h"

void Integrian::AudioLocator::Cleanup()
{
	SafeDelete(m_pAudioSystem);
	SafeDelete(m_pNullService);

	// Something strange going on with SafeDelete() not setting this to a nullptr
	m_pAudioSystem = nullptr;
	m_pNullService = nullptr;
}

Integrian::AudioSystem* Integrian::AudioLocator::GetAudio()
{
	if (m_pAudioSystem)
		return m_pAudioSystem;

	Logger::LogWarning("GetAudio returned NullAudioService\n");
	return m_pNullService;
}