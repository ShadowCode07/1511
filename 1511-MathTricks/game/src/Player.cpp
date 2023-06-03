#include <Player.h>

Player::Player(int startingPosition, Color color, int own)
	:
	currentPosition(startingPosition),
	color(color),
	own(own)
{
	//sprite = LoadTexture(texture.c_str());
}


void Player::drawPlayer(int x, int y, Color a)
{
	DrawRectangle(x, y, 65, 65, color);
	DrawRectangleLines(x, y, 65, 65, WHITE);
	DrawText("O", x+10, y+10, 40, a);
}