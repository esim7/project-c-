#pragma once
#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include"GameRender.h"

using namespace std;

void SetConsoleSize(int row = 25, int col = 80) {
	char str[100];
	sprintf(str, "mode con cols=%d lines=%d", col, row);
	system(str);
	//system("mode con cols=50 lines=24");
	system("cls");
	//CursorHide();  // Скрыть курсор
}
void CursorHide(BOOL bVisible = 0, DWORD dwSize = 10) {
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	// Get console handle
	hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	// Hide console cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = dwSize;
	cursorInfo.bVisible = bVisible;
	SetConsoleCursorInfo(hOUTPUT, &cursorInfo);
}


