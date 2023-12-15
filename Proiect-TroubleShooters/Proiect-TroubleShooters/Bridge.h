#pragma once
#include "Piece.h"

class Bridge
{
    Piece& m_piece1; 
    Piece& m_piece2;
public:
	Bridge(Piece& piece1,Piece& piece2);
	Bridge(const Bridge& other)=default;
	Bridge& operator=(const Bridge& other);
	Bridge(Bridge&& other)=default;
	Bridge& operator=(Bridge&& other)=default;
	const Piece& getPiece1() const;
	const Piece& getPiece2() const;
	bool operator==(const Bridge& other) const;
	friend std::ostream& operator<<(std::ostream& out, const Bridge& bridge);
};

