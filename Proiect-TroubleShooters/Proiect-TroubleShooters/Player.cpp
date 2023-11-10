#include "Player.h"
#include"Piece.h"

Player::Player(const std::string& playerName, Color playerColor) :name{ playerName }, color{ playerColor }, score{ 0 } {}
std::string Player::getName() const
{
	return name;
}
const Color& Player::getColor() const
{
	return color;
}
const int& Player::getScore() const
{
	return score;
}
void Player::increaseScore()
{
	score++;
}
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




