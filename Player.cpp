#include "Player.h"

void Player::setDefaultKeys()
{
	keyUp = 'w';
	keyLeft = 'a';
	keyDown = 's';
	keyRight = 'd';
}

Player::Player()
{
	score = 0;
	setDefaultKeys();
}


Player::Player(char look)
{
	score = 0;
	setView(look);
	setDefaultKeys();
}


Player::Player(char look, string tldr)
{
	score = 0;
	setView(look);
	if (tldr.length() != 4)
		setDefaultKeys();
	else {
		keyUp = tldr[0];
		keyLeft = tldr[1];
		keyDown = tldr[2];
		keyRight = tldr[3];
	}
}