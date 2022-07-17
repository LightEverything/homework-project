#include "nodegraphscene.h"

NodeGraphScene::NodeGraphScene(QSettings* setting, QWidget *parent)
    : QGraphicsScene {parent},
      setting(setting),
      mode(sceneMode(setting->value("mode").toInt()))
{
    this->setSceneRect(0, 0, 900, 500);
}

NodeItem* NodeGraphScene::addNode(int x, int y, int number)
{
    // 如果存在就直接返回
    for (auto item : nodes)
    {
        if (item->getNumber() == number)
            return item;
    }

    // 不存在新建
    NodeItem::height = setting->value("NodeSize").toInt();
    NodeItem::width = setting->value("NodeSize").toInt();
    NodeItem* tmpNode = new NodeItem(x, y, number);
    tmpNode->setBrush(QBrush(setting->value("NodeColor").value<QColor>()));
    this->addItem(tmpNode);

    // 将点压入图
    nodes.push_back(tmpNode);
    return tmpNode;
}

EdgeItem* NodeGraphScene::addEdge(int u, int v, int w)
{
    NodeItem* nodeu = nullptr;
    NodeItem* nodev = nullptr;

    nodeu = addNode(randomNode(u), randomNode(u), u);
    nodev = addNode(randomNode(v), randomNode(v), v);
    EdgeItem* tmpEdge = nullptr;

    if (!isEdges(nodeu, nodev, w))
        // 增加边
        tmpEdge = new EdgeItem(nodeu, nodev, w);

    if (tmpEdge)
    {
        QPen tmppen(setting->value("LineColor").value<QColor>());
        tmppen.setWidth(setting->value("LineWidth").toInt());
        // 设置样式
        tmpEdge->setPen(tmppen);
        this->addItem(tmpEdge);
        // 将边压入图
        edges.push_back(tmpEdge);
        // 将边压入点
        nodeu->addEdge(tmpEdge);
        nodev->addEdge(tmpEdge);
    }

    return tmpEdge;
}

void NodeGraphScene::clearAll()
{
    clickNum = 1;
    edges.clear();
    nodes.clear();
    this->clear();
}

void NodeGraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    switch(mode)
    {
    case click:
        exeReleaseClick(e);
        break;
    case matrix:
        exeReleaseMatrix(e);
        break;
    case addEgde:
        exeReleaseAddEdge(e);
        break;
    }

    return QGraphicsScene::mouseReleaseEvent(e);
}

void NodeGraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mode == addEgde && mouseLine)
    {
        mouseLine->setLine(clickNode->sceneBoundingRect().center().x(),
                           clickNode->sceneBoundingRect().center().y(),
                           mouseEvent->scenePos().x(),
                           mouseEvent->scenePos().y());
    }

    return QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void NodeGraphScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mode == click && isSelectedNodes())
    {
        mode = addEgde;
        clickNode = dynamic_cast<NodeItem*>(selectedItems().at(0));
        mouseLine = addLine(clickNode->sceneBoundingRect().center().x(),
                            clickNode->sceneBoundingRect().center().y(),
                            mouseEvent->scenePos().x(),
                            mouseEvent->scenePos().y(),
                            QPen(Qt::DashLine));
    }
    else if (mode == addEgde)
    {
        mode = click;
        clickNode = nullptr;
        removeItem(mouseLine);
        mouseLine = nullptr;
    }

    return QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void NodeGraphScene::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Backspace:
        if (isSelectedNodes())
        {
            auto item = this->selectedItems().at(0);
            nodes.removeOne(dynamic_cast<NodeItem*>((item)));
        }
        if (isSelectedEdges())
        {
            auto item = this->selectedItems().at(0);
            edges.removeOne(dynamic_cast<EdgeItem*>(item));
        }
        break;
    }
    return QGraphicsScene::keyPressEvent(e);
}

void NodeGraphScene::exeReleaseClick(QGraphicsSceneMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        // 如果是左键并且没有选中点
        if (!isSelectedNodes() && !isSelectedEdges())
            addNode(e->scenePos().rx(), e->scenePos().ry(), clickNum++);
    }
}

void NodeGraphScene::exeReleaseMatrix(QGraphicsSceneMouseEvent* e)
{

}

void NodeGraphScene::exeReleaseAddEdge(QGraphicsSceneMouseEvent *e)
{
    // 如果选中了点,并且不是同一个点
    if (isSelectedNodes() &&
        clickNode != dynamic_cast<NodeItem*>(selectedItems().at(0)))
    {
        addEdge(clickNode, dynamic_cast<NodeItem*>(selectedItems().at(0)), 0);
        removeItem(mouseLine);
        clickNode = nullptr;
        mouseLine = nullptr;
        mode = click;
        return ;
    }

    // 如果是右键
    if (!isSelectedNodes() || e->button() == Qt::RightButton)
    {
        removeItem(mouseLine);
        clickNode = nullptr;
        mouseLine = nullptr;
        mode = click;
        return ;
    }
}

// 是否存在被选中的点
bool NodeGraphScene::isSelectedNodes()
{
    // 判断是否有点被选中
    if (selectedItems().size() != 0 &&
        typeid (*selectedItems().at(0)) == typeid (NodeItem))

        return true;
    else
        return false;
}

bool NodeGraphScene::isSelectedEdges()
{
    // 判断是否有边被选中
    if (selectedItems().size() != 0 &&
        typeid (*selectedItems().at(0)) == typeid (EdgeItem))

        return true;
    else
        return false;
}

// 判断是否存在某一条边
bool NodeGraphScene::isEdges(NodeItem *u, NodeItem *v, int num)
{
    for (auto item : edges)
    {
        if (item->getFrom() == u &&
            item->getTo() == v &&
            item->getWeight() == num)
            return true;
    }

    return false;
}


EdgeItem* NodeGraphScene::addEdge(NodeItem* u, NodeItem* v, int w)
{
    EdgeItem* tmpEdge = nullptr;

    if (!isEdges(u, v, w))
        // 增加边
        tmpEdge = new EdgeItem(u, v, w);

    // 如果不存在这一条边
    if (tmpEdge)
    {
        QPen tmppen(setting->value("LineColor").value<QColor>());
        tmppen.setWidth(setting->value("LineWidth").toInt());
        // 设置样式
        tmpEdge->setPen(tmppen);
        this->addItem(tmpEdge);
        // 将边压入图
        edges.push_back(tmpEdge);
        // 将边压入点
        u->addEdge(tmpEdge);
        v->addEdge(tmpEdge);
    }

    return tmpEdge;
}
