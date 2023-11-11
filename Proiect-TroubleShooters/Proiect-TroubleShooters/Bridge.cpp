#include "Bridge.h"


Bridge::Bridge(Piece piece1, Piece piece2) :m_piece1(piece1), m_piece2(piece2) {}

Bridge::Bridge(const Bridge& other) : m_piece1(other.m_piece1), m_piece2(other.m_piece2) {}

Bridge& Bridge::operator=(const Bridge& other)
{
    if (this == &other)
    {
        return *this;
    }
    //m_owner = other.m_owner;
    m_piece1 = other.m_piece1;
    m_piece2 = other.m_piece2;
    return *this;
}

bool Bridge::sortBridgesComparator(const Bridge& other)const 
{
    if (this->getPiece1().getX() != other.getPiece1().getX()) {
        return this->getPiece1().getX() < other.getPiece1().getX();
    }
    else if (this->getPiece1().getY() != other.getPiece1().getY()) {
        return this->getPiece1().getY() < other.getPiece1().getY();
    }
    else if (this->getPiece2().getX() != other.getPiece2().getX()) {
        return this->getPiece2().getX() < other.getPiece2().getX();
    }
    else {
        return this->getPiece2().getY() < other.getPiece2().getY();
    }

}

const Piece& Bridge::getPiece1() const {
    return m_piece1;
}

const Piece& Bridge::getPiece2() const {
    return m_piece2;
}

