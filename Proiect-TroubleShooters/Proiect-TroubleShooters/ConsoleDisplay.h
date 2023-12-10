#pragma once
#include<iostream>
#include<string>
#include"Player.h"
#include"Board.h"
#include"Piece.h"
class ConsoleDisplay
{

public:
	ConsoleDisplay();
	void displayPlayerInfo(const Player & player) const;
	void displayBoard(Board& board)const;
	void displayMessage(const std::string& message) const;
};

