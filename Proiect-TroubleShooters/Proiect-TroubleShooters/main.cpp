#include <QApplication>
#include<iostream>
#include"MyWindow.h"
#include"Game.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MyWindow mainWindow;
    mainWindow.setWindowTitle("Fereastra mea");
    mainWindow.show();
    Player player1("Grig", Color::Red);
    Player player2("Cernat", Color::Black);

    uint16_t b_size;
    std::cout << "Introduceti marimea tablei de joc: ";
    std::cin >> b_size;
    while (b_size < 2)
    {
        std::cout << "Dimensiunea tablei de joc este prea mica!\n";
        std::cout << "Introduceti marimea tablei de joc: ";
        std::cin >> b_size;
    }
    Board board(b_size);

    Game Twixt(board, player1, player2);

   board.displayBoard();

   Twixt.Play();

    return app.exec();
}