#include "SubprogramManager.h"
#include "ISubprogram.h"
#include "Logger.h"

SubprogramManager& SubprogramManager::instance()
{
  static SubprogramManager inst;
  return inst;
}

void SubprogramManager::registerFactory(UIMode mode, ProgramFactory factory)
{
  m_factories[mode] = std::move(factory);
}

// When new subprogram is chosen from Tools menu it has to be registered
// Returns true on success. False means factory function is missing.
bool SubprogramManager::registerProgram(UIMode mode, QWidget *parent)
{
  if ((m_programs.find(mode) != m_programs.end()) == false)
  {
    if ((m_factories.find(mode) != m_factories.end()) == false)
    {
      Logger::logError(QString("No factory registered for mode: %1").arg(static_cast<int>(mode)));
      return false;
    }
    m_programs[mode] = m_factories[mode](parent);
  }
  return true;
}

ISubprogram* SubprogramManager::getActiveProgram()
{
  auto it = m_programs.find(m_activeMode);
  return it != m_programs.end() ? it->second.get() : nullptr;

}

ISubprogram* SubprogramManager::getProgram(UIMode mode)
{
  auto it = m_programs.find(mode);
  return it != m_programs.end() ? it->second.get() : nullptr;

}

void SubprogramManager::closeProgram(UIMode mode)
{
  if (m_activeMode == mode)
  {
    // If the active program is being closed, deactivate it first
    if (auto* activeProgram = getActiveProgram())
    {
      activeProgram->onDeactivated();
    }
    m_activeMode = UIMode::None; // Reset active mode
  }

  if (m_programs.find(mode) != m_programs.end())
  {
    // Remove the program from the map
    m_programs.erase(mode);
    Logger::logDebug(QString("Closed subprogram for mode: %1").arg(static_cast<int>(mode)));
  }
}

// Activates subprogram. Has to be registered before.
void SubprogramManager::activateProgram(UIMode mode)
{
  if (m_activeMode == mode)
    return;

  // Deactivate the current program if it exists
  auto itPrev = m_programs.find(m_activeMode);
  if (itPrev != m_programs.end() && itPrev->second.get())
  {
    itPrev->second.get()->onDeactivated();
  }

  m_activeMode = mode;

  // Activate the new program if it exists
  auto itNext = m_programs.find(m_activeMode);
  if (itNext != m_programs.end() && itNext->second.get())
  {
    itNext->second.get()->onActivated();
  }
  else
  {
    Logger::logError(QString("No subprogram registered for mode: %1").arg(static_cast<int>(mode)));
  }
}