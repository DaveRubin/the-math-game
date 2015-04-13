#include "Hud.h"


Hud::Hud()
{
	createNewObjects();

	string lineString = "";
	lineString.append(SCREEN_WIDTH, '\xB2');
	redraw = true;
	seperator->setText(lineString);
	seperator->position.set(0, 2);
}


void Hud::createNewObjects()
{
	seperator = new TextField();
}

void Hud::render()
{
	seperator->render();

	redraw = false;
}


void  Hud::updatePlayerStats(int playerNum , Player *player)
{
	redraw = true;
}