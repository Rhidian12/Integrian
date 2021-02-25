#include "Subject.h"

void Integrian::Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}
