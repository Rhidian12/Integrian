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

	if (!m_HasWarningBeenPrinted)
	{
		Logger::LogWarning("GetAudio returned NullAudioService\n");
		m_HasWarningBeenPrinted = true;
	}

	return m_pNullService;
}