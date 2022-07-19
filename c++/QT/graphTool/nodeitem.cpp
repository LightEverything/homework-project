#include "nodeitem.h"

// 静态变量width和height
int NodeItem::width = 25;
int NodeItem::height= 25;

NodeItem::NodeItem(int x, int y, int num)
    : QGraphicsEllipseItem {qreal(x), qreal(y), qreal(height), qreal(width)},
      number(num)
{
    // 设置NodeItem属性
    this->setRect(x, y, height, width);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setZValue(10);

    // 设置数字位置和属性
    nodeNum = new QGraphicsSimpleTextItem(QString().setNum(number), this);
    nodeNum->setPos(this->sceneBoundingRect().center().x() - height / 6,
                    this->sceneBoundingRect().center().y() - height / 3);
}

NodeItem::~NodeItem()
{
    delete nodeNum;
}

// 重载移动事件
void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    // 更新线的位置
    for (auto item : qAsConst(edges))
    {
        auto u = item->getFrom();
        auto v = item->getTo();
        int x1 = u->sceneBoundingRect().center().rx(); int y1 = u->sceneBoundingRect().center().ry();
        int x2 = v->sceneBoundingRect().center().rx(); int y2 = v->sceneBoundingRect().center().ry();
        item->setLine(x1, y1, x2, y2);

        // 更新数字的位置

        item->updatedgeNum();
    }
    // 移动处理
    return QGraphicsEllipseItem::mouseMoveEvent(e);
}

void NodeItem::keyPressEvent(QKeyEvent* e)
{
    switch(e->key())
    {
    case Qt::Key_Backspace:
        removethis();
        break;
    case Qt::Key_C:
        changeColor();
        break;
    }
}

void NodeItem::removethis()
{
    // 删除边(这个地方莫名其妙不能使用for_each
    for (auto item : qAsConst(edges))
    {
        auto node = this == item->getFrom() ? item->getTo(): item->getFrom();
        item->removethis(node);
    }

    // 删除本身
    scene()->removeItem(this);
}


void NodeItem::changeColor()
{
    auto color = QColorDialog::getColor(this->brush().color());
    if (color.isValid())
    {
        auto brush = this->brush();
        brush.setColor(color);
        this->setBrush(brush);
    }
}

// EdgeItem类
EdgeItem::EdgeItem(NodeItem* u, NodeItem* v, int w)
    : QGraphicsLineItem(),
      w(w),
      u(u),
      v(v)
{

    // 初始化edge
    int x1 = u->sceneBoundingRect().center().rx();
    int y1 = u->sceneBoundingRect().center().ry();
    int x2 = v->sceneBoundingRect().center().rx();
    int y2 = v->sceneBoundingRect().center().ry();
    this->setLine(x1, y1, x2, y2);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    // 设置数字位置
    if (w > 0)
    {
        edgeNum = new QGraphicsSimpleTextItem(QString().setNum(w), this);
        edgeNum->setPos(this->sceneBoundingRect().center());
    }
}

void EdgeItem::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Backspace:
        removethis();
        break;
    case Qt::Key_C:
        changeColor();
        break;
    }

    return QGraphicsItem::keyPressEvent(e);
}

EdgeItem::~EdgeItem()
{
    if (edgeNum != nullptr)
        delete edgeNum;
}

void EdgeItem::removethis(NodeItem* node)
{
    if (node == nullptr)
    {
        this->u->removeEdge(this);
        this->v->removeEdge(this);
    }
    else
        node->removeEdge(this);

    scene()->removeItem(this);
}

void EdgeItem::changeColor()
{
    auto color = QColorDialog::getColor(this->pen().color());
    if (color.isValid())
    {
        auto pen = this->pen();
        pen.setColor(color);
        this->setPen(pen);
    }
}
