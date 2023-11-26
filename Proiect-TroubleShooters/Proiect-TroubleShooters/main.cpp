#include <QApplication>
#include <QMenuBar>
#include<QMenu>
#include <QVBoxLayout>
#include<iostream>
#include"MyWindow.h"
#include"Game.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;

    //Adaug? MyWindow în cadrul unui QVBoxLayout pentru a il  men?ine centrat
    QWidget* centralWidget = new QWidget(&mainWindow);
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->addWidget(new MyWindow(&mainWindow));
    centralLayout->setAlignment(Qt::AlignCenter);

    mainWindow.setCentralWidget(centralWidget);
    mainWindow.setWindowTitle("Fereastra mea");
    mainWindow.setMinimumSize(800, 600);
    mainWindow.show();


    // Player player1("Grig", Color::Red);
    // Player player2("Cernat", Color::Black);

    // Game Twixt(board, player1, player2);
    // board.displayBoard();

    //// // Începe jocul
    // Twixt.Play();

    return app.exec();
}
