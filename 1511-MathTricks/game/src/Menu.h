#pragma once
#include <raylib.h>

class Menu
{
public:
	Menu();

	void DrawMenu();
	bool StartGame();

	int inputWidth = 0;
	int inputHeight = 0;
	bool startGame = 0;
private:
	char input[4] = "\0";
	int letterCount = 0;
};
