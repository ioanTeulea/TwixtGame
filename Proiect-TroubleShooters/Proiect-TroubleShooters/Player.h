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
    uint32_t maxPieces;
    std::vector<Piece> pieces;
    std::vector<Bridge> bridges;
    uint32_t score=0;
public:
    // Constructor
    Player(const std::string& playerName, Color playerColor);
    std::string getName() const;
    const Color& getColor() const;
    const uint32_t& getScore() const;
    void increaseScore();
    void displayPlayerNumberPieces();
    const uint32_t& getNumberMaxPieces()const;
    const int& getNumberPieces()const;
    const int& getNumberBridges()const;
    std::vector<Piece>& getPieces();
    std::vector<Bridge>& getBridges();
    void setMaxPieces(const uint32_t& maxPieces);
    void setColor(Color c);
    bool operator==(const Player& other);
    void transferFirstPiece(Player& otherPlayer);
    void addPiece(const Piece& piece);
    void addBridge(const Bridge& bridge);
    void deletePieces();
    void deleteBridges();
};


