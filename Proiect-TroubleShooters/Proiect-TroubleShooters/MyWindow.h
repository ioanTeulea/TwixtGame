#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QObject>
#include "MenuScene.h"
#include "GameScene.h"
#include <QGraphicsView>

class MyWindow : public QObject
{
    Q_OBJECT

public:
    MyWindow();

public slots:
    void switchToGameScene();

private:
    MenuScene* menuScene;
    GameScene* gameScene;
    QGraphicsView* graphicsView;
};

#endif // MYWINDOW_H