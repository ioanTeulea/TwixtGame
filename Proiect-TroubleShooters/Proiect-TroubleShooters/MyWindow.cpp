#include "MyWindow.h"
#include "PlayerInputDialog.h"
#include <QDebug>
#define INITIAL_WIDTH 800
#define INITIAL_HEIGHT 600
MyWindow::MyWindow()
    : QObject(nullptr)
{
    menuScene = new MenuScene(this);
    gameScene = new GameScene(this);
    menuScene->setSceneRect(0, 0, INITIAL_WIDTH, INITIAL_HEIGHT);
    // Use QMainWindow as the main window
    mainWindow = new QMainWindow();

    graphicsView = new QGraphicsView();
    graphicsView->setScene(menuScene);

    mainWindow->setCentralWidget(graphicsView);
    mainWindow->setWindowTitle("Fereastra mea");
    mainWindow->setMinimumSize(INITIAL_WIDTH, INITIAL_HEIGHT);


    connect(menuScene, &MenuScene::playClicked, this, &MyWindow::switchToGameScene);


    // Other connections for other menu actions
    // ...

    // Show the main window
    mainWindow->show();
}

void MyWindow::switchToGameScene()
{
    graphicsView->setScene(gameScene);
}
