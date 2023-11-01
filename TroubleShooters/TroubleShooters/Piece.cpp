#include "Piece.h"

Piece::Piece(Player* player) :owner{ player }, placed{ false }, x{ 0 }, y{ 0 } {}
Piece::~Piece(){}
Piece::Piece(const Piece& other) : owner{ other.owner }, placed{ other.placed }, x{ other.x }, y{ other.y } {}

Piece& Piece::operator=(const Piece& other)
{
    if (this == &other) {
        return *this; // Verificare auto-asignare
    }

    // Copierea datelor
    owner = other.owner;
    placed = other.placed;
    x = other.x;
    y = other.y;

    return *this;
}

const Player* Piece::getOwner() const
{
    return owner;
}

const int& Piece::getX() const
{
    return x;
}

const int& Piece::getY() const
{
    return y;
}

const bool& Piece::getPlaced() const
{
    return placed;
}




