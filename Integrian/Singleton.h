#pragma once
#ifndef INTEGRIAN_SINGLETON_H
#define INTEGRIAN_SINGLETON_H

#include "IntegrianPCH.h" // precompiled header

namespace Integrian
{
	template<typename Type>
	class Singleton
	{
	public:
		virtual ~Singleton() = default;

		static Type& GetInstance()
		{
			static Type instance{};
			return instance;
		}

		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton& operator=(Singleton&&) = delete;
	
	protected:
		Singleton() = default;

	private:
	};
}

#endif // INTEGRIAN_SINGLETON_H