#pragma once
class Character
{
public:
	Character();
	void setPosition(int x, int y);
	void getPosition(int &x, int &y);
	void addHealth(int hp);
	void subHealth(int hp);
	int getHealth() const;
	void setAttack(int att);
	int getAttack() const;

protected:
	int health;
	int attack;
	int positionX;
	int positionY;
};

