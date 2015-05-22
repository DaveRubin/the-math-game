#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "Color.h"

const int LEVEL_TURNS = 1500;
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 24;
const int HUD_HEIGHT = 3;
const int STAGE_HEIGHT = 21;
const int NUMBER_SCORE = 1;
const int PLAYER_INIT_LIVES = 3;
const int ESC_KEY = 27;
const int BULLET_REFILL_DURATION = 200;
const Color DEFAULT_COLOR = Color::LIGHTGREY;

const char BULLET_LOOK = '*';

// When submitting in MAMA, put the line below in remark and make sure your project compiles in Linux!
// (this is not mandatory, but can add bonus points)

#define WINDOWS

// make sure to always submit a readme file in English, with student names and ids

// if you put the above #define WINDOWS in comment for compilation in MAMA - remind us in the readme file that we need to take it out of comment!


#endif