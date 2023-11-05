#pragma once
#include"Board.h"
#include"Player.h"
#include<iostream>
class Game
{
public:
    Board& board; // Referin?? la tabla de joc
    Player& player1; // Referin?? la primul juc?tor
    Player& player2; // Referin?? la al doilea juc?tor
    Player* currentPlayer; // Pointer c?tre juc?torul curent
    int piece_no;
    Game(Board& gameBoard, Player& p1, Player& p2);
    void switchPLayer();
    bool checkWinCondition(Player player);
    bool isConnected(int x, int y, Color playerColor, std::vector<std::vector<bool>>& visited);
    bool checkGameResult(Game game);
    void Play();
};


