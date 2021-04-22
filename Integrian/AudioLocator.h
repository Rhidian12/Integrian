#pragma once

#ifndef INTEGRIAN_SERVICELOCATOR_H
#define INTEGRIAN_SERVICELOCATOR_H

#include <type_traits> // std::is_same_v, std::is_base_of_v
#include "Logger.h" // Logger
#include "NullAudioSystem.h" // NullAudioSystem
#include "SDLAudioSystem.h" // AudioPlayerLogged

namespace Integrian
{
	class AudioLocator final
	{
	public:
		static void Cleanup();

		[[nodiscard]] static AudioSystem* GetAudio();

		template<typename Type>
		static void Provide(Type* pAudio)
		{
			if constexpr (std::is_base_of_v<AudioSystem, Type>)
			{
				if (pAudio != nullptr && !std::is_same_v<Type, NullAudioSystem>) // maybe change this later to make NullAudioSystem private?
					m_pAudioSystem = pAudio;
				else
					m_pAudioSystem = nullptr;
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