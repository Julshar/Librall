#include "PaintCanvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

PaintCanvas::PaintCanvas(QWidget *parent)
  : QWidget(parent)
{
  setAttribute(Qt::WA_StaticContents);
  canvasImage = QImage(800, 600, QImage::Format_RGB32);
  canvasImage.fill(Qt::white);
}

void PaintCanvas::setPenColor(const QColor &color)
{
  penColor = color;
}

void PaintCanvas::setPenWidth(int width)
{
  penWidth = width;
}

void PaintCanvas::setEraserMode(bool enabled)
{
  eraser = enabled;
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
  }
}

void PaintCanvas::mouseMoveEvent(QMouseEvent *event)
{
  if ((event->buttons() & Qt::LeftButton) && drawing)
  {
    drawLineTo(event->pos() / zoomFactor);
  }
}

void PaintCanvas::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton && drawing)
  {
    drawLineTo(event->pos() / zoomFactor);
    drawing = false;
  }
}

void PaintCanvas::drawLineTo(const QPoint &endPoint)
{
  QPainter painter(&canvasImage);
  QPen pen(eraser ? Qt::white : penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(pen);
  painter.drawLine(lastPoint, endPoint);
  int rad = penWidth + 2;
  update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad));
  lastPoint = endPoint;
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