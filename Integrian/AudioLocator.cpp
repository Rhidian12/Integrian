#include "pch.h"
#include "AudioLocator.h"

void Integrian::AudioLocator::Cleanup()
{
	SafeDelete(m_pAudioSystem);
	SafeDelete(m_pNullService);
}
