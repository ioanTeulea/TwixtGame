#pragma once
class Player;
class Piece
{
    Player* owner; // Owner of the piece
    bool placed; // Is the piece placed on the board
    int x, y; // Position on the board
public:
    // Constructor
    Piece(Player* player);
    ~Piece();
    Piece(const Piece& other);
    Piece& operator=(const Piece& other);
    const Player* getOwner() const;
    const int& getX()const;
    const int& getY()const;
    const bool& getPlaced() const;
};

