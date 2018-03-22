#pragma once
#include "Player.h"
#include "Enemy.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>


class Level
{
	std::vector <std::string> currentLevel;
	std::string warningMessage = " ";
	Enemy wildfire;
	int additionalHp = 1;

public:
	Level();
	~Level();
	void load(std::string levelNumber, Player &player);
	void show();
	void messageBox();
	void movePlayer(char input, Player &playee, Enemy &enemy, Enemy &boss);
	char getElemenentAtPosition(int x, int y);
	bool canYouMove(int x, int y, Player &player, Enemy &enemy, Enemy &boss);
	bool fight(Player &player, Enemy &enemy);
	void wildfireRandomMove();
	bool wildfireMoveCheck(int x, int y);
	void deathMessage();
	void winMessage();
	void gamble(Player &player);
};

