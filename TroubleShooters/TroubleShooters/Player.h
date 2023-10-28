#pragma once
#include<string>
#include<vector>
#include"Piece.h"
class Player
{
public:
    std::string name;
    int color;
    std::vector<Piece> pieces;
    int score;
    // Constructor
    Player(const std::string& playerName, int playerColor);
    std::string getName() const;
    int getColor() const;
    int getScore() const;
    void increaseScore();

};

