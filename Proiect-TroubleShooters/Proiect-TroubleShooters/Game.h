#pragma once
#include"Board.h"
#include"Player.h"
#include<iostream>
#include <QObject>  

class Game : public QObject {  // Mo?tene?te QObject
    Q_OBJECT
    Player player1;
    Player player2;
public:
    Board& board; // Referin?? la tabla de joc
    Player* currentPlayer; // Pointer c?tre juc?torul curent
    Game(Board& gameBoard);
    void switchPlayer();
    bool checkWinCondition(Player player);
    bool isConnected(Player player);
    bool checkGameResult();
    void forfeitGame();
    void displayScore() const;
    void Play();
    void sortBridges();
    void Setup();
    void action_addPawn();
    void action_deleteBridge();
    void reset();
public slots:
    void setPlayerNames(const QString& namePlayer1, const QString& namePlayer2);
};
