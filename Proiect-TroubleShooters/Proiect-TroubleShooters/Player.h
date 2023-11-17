#pragma once
#include<string>
#include<vector>
#include"Piece.h"
#include"Bridge.h"

enum Color
{
    Red = 1,
    Black = 2
};
class Player
{
    std::string name;
    Color color;
    int maxPieces;
    std::vector<Piece> pieces;
    std::vector<Bridge> bridges;
    //int score;
public:
    // Constructor
    Player(const std::string& playerName, Color playerColor);
    std::string getName() const;
    const Color& getColor() const;
    //const int& getScore() const;
    //void increaseScore();
    void displayPlayerNumberPieces();
    const int& getNumberMaxPieces()const;
    const int& getNumberPieces()const;
    const int& getNumberBridges()const;
    std::vector<Piece>& getPieces();
    std::vector<Bridge>& getBridges();
    void setMaxPieces(const int& maxPieces);
    void setColor(Color c);
    bool operator==(const Player& other);
    void transferFirstPiece(Player& otherPlayer);
    void addPiece(const Piece& piece);
    void addBridge(const Bridge& bridge);
};


