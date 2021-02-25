#include "Observer.h"

void Integrian::Observer::OnNotify(const std::string& event)
{
	EventFunctionConstIt iterator{ m_pFunctions.find(event) };
	if (iterator != m_pFunctions.cend())
		for (std::function<void()> pFunction : iterator->second)
			pFunction();
}
