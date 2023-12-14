#include "MyWindow.h"
#include "PlayerInputDialog.h"
#include <QMainWindow>
MyWindow::MyWindow()
    : QObject(nullptr)
{
    menuScene = new MenuScene(this);
    gameScene = new GameScene(this);

    // Folosim QMainWindow ca o fereastr? principal?
    QMainWindow* mainWindow = new QMainWindow();

    graphicsView = new QGraphicsView();
    graphicsView->setScene(menuScene);

    mainWindow->setCentralWidget(graphicsView);
    mainWindow->setWindowTitle("Fereastra mea");
    mainWindow->setMinimumSize(800, 600);

    connect(menuScene, &MenuScene::playClicked, this, &MyWindow::switchToGameScene);

    // Alte conexiuni pentru alte ac?iuni din meniu
    // ...

    // Afi??m fereastra principal?
    mainWindow->show();
}

void MyWindow::switchToGameScene()
{
    graphicsView->setScene(gameScene);
}