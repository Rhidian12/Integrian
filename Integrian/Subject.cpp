#include "Subject.h"

void Integrian::Subject::AddObserver(std::weak_ptr<Observer> pObserver)
{
	m_pObservers.push_back(pObserver);
}
