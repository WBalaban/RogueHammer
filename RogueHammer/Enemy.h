#pragma once
#include "Character.h"

// Derived from Character class, class to create enemies objects
class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();
	void createBoss(int hp, int att);
	int getRandomHealth();

};

