#pragma once
#include <cstdint>
class Player;
class Piece
{
    Player* owner; // Owner of the piece
    uint16_t x, y; // Position on the board
public:
    // Constructor
    Piece(Player* player, uint16_t x, uint16_t y);
    ~Piece();
    Piece(const Piece& other);
    Piece& operator=(const Piece& other);
    Piece(Piece&& other) noexcept;
    Piece& operator=(Piece&& other) noexcept;
    Player* getOwner() const;
    const int& getX()const;
    const int& getY()const;
    bool operator==(const Piece& other) const;
};




