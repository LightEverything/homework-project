#ifndef NODEGRAPHSCENE_H
#define NODEGRAPHSCENE_H

#include <QWidget>
#include <QVector>
#include <QGraphicsScene>
#include <QBrush>
#include <QSettings>
#include <nodeitem.h>
#include <QVariant>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QObject>
#include "sceneMode.h"

class NodeGraphScene : public QGraphicsScene
{
public:
    explicit NodeGraphScene(QSettings* setting, QWidget *parent = nullptr);

    void      clearAll();
    void 	  setMode(sceneMode md) { mode = md;}
    void 	  removeEdge(EdgeItem* edge){edges.removeOne(edge);}
    void 	  removeNode(NodeItem* node){nodes.removeOne(node);}
    NodeItem* addNode(int x, int y, int number);
    EdgeItem* addEdge(NodeItem* u, NodeItem* v, int w);
    EdgeItem* addEdge(int u, int v, int w);
    sceneMode getMode() { return mode;}

    // click模式下的数字
    int 	  clickNum = 1;
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void keyPressEvent(QKeyEvent* e) override;
private:
    bool               addEdgeFlag = false;
    NodeItem* 		   clickNode = nullptr;
    QSettings* 		   setting;
    QGraphicsLineItem* mouseLine = nullptr;
    sceneMode 		   mode;
    QVector<NodeItem*> nodes;
    QVector<EdgeItem*> edges;

    int  randomNode(int num) { return float(NodeItem::getHeight()) * num *
                QRandomGenerator::global()->bounded(3.0);}
    // mousePress的函数
    void exeReleaseClick(QGraphicsSceneMouseEvent* e);
    void exeReleaseMatrix(QGraphicsSceneMouseEvent* e);
    void exeReleaseAddEdge(QGraphicsSceneMouseEvent* e);
    bool isSelectedNodes();
    bool isSelectedEdges();
    bool isEdges(NodeItem* u, NodeItem* v, int num);
signals:
};

#endif // NODEGRAPHSCENE_H
