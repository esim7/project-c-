#pragma once
#pragma warning(disable:4996)
#include"Menu.h"
#include<iostream>
#include"consoleColor.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
//#include "MainInclude.h"
const int MainThemeRows = 29;
const int MainThemeColumns = 49;
const int MaxObjThemeCount = 512;

char title[MainThemeRows][MainThemeColumns]
{
	"                                           _.oo.",
	"                   _.u[[/;:,.         .odMMMMMM'",
	"                .o888UU[[[/;:-.  .o@P^    MMM^  ",
	"               oN88888UU[[[/;::-.        dP^    ",
	"              dNMMNN888UU[[[/;:--.   .o@P^      ",
	"             ,MMMMMMN888UU[[/;::-. o@^          ",
	"             NNMMMNN888UU[[[/~.o@P^             ",
	"             888888888UU[[[/o@^-..              ",
	"            oI8888UU[[[/o@P^:--..               ",
	"         .@^  YUU[[[/o@^;::---..                ",
	"       oMP     ^/o@P^;:::---..                  ",
	"    .dMMM    .o@^ ^;::---...                    ",
	"  dMMMMMMM@^`       `^^^^                       ",
	"  YMMMUP^                                       ",
	"   ^^                                           ",
	"            _____                               ",
	"           / ___/ _____ ____ _________          ",
	"           \\ __ \\/ __ \ / __ `/ ___/ _ \\     ",
	"           ___/ / /_/ / /_/ / /__/  __/         ",
	"          /____/ .___/\\__,_/\\___/\\___/       ",
	"              /_/                               ",
	"                                                ",
	"     ____                     __                ",
	"    /  _/___ _   ______ _____/ /__  __________  ",
	"    / // __ \\ | / / __ `/ __  / _ \\/ ___/ ___/",
	"  _/ // / / / |/ / /_/ / /_/ /  __/ /  (__  )   ",
	" /___/_/ /_/|___/\\__,_/\\__,_/\\___/_/  /____/ ",
	"                                                ",
	"         press Enter key to continie...         "
};

using namespace std;

class MainTheme
{
protected:
	char mainTitle[MainThemeRows][MainThemeColumns];

public:
	MainTheme()
	{
		for (int i = 0; i < MainThemeRows; i++)
		{
			for (int j = 0; j < MainThemeColumns; j++)
			{
				mainTitle[i][j] = title[i][j];
			}
		}
	}
	void Print()
	{
		int y = 0;
		SetColor(ConsoleColor_Cyan);
		for (int i = 0; i < MainThemeRows; i++)
		{
			SetPos(28, y);
			for (int j = 0; j < MainThemeColumns; j++)
			{
				cout << mainTitle[i][j];
			}
			y++;
		}
	}
};

















