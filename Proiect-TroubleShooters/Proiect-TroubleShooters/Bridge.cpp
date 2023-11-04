#include "Bridge.h"
#include "Piece.h"

Bridge::Bridge(Piece piece1, Piece piece2) :m_piece1(piece1), m_piece2(piece2), m_owner(piece1.getOwner()) {}

Bridge::Bridge(const Bridge& other) :m_owner(other.m_owner), m_piece1(other.m_piece1), m_piece2(other.m_piece2) {}

Bridge& Bridge::operator=(const Bridge& other)
{
    if (this == &other)
    {
        return *this;
    }
    m_owner = other.m_owner;
    m_piece1 = other.m_piece1;
    m_piece2 = other.m_piece2;
    return *this;
}

