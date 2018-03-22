#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

// Loading game map from text file
void Level::load(std::string levelNumber, Player &player)
{
	std::ifstream map;
	map.open(levelNumber);
	if (map.fail())
	{
		std::cout << "Error! Cannot open level file.\n";
		system("PAUSE");
		exit(1);
	}

	std::string line;

	while (getline(map, line))
	{
		currentLevel.push_back(line);
	}
	map.close();


	for (unsigned int i = 0; i < currentLevel.size(); i++)
		for (unsigned int j = 0; j < currentLevel[i].size(); j++)
		{
			if (currentLevel[i][j] == '@')
			{
				player.setPosition(i, j);
			}
			else if (currentLevel[i][j] == '!')
			{
				wildfire.setPosition(i, j);
			}
		}
}

// Show current level
void Level::show()
{
	for (std::vector<std::string>::iterator it = currentLevel.begin(); it != currentLevel.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

// Messagebox that shows game alerts
void Level::messageBox()
{
	std::cout << warningMessage << std::endl << std::endl;
	warningMessage = " ";
}

//Method to move player
void Level::movePlayer(char input, Player &player, Enemy &enemy, Enemy &boss)
{
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);


	switch (input)
	{
	case 'W':
	case 'w': if (canYouMove(playerX - 1, playerY, player, enemy, boss))
	{
		player.setPosition(playerX - 1, playerY);
		currentLevel[playerX][playerY] = '.';
		currentLevel[playerX - 1][playerY] = '@';
		break;
	}
			  break;
	case 'S':
	case 's': if (canYouMove(playerX + 1, playerY, player, enemy, boss))
	{
		player.setPosition(playerX + 1, playerY);
		currentLevel[playerX][playerY] = '.';
		currentLevel[playerX + 1][playerY] = '@';
		break;
	}
			  break;
	case 'A':
	case 'a': if (canYouMove(playerX, playerY - 1, player, enemy, boss))
	{
		player.setPosition(playerX, playerY - 1);
		currentLevel[playerX][playerY] = '.';
		currentLevel[playerX][playerY - 1] = '@';
		break;
	}
			  break;

	case 'D':
	case 'd': if (canYouMove(playerX, playerY + 1, player, enemy, boss))
	{
		player.setPosition(playerX, playerY + 1);
		currentLevel[playerX][playerY] = '.';
		currentLevel[playerX][playerY + 1] = '@';
		break;
	}
			  break;
	case 'Q':
	case 'q':
		deathMessage();
		system("PAUSE");
		exit(1);
		break;
	}

}

char Level::getElemenentAtPosition(int x, int y)
{
	return currentLevel[x][y];
}

// Check if player can move and what will happen if player moves
bool Level::canYouMove(int x, int y, Player &player, Enemy &enemy, Enemy &boss)
{
	wildfireRandomMove();
	switch (getElemenentAtPosition(x, y))
	{
	case '#':
		warningMessage = "The wall is very cold and covered with slime.";
		return false;
		break;
	case '?':
		gamble(player);
		return true;
		break;
	case 'G':
		warningMessage = "You attack goblin!\n";
		return fight(player, enemy);
		break;
	case '+':
		player.addHealth(15);
		return true;
		break;
	case 'K':
		warningMessage = "You attack goblin king!\n";
		return fight(player, boss);
		player.setExperience(300);
		break;
	case '!':
		deathMessage();
		system("PAUSE");
		exit(1);
		break;
	case 'P' :
		winMessage();
		system("PAUSE");
		exit(1);
		break;
	default: return true;
	}
}

bool Level::fight(Player &player, Enemy &enemy)
{
	enemy.subHealth(player.getAttack());
	if (enemy.getHealth() <= 0)
	{
		warningMessage = "Congratulations warrior! You've killed the heretic!";
		enemy.addHealth((enemy.getRandomHealth()+ additionalHp));
		additionalHp++;
		player.setExperience(100);
		return true;
	}
		
	player.subHealth(enemy.getAttack());

	if (player.getHealth() <= 0)
	{
		deathMessage();
		system("PAUSE");
		exit(1);
	}
	warningMessage.append("Enemy health at: ");
	warningMessage.append(std::to_string(enemy.getHealth()));

	return false;
}
// Method for random movement of wildfire '!' which can cause instant player death
void Level::wildfireRandomMove()
{
	int whereToMove;
	int positionX;
	int positionY;

	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> mover(0, 4); // random number in range [0, 4] C++ 11
	whereToMove = mover(rng);

	wildfire.getPosition(positionX, positionY);

	switch (whereToMove)
	{
	case 0:
		break;
	case 1: if (wildfireMoveCheck(positionX, positionY+1))
	{
		wildfire.setPosition(positionX, positionY + 1);
		currentLevel[positionX][positionY] = '.';
		currentLevel[positionX][positionY + 1] = '!';
	}
			break;
	case 2: if (wildfireMoveCheck(positionX +1, positionY))
	{
		wildfire.setPosition(positionX + 1, positionY);
		currentLevel[positionX][positionY] = '.';
		currentLevel[positionX + 1][positionY] = '!';
	}
			break;
	case 3: if (wildfireMoveCheck(positionX, positionY -1))
	{
		wildfire.setPosition(positionX, positionY-1);
		currentLevel[positionX][positionY] = '.';
		currentLevel[positionX][positionY-1] = '!';
	}
			break;
	case 4: if (wildfireMoveCheck(positionX - 1, positionY))
	{
		wildfire.setPosition(positionX - 1, positionY);
		currentLevel[positionX][positionY] = '.';
		currentLevel[positionX - 1][positionY] = '!';
	}
			break;
	}
}
	
	bool Level::wildfireMoveCheck(int x, int y)
	{
		if (currentLevel[x][y] == '#')
		{
			return false;
		}
		else if (currentLevel[x][y] == '@')
		{
			deathMessage();
			system("PAUSE");
			exit(1);
			return false;
		}
		else if (currentLevel[x][y] == 'K')
		{
			return false;
		}
		else if (currentLevel[x][y] == '+')
		{
			return false;
		}
		return true;
	}

	//Read message from text file which will show up on the screen after player death
	void Level::deathMessage()
	{
		std::string line;
		std::ifstream myfile("death.txt");
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				std::cout << line << '\n';
			}
			myfile.close();
		}
		else std::cout << "Unable to open file";
		std::cout << "\n";
	}

	//Read message from text file which will show up on the screen after player wins
	void Level::winMessage()
	{
		std::string line;
		std::ifstream myfile("win.txt");
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				std::cout << line << '\n';
			}
			myfile.close();
		}
		else std::cout << "Unable to open file";
		std::cout << "\n";
	}

	// Method used to pick pseudorandom reward for '?' on the map
	void Level::gamble(Player &player)
	{
		int roll;
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> gamble(1, 3); 
		roll = gamble(rng);

		switch (roll)
		{
		case 1:
			warningMessage = "You found rusty sword\no==[]::::::::::::::::>";
			player.setAttack(15);
			break;
		case 2:
			warningMessage = "It's a trap! Run away!";
			player.subHealth(20);
			break;
		case 3: 
			warningMessage = "You found curious potion. It makes you feel stronger";
			player.setAttack(5);
			player.addHealth(20);
			break;
		}

	}


	