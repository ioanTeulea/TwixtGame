#pragma once
#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class MenuScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MenuScene(QObject* parent = nullptr);

signals:
    void playClicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // MENUSCENE_H

