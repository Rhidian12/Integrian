#include "AppInfoLocator.h"

Integrian::App_Info* Integrian::AppInfoLocator::GetAppInfo()
{
	if (m_pAppInfo)
		return m_pAppInfo;
	else
		return nullptr;
}
