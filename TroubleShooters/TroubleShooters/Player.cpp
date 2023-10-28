#include "Player.h"

Player::Player(const std::string& playerName, int playerColor):name(playerName), color(playerColor), score(0) {}
std::string Player::getName() const
{
	return name;
}
int Player::getColor() const
{
	return color;
}
int Player::getScore() const
{
	return score;
}
void Player::increaseScore()
{
	score++;
}
;


