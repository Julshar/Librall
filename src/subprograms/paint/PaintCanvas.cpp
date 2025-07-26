#include "PaintCanvas.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "Random.h"
#include "Logger.h"

PaintCanvas::PaintCanvas(QWidget *parent)
  : QWidget(parent)
{
  setAttribute(Qt::WA_StaticContents);
  canvasImage = QImage(800, 600, QImage::Format_RGB32);
  canvasImage.fill(Qt::white);
  Random::seedWithTime();
}

void PaintCanvas::setPenColor(const QColor &color)
{
  penColor = color;
}

void PaintCanvas::setPenWidth(int width)
{
  penWidth = width;
}

void PaintCanvas::setDrawMode(DrawMode mode)
{
  currentDrawMode = mode;
  Logger::log("Draw mode set to: " + DrawModeUtils::toString(mode));
}

void PaintCanvas::resizeCanvas(int width, int height)
{
  if (width <= 0 || height <= 0) return;

  canvasImage = QImage(width, height, QImage::Format_RGB32);
  canvasImage.fill(Qt::white);
  viewOffset = {0, 0};
  zoomFactor = 1.0;
  updateGeometry();
  update();
  
  Logger::log(QString("Canvas resized to %1 x %2").arg(width).arg(height));
}

void PaintCanvas::zoomIn()
{
  zoomFactor *= 1.25;
  updateGeometry();
  update();
}

void PaintCanvas::zoomOut()
{
  zoomFactor /= 1.25;
  updateGeometry();
  update();
}

void PaintCanvas::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    QPointF lastPointF = (event->pos() / zoomFactor) - viewOffset;
    lastPoint = lastPointF.toPoint();
    drawing = true;

    if (currentDrawMode == DrawMode::Fill)
    {
      // TODO: Implement the fill tool logic
      Logger::log("Fill tool clicked at " + QString::number(lastPoint.x()) + ", " + QString::number(lastPoint.y()));
    }
    else if (currentDrawMode == DrawMode::Spray)
    {
      sprayAt(lastPoint);
    }
  }
  else if (event->button() == Qt::MiddleButton)
  {
    panning = true;
    panStartPoint = event->pos();
    setCursor(Qt::ClosedHandCursor); // visual feedback
  }
    
}

void PaintCanvas::mouseMoveEvent(QMouseEvent *event)
{
  if ((event->buttons() & Qt::LeftButton) && drawing)
  {
    QPoint scaledPos = (event->pos() / zoomFactor - viewOffset).toPoint();

    if (currentDrawMode == DrawMode::Spray)
    {
      sprayAt(scaledPos);
    }
    else
    {
      drawLineTo(scaledPos);
    }
  }
  else if (panning)
  {
    QPoint delta = event->pos() - panStartPoint;
    viewOffset += delta / zoomFactor; // Scale delta to logical coords
    panStartPoint = event->pos(); // Update starting point
    update();
  }
}

void PaintCanvas::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton && drawing)
  {
    if (currentDrawMode != DrawMode::Spray && currentDrawMode != DrawMode::Fill)
    {
      drawLineTo((event->pos() / zoomFactor - viewOffset).toPoint());
    }
    drawing = false;
  }
  else if (event->button() == Qt::MiddleButton)
  {
    panning = false;
    setCursor(Qt::ArrowCursor);
  }
}

void PaintCanvas::drawLineTo(const QPoint &endPoint)
{
  QPainter painter(&canvasImage);

  QColor colorToUse = (currentDrawMode == DrawMode::Eraser) ? Qt::white : penColor;
  QPen pen(colorToUse, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

  painter.setPen(pen);
  painter.drawLine(lastPoint, endPoint);

  int rad = penWidth + 2;
  QRect rect = QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad);

  QPointF topLeft = (rect.topLeft() + viewOffset) * zoomFactor;
  QSizeF size = rect.size() * zoomFactor;
  update(QRect(topLeft.toPoint(), size.toSize()));

  lastPoint = endPoint;
}

void PaintCanvas::sprayAt(const QPoint &point)
{
  Logger::logDebug(QString("Spraying at (%1, %2)").arg(point.x()).arg(point.y()));

  Logger::logDebug(QString("Spray color RGBA: (%1, %2, %3, %4)")
                 .arg(penColor.red()).arg(penColor.green()).arg(penColor.blue()).arg(penColor.alpha()));

  QPainter painter(&canvasImage);
  painter.setPen(Qt::NoPen);
  painter.setBrush(penColor);

  const int radius = penWidth * 2;

  for (int i = 0; i < sprayParticleCount; ++i)
  {
    int x = Random::genValue(0, radius * 2) - radius;
    int y = Random::genValue(0, radius * 2) - radius;
    // Make sure the point is within circle radius
    if (x * x + y * y <= radius * radius)
    {
      painter.drawEllipse(point + QPoint(x, y), 1, 1);
    }
  }

  QRect rect(point - QPoint(radius, radius), QSize(radius * 2, radius * 2));

  QPointF topLeft = (rect.topLeft() + viewOffset) * zoomFactor;
  QSizeF size = rect.size() * zoomFactor;
  update(QRect(topLeft.toPoint(), size.toSize()));
}

void PaintCanvas::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  painter.scale(zoomFactor, zoomFactor);
  painter.translate(viewOffset); // Apply panning offset

  painter.drawImage(QPoint(0, 0), canvasImage);
}

QSize PaintCanvas::sizeHint() const
{
  return canvasImage.size() * zoomFactor;
}

void PaintCanvas::clearCanvas()
{
  canvasImage.fill(Qt::white);
  update();
  Logger::log("Canvas cleared.");
}