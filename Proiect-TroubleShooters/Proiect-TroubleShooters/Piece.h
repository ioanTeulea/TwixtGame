#pragma once
class Player;
class Piece
{
    Player* owner; // Owner of the piece
    int x, y; // Position on the board
public:
    // Constructor
    Piece(Player* player, int x, int y);
    ~Piece();
    Piece(const Piece& other);
    Piece& operator=(const Piece& other);
    Player* getOwner();
    const int& getX()const;
    const int& getY()const;
};



