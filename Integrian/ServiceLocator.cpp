#include "ServiceLocator.h"

const Integrian::InputManager& Integrian::ServiceLocator::GetInputManager() const
{
    return m_Inputmanager;
}

const Integrian::CommandManager& Integrian::ServiceLocator::GetCommandManager() const
{
    return m_CommandManager;
}

const Integrian::PrinterManager& Integrian::ServiceLocator::GetPrinterManager() const
{
    return m_PrinterManager;
}

const Integrian::TextureManager& Integrian::ServiceLocator::GetTextureManager() const
{
    return m_TextureManager;
}

const Integrian::Logger& Integrian::ServiceLocator::GetLogger() const
{
    return m_Logger;
}
