

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include"GameRender.h"
using namespace std;

enum kbKEYS {
	ESC = 27,
	SPACE = 32,
	ENTER = 13,

	CURSOR1 = 0, CURSOR2 = 224,
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80,

	HOME = 71,
	END = 79,
	PG_UP = 73,
	PG_DOWN = 81,
};

void SetColor(WORD wAttributes) {
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOUTPUT, wAttributes);
}
void SetColor(int colBkgr, int colSym) {
	SetColor(colBkgr * 16 + colSym);
}
void SetPos(int x, int y) {
	COORD cd{ x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}
class Menu {
	GameRender ren;
	vector<string> strItems;
	vector<int>    idItems;
	int X, Y;
	int defColor, selColor;
	int selPos;
public:
	Menu() : X(10), Y(4), selPos(),
		defColor(0x07), selColor(0x1E) {}

	void Add(int id, const string& mPoint) {
		strItems.push_back(mPoint);
		idItems.push_back(id);
	}
	void SetColor(int defColSym, int defColFon,
		int selColSym, int selColFon) {
		defColor = (defColFon << 4) | defColSym;
		selColor = (selColFon << 4) | selColSym;
	}
	void GetColor(int& defColSym, int& defColFon,
		int& selColSym, int& selColFon) {
		defColSym = defColor & 0x000F;
		defColFon = defColor >> 4;
		selColSym = selColor & 0x000F;
		selColFon = selColor >> 4;
	}
	int Show(int x = 10, int y = 4, bool bClear = true) {
		if (bClear) system("cls");
		X = x, Y = y;
		do {

			for (size_t i = 0; i < strItems.size(); i++) {
				SetPos(X, Y + i);
				int tmp = (selPos == i) ? selColor : defColor;
				::SetColor(tmp);
				cout << strItems[i];
			}
			int key = _getch();
			if (key == kbKEYS::CURSOR1 || key == kbKEYS::CURSOR2) {
				key = _getch();
			}
			while (_kbhit()) _getch();
			switch (key) {
			case kbKEYS::UP: case kbKEYS::LEFT:
				if (selPos > 0) selPos--;
				break;
			case kbKEYS::DOWN: case kbKEYS::RIGHT:
				if (selPos < strItems.size() - 1) selPos++;
				break;
			case kbKEYS::ENTER:
				return idItems[selPos];
			case kbKEYS::ESC:
				return -1;
				break;
			}
		} while (true);
		return -1;
	}


};

