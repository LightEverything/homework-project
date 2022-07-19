#ifndef NODEITEM_H
#define NODEITEM_H

#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsLineItem>
#include <QVector>
#include <QColorDialog>
#include <QDebug>
#include "sceneMode.h"

class NodeItem;

// 边类型
class EdgeItem : public	QGraphicsLineItem
{
public:
    explicit  EdgeItem(NodeItem* u, NodeItem* v, int w);
    ~EdgeItem();

    NodeItem* getFrom() {return u;}
    NodeItem* getTo()   {return v;}
    int       getWeight()		{return w;}
    void 	  removethis(NodeItem* node = nullptr);
    // 更新边上数字
    void 	  updatedgeNum()
    {
        if (edgeNum != nullptr)
            edgeNum->setPos(this->sceneBoundingRect().center());
    }
    void 	  changeColor();
protected:
    void keyPressEvent(QKeyEvent* e) override;
private:
    int                      w;
    NodeItem*  				 u;
    NodeItem* 				 v;
    QGraphicsSimpleTextItem* edgeNum = nullptr;

signals:
};

// 点类型
class NodeItem : public QGraphicsEllipseItem
{
public:
    static int  height;
    static int  width;
    // 当前模式

    explicit 	NodeItem(int x, int y, int number);
                ~NodeItem();

    int  		getX() const { return this->x();}
    int  		getY() const { return this->y();}
    static int  getHeight() { return height;}
    static int  getWidth()  { return width;}
    int  		getNumber() const { return this->number;}
    void 		addEdge(EdgeItem* edge)   { edges.push_back(edge);}
    void 		removeEdge(EdgeItem* edge) {edges.removeOne(edge);}
    void 		removethis();
    void 		changeColor();
protected:
    // 重载移动事件
    void 		mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;
    void 		keyPressEvent(QKeyEvent* e) override;
private:
    bool 					 clickAddEdges = false;
    int                 	 number;
    // 边的点数
    QVector<EdgeItem* > 	 edges;

    // 点的标号
    QGraphicsSimpleTextItem* nodeNum = nullptr;
signals:
};

#endif // NODEITEM_H
