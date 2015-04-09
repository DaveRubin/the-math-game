#include "Hud.h"


Hud::Hud()
{
	createNewObjects();
	int rightPlayePos = 15;
	//set position of the player 1 equation,lives and score
	equation1->position.set(0, 0);
	lives1->position.set(0, 1);
	score1->position.set(5, 1);
	score1->setText(0);
	////set position of the player 1 equation,lives and score
	equation2->position.set(SCREEN_WIDTH - rightPlayePos, 0);
	lives2->position.set(SCREEN_WIDTH - rightPlayePos, 1);
	score2->position.set(SCREEN_WIDTH - rightPlayePos + 5, 1);
	score2->setText(0);

	string lineString = "";
	lineString.append(SCREEN_WIDTH, '\xB2');

	seperator->setText(lineString);
	seperator->position.set(0, 2);
}


void Hud::createNewObjects()
{
	equation1 = new Equation();
	equation2 = new Equation();
	lives1 = new LivesMeter();
	lives2 = new LivesMeter();
	score1 = new TextField();
	score2 = new TextField();
	seperator = new TextField();
}

void Hud::render()
{
	equation1->render();
	equation2->render();
	lives1->render();
	lives2->render();
	score1->render();
	score2->render();
	seperator->render();

	redraw = false;
}


void  Hud::updatePlayerStats(int playerNum , Player *player)
{
	//TODO: add condinional change, and set redraw only when somthing has changed
	if (playerNum == 1)
	{
		lives1->setLives(player->getLives());
		score1->setText(player->getScore());
	}
	else
	{
		lives2->setLives(player->getLives());
		score2->setText(player->getScore());
	}
	redraw = true;
}