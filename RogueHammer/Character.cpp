#include "Character.h"

Character::Character()
{

}

void Character::addHealth(int hp)
{
	health += hp;
}

void Character::subHealth(int hp)
{
	health -= hp;
}

int Character::getHealth() const
{
	return health;
}

void Character::setAttack(int att)
{
	attack += att;
}

int Character::getAttack() const
{
	return attack;
}

void Character::setPosition(int x, int y)
{
	positionX = x;
	positionY = y;
}

void Character::getPosition(int &x, int &y)
{
	x = positionX;
	y = positionY;
}

