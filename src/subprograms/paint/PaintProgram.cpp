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
  canvas = new PaintCanvas(parent);
}

PaintProgram::~PaintProgram()
{
  delete canvas;
}

QWidget* PaintProgram::getMainWidget()
{
  return canvas;
}

QList<QWidget*> PaintProgram::getSidePanelControls()
{
  QList<QWidget*> controls;

  // Color picker
  QPushButton* colorButton = new QPushButton("Choose Color");
  QObject::connect(colorButton, &QPushButton::clicked, [this]()
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
  QSlider* penSizeSlider = new QSlider(Qt::Horizontal);
  penSizeSlider->setRange(1, 30);
  penSizeSlider->setValue(canvas->getPenWidth());
  penSizeSlider->setStyleSheet(R"(
  QSlider::handle:horizontal
  {
      background: #6eb800;
      width: 20px;
      border-radius: 12px;
  }
  QSlider::groove:horizontal
  {W
      height: 12px;
      background: #444;
  }
)");
  QObject::connect(penSizeSlider, &QSlider::valueChanged, canvas, &PaintCanvas::setPenWidth);

  // Zoom controls
  QPushButton* zoomInBtn = new QPushButton("Zoom In");
  QPushButton* zoomOutBtn = new QPushButton("Zoom Out");
  QObject::connect(zoomInBtn, &QPushButton::clicked, canvas, &PaintCanvas::zoomIn);
  QObject::connect(zoomOutBtn, &QPushButton::clicked, canvas, &PaintCanvas::zoomOut);

  controls << colorButton << sizeLabel << penSizeSlider << zoomInBtn << zoomOutBtn;
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