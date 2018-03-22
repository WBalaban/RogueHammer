#pragma once
#include "Character.h"

// Derived from Character class, class to create player object

class Player :
	public Character
{
public:
	Player();
	~Player();
	void createPlayer(int hp, int att, int xp, int lvl);
	void setExperience(int xp);
	int getExperience() const;
	void setLevel(int lvl);
	int getLevel() const;

private:
	int experience;
	int level;
};

