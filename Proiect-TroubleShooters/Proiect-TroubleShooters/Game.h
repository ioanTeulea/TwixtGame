#pragma once
#include"Board.h"
#include"Player.h"
#include"ConsoleDisplay.h";
#include <QObject>  

class Game : public QObject {  // Mo?tene?te QObject
    Q_OBJECT
    Player player1;
    Player player2;
    ConsoleDisplay consoleDisplay;
public:
    Board& board; // Referin?? la tabla de joc
    Player* currentPlayer; // Pointer c?tre juc?torul curent
    Game(Board& gameBoard);
    void switchPlayer();
    void switchPlayerColors();
    bool checkWin(Color color);
    bool checkGameResult();
    void forfeitGame();
    void Play();
    void Setup();
    void action_addPawn();
    void action_placeBridge();
    void action_deleteBridge();
    void display_changingBridges();
    void reset();
    friend std::ostream& operator<<(std::ostream& out, const Game& game);
private:
    void Play_menu();
    void Load_menu();
    void Restart_menu(bool& exit);
public slots:
    void setPlayerNames(const QString& namePlayer1, const QString& namePlayer2);
    void setBoardSize(const int boardSize);
};
