#pragma once
#include "Piece.h"
//#include "Player.h"

//class Player;
class Bridge
{
	//Player* m_owner;
	Piece m_piece1, m_piece2;
public:
	Bridge(Piece piece1, Piece piece2);
	Bridge(const Bridge& other);
	Bridge& operator=(const Bridge& other);
	bool sortBridgesComparator(const Bridge& other)const;
	const Piece& getPiece1() const;
	const Piece& getPiece2() const;
};

