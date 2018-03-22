#include "Player.h"


Player::Player()
{

}

Player::~Player()
{
}

void Player::createPlayer(int hp, int att, int xp, int lvl)
{
	health = hp;
	attack = att;
	experience = xp;
	level = lvl;
}

void Player::setExperience(int xp)
{
	experience += xp;
	if (experience >= 500)
	{
		level += 1;
		attack += 10;
		health += 30;
		experience = 0;
	}
}
int Player::getExperience() const
{
	return experience;
}

void Player::setLevel(int lvl)
{
	level += lvl;
}
int Player::getLevel() const
{
	return level;
}
