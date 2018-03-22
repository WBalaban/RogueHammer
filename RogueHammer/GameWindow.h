#pragma once
#include "Level.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>


class GameWindow
{
	Level level;
	Player player;
	Enemy goblin;
	Enemy boss;

public:
	void startMessage();
	GameWindow(std::string level_number);
	~GameWindow();
	void statsBar(Player &player);
	void startGame();
	void clearScreen(HANDLE hConsole);

};

