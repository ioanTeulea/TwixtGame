#pragma once
#include"Player.h"
class Piece
{
public:
    Player* owner; // Owner of the piece
    bool placed; // Is the piece placed on the board
    int x, y; // Position on the board
    // Constructor
    Piece(Player* player);
    ~Piece();
    Piece(const Piece& other);
    Piece& operator=(const Piece& other);
};

