#include "DrawMode.h"
#include "PaintProgram.h"
#include "PaintCanvas.h"
#include "Logger.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QSlider>
#include <QLabel>
#include <QToolButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QWidget>

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

  QWidget* toolSelectionWidget = createToolSelectionWidget(this);

  QPushButton* clearCanvasBtn = new QPushButton("Clear");
  QObject::connect(clearCanvasBtn, &QPushButton::clicked, canvas, &PaintCanvas::clearCanvas);

  controls << toolSelectionWidget << colorButton << sizeLabel << penSizeSlider << zoomInBtn << zoomOutBtn << clearCanvasBtn;
  return controls;
}

void PaintProgram::onActivated()
{
  Logger::log("[PaintProgram] Activated.");
}

void PaintProgram::onDeactivated()
{
  Logger::log("[PaintProgram] Deactivated.");
}

QWidget* PaintProgram::createToolSelectionWidget(QObject* parentObject)
{
  QWidget* container = new QWidget;
  QGridLayout* layout = new QGridLayout(container);

  QButtonGroup* buttonGroup = new QButtonGroup(parentObject); // Parent should be something that lives long, e.g. PaintProgram

  buttonGroup->setExclusive(true); // Only one button can be selected

  QList tools = {DrawMode::Brush,
                 DrawMode::Eraser,
                 DrawMode::Spray,
                 DrawMode::Fill};
  
  for (int i = 0; i < tools.size(); ++i)
  {
    QToolButton* button = new QToolButton;
    button->setText(DrawModeUtils::toString(tools[i]));
    button->setCheckable(true);  // Allows it to stay "pressed"
    
    layout->addWidget(button, i / 2, i % 2); // 2-column grid

    buttonGroup->addButton(button, i); // Use the index as the button ID
  }

  QObject::connect(buttonGroup, &QButtonGroup::idClicked, this, [=](int id) {
  DrawMode selectedTool = tools[id];
  Logger::log("Selected tool: " + DrawModeUtils::toString(selectedTool));
  canvas->setDrawMode(selectedTool);
  });

  return container;
}