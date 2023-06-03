#pragma once
#include <string>
#include <raylib.h>
#include <Board.h>

class Player
{
public:
	Player(std::string texture);
	~Player();
	
	void drawPlayer();
	void PlayerMove();
private:
	std::string Name = " ";
	bool lost = false;
	Texture2D sprite;
	

};

//Player player1();
//Player player2;