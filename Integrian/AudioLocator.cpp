#include "IntegrianPCH.h" // Precompiled header
#include "AudioLocator.h" // Header

void Integrian::AudioLocator::Cleanup()
{
	SafeDelete(m_pAudioSystem);
	SafeDelete(m_pNullService);
}

Integrian::AudioSystem* Integrian::AudioLocator::GetAudio()
{
	if (m_pAudioSystem)
		return m_pAudioSystem;

	Logger::LogWarning("GetAudio returned NullAudioService\n");
	return m_pNullService;
}