#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QObject>
#include <QResizeEvent>
#include "MenuScene.h"
#include "GameScene.h"
#include <QGraphicsView>
#include <QMainWindow>

class MyWindow : public QObject
{
    Q_OBJECT

public:
    MyWindow();
    MenuScene* getMenuScene() const;
    GameScene* getGameScene() const;

public slots:
    void switchToGameScene();

private:
    MenuScene* menuScene;
    GameScene* gameScene;
    QGraphicsView* graphicsView;
    QMainWindow* mainWindow;
    MyWindow(const MyWindow&) = delete;
};

#endif // MYWINDOW_H
