#pragma once

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QColor>

class PaintCanvas : public QWidget
{
  Q_OBJECT

public:
  PaintCanvas(QWidget *parent = nullptr);
  void setPenColor(const QColor &color);
  void setPenWidth(int width);
  void setEraserMode(bool enabled);
  void zoomIn();
  void zoomOut();

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
  int penWidth = 2;
  bool drawing = false;
  bool eraser = false;
  double zoomFactor = 1.0;

  void drawLineTo(const QPoint &endPoint);
};