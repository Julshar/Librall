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
#include <QSpinBox>
#include <QFileDialog>

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
  penSizeSlider->setRange(1, 100);
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

  QPushButton* resizeCanvasButton = new QPushButton("New Canvas");
  QObject::connect(resizeCanvasButton, &QPushButton::clicked, this, &PaintProgram::handleCanvasResize);

  QPushButton* exportBtn = new QPushButton("Export Image");
  QObject::connect(exportBtn, &QPushButton::clicked, [this]() {
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Image", "", "PNG Files (*.png);;JPEG Files (*.jpg)");
    if (!fileName.isEmpty())
    {
      canvas->saveToFile(fileName);
    }
  });

  controls << toolSelectionWidget << colorButton << sizeLabel << penSizeSlider << zoomInBtn <<
  zoomOutBtn << clearCanvasBtn << resizeCanvasButton << exportBtn;

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

void PaintProgram::handleCanvasResize()
{
  QDialog dialog;
  dialog.setWindowTitle("New Canvas Size");

  QVBoxLayout layout(&dialog);

  QSpinBox* widthBox = new QSpinBox;
  widthBox->setRange(100, 5000);
  widthBox->setValue(800);

  QSpinBox* heightBox = new QSpinBox;
  heightBox->setRange(100, 5000);
  heightBox->setValue(600);

  layout.addWidget(new QLabel("Width:"));
  layout.addWidget(widthBox);
  layout.addWidget(new QLabel("Height:"));
  layout.addWidget(heightBox);

  QPushButton* okBtn = new QPushButton("OK");
  QPushButton* cancelBtn = new QPushButton("Cancel");

  QHBoxLayout* btnLayout = new QHBoxLayout;
  btnLayout->addWidget(okBtn);
  btnLayout->addWidget(cancelBtn);
  layout.addLayout(btnLayout);

  QObject::connect(okBtn, &QPushButton::clicked, [&]() {
    canvas->resizeCanvas(widthBox->value(), heightBox->value());
    dialog.accept();
  });
  QObject::connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

  dialog.exec();
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