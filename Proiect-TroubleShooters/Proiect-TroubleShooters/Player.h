#pragma once
#include<string>
#include<vector>
#include"Piece.h"
enum Color
{
    Red = 0,
    Black = 1
};
class Player
{
    std::string name;
    Color color;
    std::vector<Piece> pieces;
    int score;
public:
    // Constructor
    Player(const std::string& playerName, Color playerColor);
    std::string getName() const;
    const Color& getColor() const;
    const int& getScore() const;
    void increaseScore();
    const int& getNumberPieces()const;
    const std::vector<Piece>& getPieces() const;
};


