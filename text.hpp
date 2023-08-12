#include <iostream>
#include "raylib.h"

typedef struct FontSet 
{ //creates easy to use texture and font detail variables for later use
	Texture2D font;
	int fWidth;
	int fHeight;
	int rowSize;
	int columnSize;

} FontSet;

typedef struct charIndex 
{ //little solution to make it easy for character rendering and indexing
	int x;
	int y;
} charIndex;

void insertChar(int x, int y, int indexX, int indexY, FontSet font, int scale = 1, Color background = BLACK, Color foreground = WHITE);

void insertStr(std::string phrase, int x, int y, FontSet font, int scale, Color background = BLACK, Color foreground = WHITE);