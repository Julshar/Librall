#pragma once

#include <QString>

enum class DrawMode
{
  Brush,
  Eraser,
  Spray,
  Fill
};

namespace DrawModeUtils
{
  inline QString toString(DrawMode mode)
  {
    switch (mode)
    {
      case DrawMode::Brush: return "Brush";
      case DrawMode::Eraser: return "Eraser";
      case DrawMode::Spray: return "Spray";
      case DrawMode::Fill: return "Fill";
      default: return "Unknown";
    }
  }
}