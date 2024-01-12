#include "Bridge.h"




Bridge::Bridge() : m_piece1(defaultPiece()), m_piece2(defaultPiece()) {}

Bridge::Bridge(Piece piece1, Piece piece2) :m_piece1{ piece1 }, m_piece2{ piece2 } {}

Bridge& Bridge::operator=(const Bridge& other)
{
    if (this != &other)
    {
        m_piece1 = other.m_piece1;
        m_piece2 = other.m_piece2;
    }
    return *this;
}


const Piece& Bridge::getPiece1() const {
    return m_piece1;
}

const Piece& Bridge::getPiece2() const {
    return m_piece2;
}

bool Bridge::operator==(const Bridge& other) const
{
    return (m_piece1 == other.m_piece1 && m_piece2 == other.m_piece2) || (m_piece1 == other.m_piece2 && m_piece2 == other.m_piece1);
    
}

std::ostream& operator<<(std::ostream& out, const Bridge& bridge)
{
    out << bridge.m_piece1 << '\n';
    out << bridge.m_piece2;
    return out;
}

std::istream& operator>>(std::istream& in, Bridge& bridge)
{
    in >> bridge.m_piece1;
    in>> bridge.m_piece2;
    return in;
}
