#pragma once

#ifndef INTEGRIAN_SERVICELOCATOR_H
#define INTEGRIAN_SERVICELOCATOR_H

#include "pch.h" // AlwaysFalse()
#include <type_traits> // std::is_same_v, std::is_base_of_v
#include "Logger.h" // Logger
#include "NullAudioSystem.h" // NullAudioSystem
#include "SDLAudioSystem.h" // AudioPlayerLogged

namespace Integrian
{
	class AudioLocator final // There is no such thing as a static class in C++
	{
	public:
		static void Cleanup();

		[[nodiscard]] inline static AudioSystem* GetAudio()
		{
			if (m_pAudioSystem)
				return m_pAudioSystem;

			Logger::LogWarning("GetAudio returned NullAudioService\n");
			return m_pNullService;
		}

		template<typename Type>
		inline static void Provide(Type* pAudio)
		{
			if constexpr (std::is_base_of_v<AudioSystem, Type>)
			{
				if (pAudio != nullptr && !std::is_same_v<Type, NullAudioSystem>)
					m_pAudioSystem = pAudio;
			}
			else
				static_assert(AlwaysFalse(), "The pointer supplied to AudioLocator::Provide() was not an AudioSystem");
		}

	private:
		AudioLocator() = default;

		inline static AudioSystem* m_pAudioSystem{};
		inline static AudioSystem* m_pNullService{ new NullAudioSystem{} };
	};
}

#endif // !INTEGRIAN_SERVICELOCATOR_H