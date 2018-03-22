#include "GameWindow.h"

GameWindow::GameWindow(std::string level_number)
{
	level.load(level_number, player);
	player.createPlayer(100, 15, 0, 1);
	boss.createBoss(200, 30);
}

GameWindow::~GameWindow()
{
}

// Method to clear screen after each move
void GameWindow::clearScreen(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten))
		return;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;

	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	SetConsoleCursorPosition(hConsole, coordScreen);
}

// Player stats displayed above the map
void GameWindow::statsBar(Player &player)
{
	std::cout << "\nYour stats\n";
	std::cout << "Health: " << player.getHealth() << std::endl;
	std::cout << "Attack: " << player.getAttack() << std::endl;
	std::cout << "Experience: " << player.getExperience() << std::endl;
	std::cout << "Level: " << player.getLevel() << std::endl << std::endl;
}

// Function which collects data to start the game
void GameWindow::startGame()
{

	startMessage();

	char playerInput;

	while (true)
	{
		HWND console = GetConsoleWindow(); 
		RECT r;
		GetWindowRect(console, &r); 
		MoveWindow(console, r.left, r.top, 550, 650, TRUE); // fixed size of console window

		statsBar(player);
		level.messageBox();
		level.show();
		playerInput = _getch();
		clearScreen(GetStdHandle(STD_OUTPUT_HANDLE));
		level.movePlayer(playerInput, player, goblin, boss);
	}
}

// Message showed after starting the game
void GameWindow::startMessage()
{
	std::string line;
	std::ifstream myfile("start.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << line << '\n';
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
	system("PAUSE");
	std::cout << "\n";

}
