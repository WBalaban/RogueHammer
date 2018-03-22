#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <fstream>
#include "GameWindow.h"



using namespace std;
int main()
{
	GameWindow StartGame("level.txt");
	StartGame.startGame();

	return 0;

}