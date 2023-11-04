#include "Piece.h"
#include "Player.h"
class Player;
Piece::Piece(Player* player, int coordX, int coordY) :owner{ player }, x{ coordX }, y{ coordY } {}
Piece::~Piece() {}
Piece::Piece(const Piece& other) : owner{ other.owner }, x{ other.x }, y{ other.y } {}

Piece& Piece::operator=(const Piece& other)
{
    if (this == &other) {
        return *this; // Verificare auto-asignare
    }

    // Copierea datelor
    owner = other.owner;
    x = other.x;
    y = other.y;

    return *this;
}

Player* Piece::getOwner()
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





