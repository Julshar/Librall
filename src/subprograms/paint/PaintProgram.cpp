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

  controls << toolSelectionWidget << colorButton << sizeLabel << penSizeSlider << zoomInBtn << zoomOutBtn;
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
    button->setText(getDrawModeName(tools[i]));
    button->setCheckable(true);  // Allows it to stay "pressed"
    
    layout->addWidget(button, i / 2, i % 2); // 2-column grid

    buttonGroup->addButton(button, i); // Use the index as the button ID
  }

  QObject::connect(buttonGroup, &QButtonGroup::idClicked, this, [=](int id) {
  DrawMode selectedTool = tools[id];
  Logger::log("Selected tool: " + getDrawModeName(selectedTool));
  // Update tool state here
});

  return container;
}

QString PaintProgram::getDrawModeName(DrawMode mode) const
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