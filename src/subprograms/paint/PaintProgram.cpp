#include "PaintProgram.h"
#include "PaintCanvas.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QSlider>
#include <QLabel>

PaintProgram::PaintProgram(QWidget* parent)
  : SubprogramBase(parent)
{
  // Nothing else needed here — lazy creation of widgets below
}

PaintProgram::~PaintProgram() = default;

QWidget* PaintProgram::getMainWidget()
{
  // Lazy init pattern
  static PaintCanvas* canvas = new PaintCanvas();
  return canvas;
}

QList<QWidget*> PaintProgram::getSidePanelControls()
{
  QList<QWidget*> controls;
  auto canvas = qobject_cast<PaintCanvas*>(getMainWidget());
  if (!canvas)
    return controls;

  // Color picker
  QPushButton* colorButton = new QPushButton("Choose Color");
  
  
  QObject::connect(colorButton, &QPushButton::clicked, [canvas]()
  {
    QColor color = QColorDialog::getColor(
    canvas->palette().color(canvas->backgroundRole()),
    nullptr,
    "Select Color"
    );
    if (color.isValid())
      canvas->setPenColor(color);
  });

  // Brush size slider
  QLabel* sizeLabel = new QLabel("Brush Size");
  QSlider* sizeSlider = new QSlider(Qt::Horizontal);
  sizeSlider->setRange(1, 30);
  sizeSlider->setValue(2);
  QObject::connect(sizeSlider, &QSlider::valueChanged, canvas, &PaintCanvas::setPenWidth);

  // Zoom buttons
  QPushButton* zoomInBtn = new QPushButton("Zoom In");
  QPushButton* zoomOutBtn = new QPushButton("Zoom Out");
  QObject::connect(zoomInBtn, &QPushButton::clicked, canvas, &PaintCanvas::zoomIn);
  QObject::connect(zoomOutBtn, &QPushButton::clicked, canvas, &PaintCanvas::zoomOut);

  // Add to list
  controls << colorButton << sizeLabel << sizeSlider << zoomInBtn << zoomOutBtn;
  return controls;
}

void PaintProgram::onActivated()
{
  // Optional: could focus canvas or log something
}

void PaintProgram::onDeactivated()
{
  // Optional: could reset tool state or save canvas
}