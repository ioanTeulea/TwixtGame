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

    int b_size;
    std::cout << "Introduceti marimea tablei de joc: ";
    std::cin >> b_size;

    Board board(b_size);

    Game Twixt(board, player1, player2);
    board.placePiece(player1, 3, 0);
    player1.transferFirstPiece(player2);
    if (player1.getPieces().empty())
        std::cout << "Da";



   //board.displayBoard();

   //Twixt.Play();

    return app.exec();
}