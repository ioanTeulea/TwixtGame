#include "Player.h"
#include"Piece.h"
Player::Player(const std::string& playerName, Color playerColor) :name{ playerName }, color{ playerColor } {}
std::string Player::getName() const
{
	return name;
}
void Player::setName(const std::string& newName)
{
	name = newName;
}
const Color& Player::getColor() const
{
	return color;
}
const uint16_t& Player::getRemainingPieces() const
{
	return remainingPieces;
}
const uint16_t& Player::getRemainingBridges() const
{
	return remainingBridges;
}

void Player::setRemainingPieces(uint16_t pieces)
{
	remainingPieces = pieces;
}

void Player::setRemainingBridges(uint16_t bridges)
{
	remainingBridges = bridges;
}

void Player::setColor(Color c)
{
	color = c;
}

void Player::setInitialValues(uint16_t max)
{
	remainingPieces = max;
	remainingBridges = max;
}



bool Player::operator==(const Player& other)
{
	return color == other.color;
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
	out << player.name << '\n';
	out << player.color << '\n';
	out << player.remainingPieces << '\n';
	out << player.remainingBridges << '\n';
	out << player.advantage;
	return out;
}

std::istream& operator>>(std::istream& in, Player& player)
{
	in >> player.name;
	uint16_t c;
	in >> c;
	player.color = static_cast<Color>(c);
	in >> player.remainingPieces;
	in >> player.remainingBridges;
	in >> player.advantage;
	return in;
}
