#include "text.hpp"

charIndex asciiTable[] = 
{ // this table gets index of each character from space all the way to tilda and makes it easy for the insertStr to access it
	//15 characters across each row
	//7 rows
	{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},{9,2},{10,2},{11,2},{12,2},{13,2},{14,2},{15,2},
	{0,3}, {1,3},{2,3},{3,3},{4,3},{5,3},{6,3},{7,3},{8,3},{9,3},{10,3},{11,3},{12,3},{13,3},{14,3},{15,3},
	{0,4}, {1,4},{2,4},{3,4},{4,4},{5,4},{6,4},{7,4},{8,4},{9,4},{10,4},{11,4},{12,4},{13,4},{14,4},{15,4},
	{0,5}, {1,5},{2,5},{3,5},{4,5},{5,5},{6,5},{7,5},{8,5},{9,5},{10,5},{11,5},{12,5},{13,5},{14,5},{15,5},
	{0,6}, {1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6},{9,6},{10,6},{11,6},{12,6},{13,6},{14,6},{15,6},
	{0,7}, {1,7},{2,7},{3,7},{4,7},{5,7},{6,7},{7,7},{8,7},{9,7},{10,7},{11,7},{12,7},{13,7},{14,7},{15,7}
};//possibly better way to do this... i dont care though

void insertChar(int x, int y, int indexX, int indexY, FontSet font, int scale, Color background, Color foreground) //made to insert characters from fonts
{
	DrawRectangle(x, y, font.fWidth*scale, font.fHeight*scale, background); //draws background to avoid overlapping
	DrawTexturePro(font.font,
		{ (float)(font.fWidth * indexX),(float)(font.fHeight * indexY),(float)font.fWidth,(float)font.fHeight }, //gets character from sheet
		{ (float)x, (float)y,(float)font.fWidth * scale,(float)font.fHeight * scale }, //outputs proper position and scale
		{ 0,0 }, //sets origin point
		0.f, //rotation float if needed
		foreground); // foreground color

}

void insertStr(std::string phrase, int x, int y, FontSet font, int scale, Color background, Color foreground)
{
	for (int i=0; i < phrase.size(); i++)
	{
		//std::cout << asciiTable[phrase[i] - 32].x << "," << asciiTable[phrase[i] - 32].y << "\n";
		insertChar(x + i*scale * font.fWidth, y, asciiTable[phrase[i] - 32].x, asciiTable[phrase[i] - 32].y, font, scale, background, foreground);
	}
}