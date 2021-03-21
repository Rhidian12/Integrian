#pragma once

#ifndef INTEGRIAN_NULLSERVICE_H
#define INTEGRIAN_NULLSERVICE_H

#include "AudioPlayerLogged.h"

namespace Integrian
{
	class NullService final : public AudioPlayerLogged
	{
	public:
		virtual void PlaySound(const SoundID, const bool = false, const int = 0, const int = 100) override {}
		virtual void PlayMusic(const SoundID, const bool = false, const int = 0, const int = 100) override {}
	};
}

#endif // !INTEGRIAN_NULLSERVICE_H