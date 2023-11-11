#include "Player.h"
#include"Piece.h"
#include<iostream>
Player::Player(const std::string& playerName, Color playerColor) :name{ playerName }, color{ playerColor } {}
std::string Player::getName() const
{
	return name;
}
const Color& Player::getColor() const
{
	return color;
}
void Player::displayPlayerNumberPieces()
{
	std::cout << "Remaining pieces for " << getName() << '\n';
	std::cout << "Pieces: " << maxPieces - getNumberPieces() << '\n';
	std::cout << "Bridges: " << maxPieces - getNumberBridges() << '\n';
}
const int& Player::getNumberMaxPieces() const
{
	return maxPieces;
}
//const int& Player::getScore() const
//{
//	return score;
//}
//void Player::increaseScore()
//{
//	score++;
//}
const int& Player::getNumberPieces() const
{
	return pieces.size();
}
const int& Player::getNumberBridges() const
{
	return bridges.size();
}
std::vector<Piece>& Player::getPieces()
{
	return pieces;
}
std::vector<Bridge>& Player::getBridges()
{
	return bridges;
}

void Player::setMaxPieces(const int& maxPieces)
{
	this->maxPieces = maxPieces;
}





