#pragma once
#ifndef INTEGRIAN_COMPONENT_H
#define INTEGRIAN_COMPONENT_H

#include "TypeDefines.h"

namespace Integrian
{
	class Component abstract
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void Update(const float) {}
		virtual void FixedUpdate(const float) {}
		virtual void LateUpdate(const float) {}
		
		virtual void Render(const Point2f&) const {}

	protected:

	private:
	};
}

#endif //!INTEGRIAN_COMPONENT_H