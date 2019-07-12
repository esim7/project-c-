#include"GameRender.h"
#include<cstdio>
#include"MainInclude.h"
#include<windows.h>
#include <iostream>
GameRender::GameRender()
{
	consoleHandle = 0;
	for (int r = 0; r < screenRows; r++)
	{
		for (int c = 0; c < screenColumns; c++)
		{
			backBuffer[r][c].symbol = 0;
			backBuffer[r][c].symbolColor = ConsoleColor_Gray;
			backBuffer[r][c].backgroundColor = ConsoleColor_Black;
			screenBuffer[r][c] = backBuffer[r][c];
		}
	}
}
void GameRender::initialize()
{
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CursorHide();
	SetConsoleSize();
}

void GameRender::clear()
{
	for (int r = 0; r < screenRows; r++)
	{
		for (int c = 0; c < screenColumns; c++)
		{
			backBuffer[r][c].symbol = 0;
			backBuffer[r][c].backgroundColor = ConsoleColor_Black;
		}
	}
}

void GameRender::drawChar(int r, int c, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
	if (r < 0 || c < 0 || r >= screenRows || c >= screenColumns)
	{
		return;
	}
	backBuffer[r][c].symbol = symbol;
	backBuffer[r][c].symbolColor = symbolColor;
	backBuffer[r][c].backgroundColor = backgroundColor;
}

void GameRender::drawText(int r, int c, const char* text, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
	int column = c;
	char symbol = *text;
	while (symbol != 0)
	{
		drawChar(r, column, symbol, symbolColor, backgroundColor);
		text++;
		column++;
		symbol = *text;
	}
}

void GameRender::flush()
{
	bool screenBufferModified = false;
	for (int r = 0; r < screenRows; r++)
	{
		for (int c = 0; c < screenColumns; c++)
		{
			if ((backBuffer[r][c].symbol != screenBuffer[r][c].symbol)
				|| (backBuffer[r][c].symbolColor != screenBuffer[r][c].symbolColor)
				|| (backBuffer[r][c].backgroundColor != screenBuffer[r][c].backgroundColor))
			{
				screenBuffer[r][c] = backBuffer[r][c];
				setPos(r, c);
				setColor(backBuffer[r][c].symbolColor, backBuffer[r][c].backgroundColor);
				cout << backBuffer[r][c].symbol;
				screenBufferModified = true;
			}
		}
	}
	if (screenBufferModified)
	{
		setPos(0, 0);
	}
}

void GameRender::setPos(int r, int c)
{
	COORD cursorCoord;
	cursorCoord.X = c;
	cursorCoord.Y = r;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

void GameRender::setColor(ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
	unsigned char cosoleColor = symbolColor | (backgroundColor << 4);
	SetConsoleTextAttribute(consoleHandle, cosoleColor);
}
