#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QString>
#include <QGraphicsView>
#include "MyWindow.h"  // Ad?uga?i header-ul pentru clasa CustomGraphicsScene
#include "Game.h"
#include "PlayerInputDialog.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    MyWindow myWindow;

    // Creeaz? fereastra de dialog personalizat
    PlayerInputDialog playerDialog;


    
    Board board;
    Game Twixt(board);
   // Twixt.Setup();

    QObject::connect(&playerDialog, &PlayerInputDialog::acceptedWithNames, &Twixt, &Game::setPlayerNames);
    QObject::connect(&playerDialog, &PlayerInputDialog::acceptedWithBoardSize, &Twixt, &Game::setBoardSize);  
    playerDialog.exec();
    
    // Începe jocul
    Twixt.Play();

    return app.exec();
}