#include <Game.h>

int main()
{
	int screenWidth = 960+(960*0.25);
	int screenHeight = 540+(540*0.25);
	std::string title = "1511 - MathTricks";

	Game game;
	InitWindow(screenWidth, screenHeight, title.c_str());

	while (!game.GameShoudlClose())
	{
		game.Tick();
	}
}