#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_

#define SCREEN_WIDTH  80
#define SCREEN_HEIGHT  24
#define HUD_HEIGHT  3
#define STAGE_HEIGHT  (SCREEN_HEIGHT-HUD_HEIGHT)
#define NUMBER_SCORE 1500

// you must have a config file, both for windows and for compiling on Linux (MAMA)
// BUT, you need to change the content of the config!
#include "config.h"
#include "Color.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void gotoxy(int x, int y);
void setTextColor(Color);
void hideCursor();
void clear_screen();

	#ifndef WINDOWS	
		int _getch(void);
		int _kbhit(void);
		void Sleep(unsigned long);
		void _itoa_s(unsigned int, char s[], unsigned int, int);
		void setTextColor(int);
	#else
		#include <stdlib.h>
		#include <conio.h>
		#include <windows.h>
	#endif

#endif