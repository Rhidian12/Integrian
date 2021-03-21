#pragma once

#ifndef INTEGRIAN_SERVICEINTERFACE_H
#define INTEGRIAN_SERVICEINTERFACE_H

namespace Integrian
{
	class IService abstract
	{
	public:
		IService() = default;
		virtual ~IService() = default;
	};
}

#endif // !INTEGRIAN_SERVICEINTERFACE_H