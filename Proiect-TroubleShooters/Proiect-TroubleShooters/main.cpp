#include <QApplication>
#include <QMenuBar>
#include<QMenu>
#include <QInputDialog>
#include <QString>

#include <QVBoxLayout>
#include<iostream>
#include"MyWindow.h"
#include"Game.h"
#include "PlayerInputDialog.h"


int main(int argc, char* argv[]) {
   
    QApplication app(argc, argv);
    QMainWindow mainWindow;

    // Adauga MyWindow în cadrul unui QVBoxLayout pentru a îl mentine centrat
    QWidget* centralWidget = new QWidget(&mainWindow);
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->addWidget(new MyWindow(&mainWindow));
    centralLayout->setAlignment(Qt::AlignCenter);

    mainWindow.setCentralWidget(centralWidget);
    mainWindow.setWindowTitle("Fereastra mea");
    mainWindow.setMinimumSize(800, 600);

    // Creeaza fereastra de dialog personalizat
    PlayerInputDialog playerDialog(&mainWindow);

  
    Board board;

    // Conecteaza semnalul emis de fereastra de dialog la slot-ul din clasa Game
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