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
const uint32_t& Player::getNumberMaxPieces() const
{
	return maxPieces;
}
const uint32_t& Player::getScore() const
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

void Player::setMaxPieces(const uint32_t& maxPieces)
{
	this->maxPieces = maxPieces;
}

void Player::setColor(Color c)
{
	color = c;
}



bool Player::operator==(const Player& other)
{
	return color == other.color;
}

void Player::transferFirstPiece( Player& otherPlayer)
{
	if (!otherPlayer.pieces.empty()) {
		Piece transferredPiece = std::move(otherPlayer.pieces.front()); // Mut? prima pies?
		otherPlayer.pieces.erase(otherPlayer.pieces.begin()); // Elimin? prima pies? din vectorul curent
		getPieces().push_back(std::move(transferredPiece)); // Adaug? piesa în vectorul celui?lalt juc?tor
	}

	// Schimbarea culorii între juc?tori
	Color tempColor = color;
	color = otherPlayer.getColor();
	otherPlayer.setColor(tempColor);
} 

void Player::addPiece(const Piece& piece)
{
	pieces.push_back(piece);
}

void Player::addBridge(const Bridge& bridge)
{
	bridges.push_back(bridge);
}

void Player::deletePieces()
{
	pieces.clear();
}

void Player::deleteBridges()
{
	bridges.clear();
}





