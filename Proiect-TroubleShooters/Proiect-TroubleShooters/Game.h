#pragma once
#include"Board.h"
#include"Player.h"
#include"ConsoleDisplay.h"
#include <QObject>  
#include <fstream>

class Game : public QObject {  // Mo?tene?te QObject
    Q_OBJECT
        Player player1;
    Player player2;
    ConsoleDisplay consoleDisplay;
    std::string difficulty;
    uint16_t percentage;
    std::pair<uint16_t, uint16_t>lastDozer{ -1,-1 };
public:
    Board& board; // Referin?? la tabla de joc
    Player* currentPlayer; // Pointer c?tre juc?torul curent
    Game(Board& gameBoard);
    void switchPlayer();
    void switchPlayerColors();
    bool checkWin(QColor color);
    bool checkGameResult();
    void forfeitGame();
    bool Play();
    void Setup();
    void display_changingBridges();
    void setGameDifficulty();
    void reset();
    std::string getDifficulty();
    void Save(const std::string& filename,bool isPiecePlaced);
    friend std::ostream& operator<<(std::ostream& out, const Game& game);
    friend std::istream& operator>>(std::istream& in, Game& game);
private:
    void Play_menu();
    void Load_menu();
    void Restart_menu(bool& exit);
signals:
    void PlayersInfo(const std::string &player1Name,QColor color1, const std::string& player2Name, QColor color2);
    void gameFinished();
    void boardLoaded(Board board,int isLastPiecePlaced);
    void mineExploded(Board board);
    void randomPiece(int X, int Y);
public slots:
    void setDifficulty(const QString& difficulty);
    void setPlayerNames(const QString& namePlayer1, const QString& namePlayer2);
    void setBoardSize(const int boardSize);
    void action_addPawn(QColor color, const  uint16_t i, const  uint16_t j, bool& isOk);
    void action_placeBridge(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2, bool& isOk);
    void action_deleteBridge(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2);
    void Load();
    void actionRandomPiece(std::pair<uint16_t, uint16_t> random_pice);
};