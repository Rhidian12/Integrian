#pragma once
#ifndef INTEGRIAN_COMPONENT_H
#define INTEGRIAN_COMPONENT_H

#include <string>
#include <vector>

namespace Integrian
{
	class Component abstract
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void Render() const {}

	protected:

	private:
	};
}

#endif //!INTEGRIAN_COMPONENT_H