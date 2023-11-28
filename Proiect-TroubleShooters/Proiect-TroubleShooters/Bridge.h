#pragma once
#include "Piece.h"
//#include "Player.h"

//class Player;
class Bridge
{
	//Player* m_owner;
	Piece& m_piece1; 
	Piece& m_piece2;
public:
	Bridge(Piece& piece1, Piece& piece2);
	Bridge(const Bridge& other)=default;
	Bridge& operator=(const Bridge& other)=default;
	Bridge(Bridge&& other)=default;
	Bridge& operator=(Bridge&& other)=default;
	const Piece& getPiece1() const;
	const Piece& getPiece2() const;
};

