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
    lastPoint = event->pos() / zoomFactor;
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
}

void PaintCanvas::mouseMoveEvent(QMouseEvent *event)
{
  if ((event->buttons() & Qt::LeftButton) && drawing)
  {
    QPoint scaledPos = event->pos() / zoomFactor;

    if (currentDrawMode == DrawMode::Spray)
    {
      sprayAt(scaledPos);
    }
    else
    {
      drawLineTo(scaledPos);
    }
  }
}

void PaintCanvas::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton && drawing)
  {
    if (currentDrawMode != DrawMode::Spray && currentDrawMode != DrawMode::Fill)
    {
      drawLineTo(event->pos() / zoomFactor);
    }
    drawing = false;
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
  update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad));
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

  const int particles = 100;
  const int radius = penWidth * 2;

  for (int i = 0; i < particles; ++i)
  {
    int x = Random::genValue(0, radius * 2) - radius;
    int y = Random::genValue(0, radius * 2) - radius;
    // Make sure the point is within circle radius
    if (x * x + y * y <= radius * radius)
    {
      // Logger::logDebug(QString("Spraying particle at (%1, %2)").arg(point.x() + x).arg(point.y() + y));

      painter.drawEllipse(point + QPoint(x, y), 1, 1);
    }
  }

  update(QRect(point - QPoint(radius, radius), QSize(radius * 2, radius * 2)));
}

void PaintCanvas::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  painter.scale(zoomFactor, zoomFactor);
  QRectF sourceRect(
    event->rect().x() / zoomFactor,
    event->rect().y() / zoomFactor,
    event->rect().width() / zoomFactor,
    event->rect().height() / zoomFactor
  );
  painter.drawImage(sourceRect, canvasImage, sourceRect);
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