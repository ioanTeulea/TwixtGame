#include "Piece.h"
#include "Player.h"
Piece::Piece(Color color, uint16_t coordX, uint16_t coordY) :m_color{ color }, x{ coordX }, y{ coordY } {}

Color Piece::getColor() const
{
    return m_color;
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
    if (m_color != other.m_color)
        return false;
    if (x != other.getX())
        return false;
    if (y != other.getY())
        return false;
    return true;
}

std::ostream& operator<<(std::ostream& out, const Piece& piece)
{
    out << piece.m_color << '\n';
    out << piece.x << " " << piece.y;
    return out;
}
