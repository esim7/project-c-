#pragma once
#include<Windows.h>               
#include"consoleColor.h"         

const int screenRows = 25;
const int screenColumns = 80;

struct ConsoleSymbolData
{
	char symbol;
	ConsoleColor symbolColor;
	ConsoleColor backgroundColor;
};

class GameRender
{
private:
	HANDLE consoleHandle;
	ConsoleSymbolData backBuffer[screenRows][screenColumns];
	ConsoleSymbolData screenBuffer[screenRows][screenColumns];
public:
	void setPos(int r, int c);
	void setColor(ConsoleColor symbolColor, ConsoleColor backgroundColor);


	GameRender();
	void initialize();
	void clear();
	void drawChar(int r, int c, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor);
	void drawText(int r, int c, const char* text, ConsoleColor symbolColor, ConsoleColor backgroundColor);
	void flush();
};


