#include "IntegrianPCH.h"
#include "IApp.h"
#include "App.h"

Integrian::IApp::IApp(const char* pName)
	: m_pApp{ new App{pName} }
{
}

uint32_t Integrian::IApp::GetWindowWidth() const noexcept
{
	return uint32_t();
}

uint32_t Integrian::IApp::GetWindowHeight() const noexcept
{
	return uint32_t();
}
