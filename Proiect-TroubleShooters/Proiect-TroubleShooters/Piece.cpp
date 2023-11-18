#include "Piece.h"
#include "Player.h"
class Player;
Piece::Piece(Player* player, uint16_t coordX, uint16_t coordY) :owner{ player }, x{ coordX }, y{ coordY } {}
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

Piece::Piece(Piece&& other) noexcept :x{ std::move(other.x) }, y{ std::move(other.y) }, owner{ std::move(other.owner) }
{
    // Resetare obiect sursă
    other.owner = nullptr;
    other.x = 0;
    other.y = 0;
}
Piece& Piece::operator=(Piece&& other) noexcept
{
    //delete owner; NU trebuie sters
    x = std::move(other.x);
    y = std::move(other.y);
    owner = std::move(other.owner);
    other.owner = nullptr;
    other.x = 0;
    other.y = 0;
    return *this;
}

Player* Piece::getOwner() const
{
    return owner;
}

const uint16_t& Piece::getX() const
{
    return x;
}

const uint16_t& Piece::getY() const
{
    return y;
}

bool Piece::operator==(const Piece& other) const
{
    if (owner == other.owner) {}
    else
        return false;
    if (x != other.getX())
        return false;
    if (y != other.getY())
        return false;
    return true;
}






