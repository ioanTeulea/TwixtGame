#include "MyWindow.h"
#include "PlayerInputDialog.h"
#include "Game.h"
#include <QDebug>
#define INITIAL_WIDTH 900
#define INITIAL_HEIGHT 700
MyWindow::MyWindow()
    : QObject(nullptr)
{
    menuScene = new MenuScene(this, INITIAL_WIDTH, INITIAL_HEIGHT);
    gameScene = new GameScene(this, INITIAL_WIDTH, INITIAL_HEIGHT);
    menuScene->setSceneRect(0, 0, INITIAL_WIDTH, INITIAL_HEIGHT);
    // Use QMainWindow as the main window
    mainWindow = new QMainWindow();

    graphicsView = new QGraphicsView();
    graphicsView->setScene(menuScene);

    mainWindow->setCentralWidget(graphicsView);
    mainWindow->setWindowTitle("Fereastra mea");
    mainWindow->setMinimumSize(INITIAL_WIDTH, INITIAL_HEIGHT);


    connect(menuScene, &MenuScene::playClicked, this, &MyWindow::switchToGameScene);
    connect(menuScene, &MenuScene::playClicked, gameScene, &GameScene::drawGameBoard);
    connect(menuScene, &MenuScene::loadClicked, this, &MyWindow::switchToGameScene);

    // Show the main window
    mainWindow->show();
}
// Implementarea getterilor
MenuScene* MyWindow::getMenuScene() const
{
    return menuScene;
}

GameScene* MyWindow::getGameScene() const
{
    return gameScene;
}


void MyWindow::switchToGameScene()
{
    graphicsView->setScene(gameScene);
}
