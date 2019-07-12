#pragma once

#include "GameRender.h"

// Перечисление для кодов кнопок клавиатуры
enum KEY { // Именнованное перечисление 
	ESC = 27,    // const int ESC = 27;
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

const int levelRows = screenRows;
const int levelColumns = screenColumns;
const float shipSpeed = 10.0;
const float EnemyFireCooldown = 0.5;
const float shipFireCooldown = 0.2;
const float bulletSpeed = 40.0;
const float alienAmplitude = 3.0;
const float alienSpeed = 0.23;
const int EnemyHealth = 1;
const int ShieldHealth = 3;
const int ShipHealth = 1;
const float EnemyBulletSpeed = 40.0;

const char Symbol_EnemyBullet = 'I';
const char Symbol_Ship = 'P';
const char Symbol_Bullet = '|';
const char Symbol_Alien = 'E';
const char Symbol_Shield = 'S';


char GetSymbol(unsigned char Symbol)
{
	switch (Symbol)
	{
	case Symbol_Ship: return 202;
	case Symbol_Bullet: return 179;
	case Symbol_Alien: return 203;
	case Symbol_EnemyBullet: return 179;
	case Symbol_Shield: return 178;
	}
	return '?';
}

ConsoleColor GetSymbColor(unsigned char Symbol)
{
	switch (Symbol)
	{
	case Symbol_Ship: return ConsoleColor_Red;
	case Symbol_Bullet: return ConsoleColor_Red;
	case Symbol_Alien: return ConsoleColor_Cyan;
	case Symbol_EnemyBullet: return ConsoleColor_Green;
	case Symbol_Shield: return ConsoleColor_Yellow;
	}
	return ConsoleColor_Gray;
}

ConsoleColor GetBgColor(char Symbol)
{
	switch (Symbol)
	{
	case Symbol_Ship: return ConsoleColor_Blue;
	}
	return ConsoleColor_Black;
}

const char level1[levelRows][levelColumns + 1] =
{
	"                                                                                ",
	"         EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE           ",
	"                                                                                ",
	"       E E E      E E E     E E E      E E E     E E E     E E E                ",
	"                                                                                ",
	"            E E E      E E E     E E E      E E E     E E E     E E E           ",
	"                                                                                ",
	"       E E E      E E E     E E E      E E E     E E E     E E E                ",
	"                                                                                ",
	"            E E E      E E E     E E E      E E E     E E E     E E E           ",
	"                                                                                ",
	"       E E E      E E E     E E E      E E E     E E E     E E E                ",
	"                                                                                ",
	"            E E E      E E E     E E E      E E E     E E E     E E E           ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"      SSSSSSSSSSSS      SSSSSSSSSSSS      SSSSSSSSSSSS      SSSSSSSSSSSS        ",
	"       SSSSSSSSSS        SSSSSSSSSS        SSSSSSSSSS        SSSSSSSSSS         ",
	"        SSSSSSSS          SSSSSSSS          SSSSSSSS          SSSSSSSS          ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                       P                                        ",
};



