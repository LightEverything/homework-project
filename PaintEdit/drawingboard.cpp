#include "drawingboard.h"

DrawingBoard::DrawingBoard(QWidget *parent) :
    QWidget(parent),
    image(new QImage()),
    linePen(new QPen(Qt::black)),
    eraserPen(new QPen(Qt::white)),
    brush(new QBrush(Qt::black))
{
    linePen->setWidth(2);
    eraserPen->setWidth(10);

    filledBackground = Qt::white;
}

void DrawingBoard::drawLine(QMouseEvent* event)
{
    QPainter painter(image);
    // 设置画笔
    if (isEraser)
        painter.setPen(*eraserPen);
    else
    {
        painter.setBrush(*brush);
        painter.setPen(*linePen);
    }

    painter.drawLine(lastPoint, event->pos());
    update();
    // 最后的位置更新
    lastPoint = event->pos();
    return ;
}

void DrawingBoard::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton )&&isDrawing)
        drawLine(event);

    return QWidget::mouseMoveEvent(event);
}

void DrawingBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);

    return QWidget::paintEvent(event);
}

void DrawingBoard::mousePressEvent(QMouseEvent *event)
{
    // 设置初始锚点
    lastPoint = event->pos();

    if (event->button() == Qt::LeftButton)
    {
        drawLine(event);
        isDrawing = true;
    }

    return QWidget::mousePressEvent(event);
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() && event->button() == Qt::LeftButton && isDrawing)
    {
        drawLine(event);
        isDrawing = false;
    }

    return QWidget::mouseReleaseEvent(event);
}

void DrawingBoard::resizeEvent(QResizeEvent *event)
{
    if (event->size() != image->size())
        resizeImage(event->size());

    return QWidget::resizeEvent(event);
}

DrawingBoard::~DrawingBoard()
{
    delete image;
    delete linePen;
    delete eraserPen;
    delete brush;
}

void DrawingBoard::setBrush(const QBrush& bs)
{
    delete this->brush;
    brush = new QBrush(bs);
}

void DrawingBoard::setPen(const QPen& p)
{
        delete this->linePen;
        linePen = new QPen(p);
}

bool DrawingBoard::loadImage(const QString& file)
{
   QImage* tempImage = new QImage(file);
   this->resize(tempImage->width(), tempImage->height());
   delete image;
   image = tempImage;

   return true;
}

void DrawingBoard::resizeImage(const QSize &size)
{
    QImage* tempImage = new QImage(size, QImage::Format_RGB32);
    tempImage->fill(filledBackground);
    QPainter p(tempImage);
    p.drawImage(0, 0, *image);
    delete image;
    image = tempImage;
    return ;
}

void DrawingBoard::setPenMode(penmode mode)
{
    if (mode == eraser)
        isEraser = true;
    else
        isEraser = false;

    return ;
}

void DrawingBoard::setFilledBackground(const QColor& c)
{
    filledBackground = c;

    QImage* tempImage = new QImage(this->size(), QImage::Format_RGB32);
    tempImage->fill(filledBackground);
    QPainter p(tempImage);
    p.drawImage(0, 0, *image);
    delete image;
    image = tempImage;

    return ;
}

void DrawingBoard::saveImage(const QString &file) const
{
    image->save(file);
}

bool DrawingBoard::isErase() const
{
    return isEraser;
}

void DrawingBoard::clear()
{
    QImage* tempImage = new QImage(this->size(), QImage::Format_RGB32);
    tempImage->fill(filledBackground);
    delete image;
    image = tempImage;
    this->update();
}
