#include "Bridge.h"


Bridge::Bridge(Piece& piece1, Piece& piece2) :m_piece1{ piece1 }, m_piece2{ piece2 } {}

Bridge& Bridge::operator=(const Bridge& other)
{
    m_piece1 = other.m_piece1;
    m_piece2 = other.m_piece2;
    return *this;
}


const Piece& Bridge::getPiece1() const {
    return m_piece1;
}

const Piece& Bridge::getPiece2() const {
    return m_piece2;
}

