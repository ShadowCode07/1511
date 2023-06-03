#include <Game.h>

Game::Game()
{
	assert(!GetWindowHandle());
	SetTargetFPS(60);
}

Game::~Game() noexcept
{
	assert(GetWindowHandle());
}

bool Game::GameShoudlClose()
{
	return gameShoudlClose || WindowShouldClose();
}

void Game::Tick()
{
	BeginDrawing();

	Update();
	Draw();

	EndDrawing();
}

void Game::Update()
{
}

void Game::Draw()
{
	ClearBackground(BLACK);
	static bool setup = false;

	if (menu.startGame == 0)
	{
		menu.DrawMenu();
	}
	else
	{
		Board& board = Board::getInstance();
		if(setup == false)
		{ 
			board.setBoardHeight(menu.inputHeight);
			board.setBoardWidth(menu.inputWidth);
			board.setup();
			setup = true;
		}

		board.DrawBoard();
	}
}
