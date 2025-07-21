#pragma once

#include <QWidget>
#include <map>
#include <memory>
#include <vector>
#include "UIMode.h"

class SubprogramBase;

// Factory function for creating subprograms
using ProgramFactory = std::function<std::unique_ptr<SubprogramBase>(QWidget *parent)>;

class SubprogramManager
{
public:
  static SubprogramManager& instance();

  void registerFactory(UIMode mode, ProgramFactory factory);
  bool registerProgram(UIMode mode, QWidget *parent);
  SubprogramBase* getActiveProgram();
  SubprogramBase* getProgram(UIMode mode);
  void closeProgram(UIMode mode);
  void activateProgram(UIMode mode);
  std::vector<UIMode> getOpenedModes() const;

private:
  SubprogramManager() = default;

  UIMode m_activeMode = UIMode::None;
  
  std::map<UIMode, std::unique_ptr<SubprogramBase>> m_programs; // Storage for active subprograms
  std::map<UIMode, ProgramFactory> m_factories; // Storage for subprogram factories
};