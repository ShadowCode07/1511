#pragma once
#include <string>
#include <raylib.h>

class Player
{
public:
	Player(int startingPosition, Color color, int own);
	
	void drawPlayer(int x, int y, Color a);
	
	Color color = BLUE;
	int currentPosition = 0;
	int own;
	float score = 0;
};