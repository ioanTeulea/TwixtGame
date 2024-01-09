#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QMouseEvent>

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene(QObject* parent = nullptr);
    void showCoordinates(qreal x, qreal y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
   // void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    qreal cellSize = 50;
    qint32 boardSize = 10;
    QGraphicsEllipseItem* startEllipse;
    QList<QGraphicsLineItem*> lines;
};

#endif // GAMESCENE_H

