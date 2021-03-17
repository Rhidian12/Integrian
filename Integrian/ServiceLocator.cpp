#include "ServiceLocator.h"

Integrian::InputManager& Integrian::ServiceLocator::GetInputManager()
{
    return m_Inputmanager;
}

Integrian::CommandManager& Integrian::ServiceLocator::GetCommandManager()
{
    return m_CommandManager;
}

Integrian::PrinterManager& Integrian::ServiceLocator::GetPrinterManager()
{
    return m_PrinterManager;
}

Integrian::TextureManager& Integrian::ServiceLocator::GetTextureManager()
{
    return m_TextureManager;
}

Integrian::Logger& Integrian::ServiceLocator::GetLogger()
{
    return m_Logger;
}
