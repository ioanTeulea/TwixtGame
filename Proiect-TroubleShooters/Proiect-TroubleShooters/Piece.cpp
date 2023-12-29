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

bool Piece::operator==(const Piece& other) const {
    return (m_color == other.m_color) && (x == other.x) && (y == other.y);
}


std::ostream& operator<<(std::ostream& out, const Piece& piece)
{
    out << piece.m_color << '\n';
    out << piece.x << " " << piece.y;
    return out;
}

std::istream& operator>>(std::istream& in, Piece& piece)
{
    uint16_t color;
    in >> color;
    piece.m_color = static_cast<Color>(color);
    in >> piece.x >> piece.y;
    return in;
}
