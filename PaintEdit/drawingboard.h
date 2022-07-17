#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPaintEvent>
#include <QImage>
#include <QResizeEvent>
#include <QColor>
#include <QString>
#include <QSize>

class DrawingBoard : public QWidget
{
    Q_OBJECT
public:
    enum penmode{eraser, write};
    explicit DrawingBoard(QWidget *parent = nullptr);
    virtual ~DrawingBoard();
    void setFilledBackground(const QColor& c);
    void setBrush(const QBrush& bs);
    void setPen(const QPen& p);
    void setPenMode(const penmode mode);
    bool loadImage(const QString& file);
    void saveImage(const QString& file) const;
    bool isErase() const;
    void clear();
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);
private:
    void drawLine(QMouseEvent* event);
    void resizeImage(const QSize& size);

    QImage* image = nullptr;	// 背景画布
    QPen* linePen = nullptr;
    QPen* eraserPen = nullptr;
    QBrush* brush = nullptr;
    QColor filledBackground; 	// 背景填充色
    QPoint lastPoint ;
    bool isDrawing = false; // 画线状态
    bool isEraser = false;
signals:
};

#endif // DRAWINGBOARD_H
