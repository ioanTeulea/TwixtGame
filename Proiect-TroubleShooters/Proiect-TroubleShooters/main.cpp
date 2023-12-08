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
    QMainWindow mainWindow;

    // Adaug? CustomGraphicsScene în cadrul unui QVBoxLayout pentru a îl men?ine centrat
    QWidget* centralWidget = new QWidget(&mainWindow);
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);

    CustomGraphicsScene* customScene = new CustomGraphicsScene(&mainWindow);

    QGraphicsView* graphicsView = new QGraphicsView(customScene);
    centralLayout->addWidget(graphicsView);
    centralLayout->setAlignment(Qt::AlignCenter);

    mainWindow.setCentralWidget(centralWidget);
    mainWindow.setWindowTitle("Fereastra mea");
    mainWindow.setMinimumSize(800, 600);

    // Creeaza fereastra de dialog personalizat
    PlayerInputDialog playerDialog(&mainWindow);

    // Ad?uga?i o instan?? a clasei CustomGraphicsScene în Game
    Board board;
    Game Twixt(board);
    //Twixt.Setup();

    QObject::connect(&playerDialog, &PlayerInputDialog::acceptedWithNames, &Twixt, &Game::setPlayerNames);

    // Afiseaza ferestrele
    mainWindow.show();
    playerDialog.exec();

    // Începe jocul
    Twixt.Play();

    return app.exec();
}