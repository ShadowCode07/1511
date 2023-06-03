#include <Player.h>

Player::Player(std::string texture)
{
	sprite = LoadTexture(texture.c_str());
}

Player::~Player()
{
	UnloadTexture(sprite);
}

void Player::drawPlayer()
{
}

void Player::PlayerMove()
{

}
