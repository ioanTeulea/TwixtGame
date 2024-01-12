#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QString>
#include <QGraphicsView>
#include "MyWindow.h"  // Ad?uga?i header-ul pentru clasa CustomGraphicsScene
#include "Game.h"
#include "PlayerInputDialog.h"
#include "EscapeMenuDialog.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    MyWindow myWindow;

    // Creeaz? fereastra de dialog personalizat
    PlayerInputDialog playerDialog;

    Board board;
    Game Twixt(board);

    QObject::connect(&playerDialog, &PlayerInputDialog::acceptedWithNames, &Twixt, &Game::setPlayerNames);
    QObject::connect(&playerDialog, &PlayerInputDialog::acceptedWithBoardSize, &Twixt, &Game::setBoardSize);
    QObject::connect(&playerDialog, &PlayerInputDialog::acceptedWithBoardSize, myWindow.getGameScene(), &GameScene::setBoardSize);
    QObject::connect(&playerDialog, &PlayerInputDialog::acceptedWithDifficulty, &Twixt, &Game::setDifficulty);
    QObject::connect(myWindow.getGameScene(), &GameScene::circleClicked, &Twixt, &Game::action_addPawn);
    QObject::connect(myWindow.getGameScene(), &GameScene::bridgeClicked, &Twixt, &Game::action_placeBridge);
    QObject::connect(myWindow.getGameScene(), &GameScene::deleteBridgeClicked, &Twixt, &Game::action_deleteBridge);
    QObject::connect(myWindow.getGameScene()->getNextPlayerButton(), &QPushButton::clicked, &Twixt, &Game::switchPlayer);
    QObject::connect(&Twixt, &Game::PlayersInfo, myWindow.getGameScene(), &GameScene::PlayersInfo);
    QObject::connect(myWindow.getGameScene()->getEscapeMenu(), &EscapeMenuDialog::save, &Twixt, &Game::Save);
    QObject::connect(myWindow.getGameScene()->getEscapeMenu(), &EscapeMenuDialog::savedClicked, myWindow.getGameScene(), &GameScene::saveButtonClicked);
    QObject::connect(myWindow.getGameScene(), &GameScene::isPiecePlaced, myWindow.getGameScene()->getEscapeMenu(), &EscapeMenuDialog::isPiecePlaced);
    QObject::connect(&Twixt, &Game::PlayersInfo, myWindow.getGameScene(), &GameScene::PlayersInfo);
    QObject::connect(myWindow.getMenuScene(), &MenuScene::loadGame, &Twixt, &Game::Load);
    QObject::connect(&Twixt, &Game::boardLoaded, myWindow.getGameScene(), &GameScene::onBoardLoaded);
    QObject::connect(myWindow.getMenuScene()->getPlayButton(), &QPushButton::clicked, [&playerDialog, &Twixt]() {
        if (playerDialog.exec() == QDialog::Accepted) {
            Twixt.Setup();
        }
        });
    QObject::connect(&Twixt, &Game::gameFinished, &myWindow, [&myWindow, &Twixt]() {
        QObject::disconnect(myWindow.getGameScene(), &GameScene::circleClicked, &Twixt, &Game::action_addPawn);
        QObject::disconnect(myWindow.getGameScene(), &GameScene::bridgeClicked, &Twixt, &Game::action_placeBridge);
        QObject::disconnect(myWindow.getGameScene(), &GameScene::deleteBridgeClicked, &Twixt, &Game::action_deleteBridge);
        QObject::disconnect(myWindow.getGameScene()->getNextPlayerButton(), &QPushButton::clicked, &Twixt, &Game::switchPlayer);
        // Deconecta?i orice alte semnale ?i sloturi între obiectele implicate
        });

    return app.exec();
}