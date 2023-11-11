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

void Player::deleteBridge(int x1, int y1, int x2, int y2) {
	for (auto it = bridges.begin(); it != bridges.end(); ++it) {
		if ((it->getPiece1().getX() == x1 && it->getPiece1().getY() == y1 && it->getPiece2().getX() == x2 && it->getPiece2().getY() == y2) ||
			(it->getPiece1().getX() == x2 && it->getPiece1().getY() == y2 && it->getPiece2().getX() == x1 && it->getPiece2().getY() == y1)) {
			getBridges().erase(it);
			break;
		}
	}
}

bool Player::operator==(const Player& other)
{
	return color == other.color;
}

void Player::transferFirstPiece(Player& otherPlayer)
{
	if (!pieces.empty()) {
		Piece transferredPiece = pieces.front(); // Ia prima pies?
		pieces.erase(pieces.begin()); // Elimin? prima pies? din vectorul curent
		otherPlayer.getPieces().push_back(transferredPiece); // Adaug? piesa în vectorul celuilalt juc?tor
	}

}





