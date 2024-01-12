#include "Piece.h"
#include "Player.h"
Piece::Piece(QColor color, uint16_t coordX, uint16_t coordY) :m_color{ color }, x{ coordX }, y{ coordY } {}

QColor Piece::getColor() const
{
    return m_color;
}

void Piece::setColor(QColor color)
{
    m_color = color;
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
    out << piece.m_color.name().toStdString() << '\n';
    out << piece.x << " " << piece.y;
    return out;
}

std::istream& operator>>(std::istream& in, Piece& piece)
{
    std::string colorStr;
    in >> colorStr;
    QColor Color(QString::fromStdString(colorStr));
    piece.setColor(Color);
    in >> piece.x >> piece.y;
    return in;
}