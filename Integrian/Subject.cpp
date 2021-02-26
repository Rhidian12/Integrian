#include "Subject.h"
#include <algorithm>

void Integrian::Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void Integrian::Subject::RemoveObserver(Observer* pObserver)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver));
}
