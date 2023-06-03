#pragma once
#include <assert.h>
#include <raylib.h>
#include <iostream>
#include <Board.h>
#include <Menu.h>

class Game
{
public:
	Game();
	~Game() noexcept;

	bool GameShoudlClose();

	void Tick();
private:

	void Update();
	void Draw();

	bool gameShoudlClose = false;

	Menu menu;
};