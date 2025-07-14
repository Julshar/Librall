#pragma once

#include <QWidget>
#include <map>
#include <memory>
#include "UIMode.h"

class ISubprogram;

// Factory function for creating subprograms
using ProgramFactory = std::function<std::unique_ptr<ISubprogram>(QWidget *parent)>;

class SubprogramManager
{
public:
  static SubprogramManager& instance();

  void registerFactory(UIMode mode, ProgramFactory factory);
  bool registerProgram(UIMode mode, QWidget *parent);
  ISubprogram* getActiveProgram();
  ISubprogram* getProgram(UIMode mode);
  void closeProgram(UIMode mode);
  void activateProgram(UIMode mode);

private:
  SubprogramManager() = default;

  UIMode m_activeMode = UIMode::None;
  
  std::map<UIMode, std::unique_ptr<ISubprogram>> m_programs; // Storage for active subprograms
  std::map<UIMode, ProgramFactory> m_factories; // Storage for subprogram factories
};