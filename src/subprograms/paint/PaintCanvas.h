#pragma once

#include "DrawMode.h"

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QTimer>

class PaintCanvas : public QWidget
{
  Q_OBJECT

public:
  PaintCanvas(QWidget *parent = nullptr);
  void setPenColor(const QColor &color);
  void setPenWidth(int width);
  void setDrawMode(DrawMode mode);
  void zoomIn();
  void zoomOut();
  void clearCanvas();
  int getPenWidth() const { return penWidth; }

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  QSize sizeHint() const override;

private:
  QImage canvasImage;
  QPoint lastPoint;
  QColor penColor = Qt::black;
  DrawMode currentDrawMode = DrawMode::Brush;
  int penWidth = 10;
  bool drawing = false;
  double zoomFactor = 1.0;

  QTimer* sprayTimer = nullptr;
  QPoint sprayPoint;

  void drawLineTo(const QPoint &endPoint);
  void sprayAt(const QPoint &point);
};