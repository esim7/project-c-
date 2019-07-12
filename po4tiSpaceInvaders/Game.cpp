#include"game.h"
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include"level.h"
#include <conio.h>
#include<iostream>

Game::Game()
{
	isGameActive = true;
	clockLastFrame = 0;
	for (int i = 0; i < gameObjectsCountMax; i++)
	{
		objects[i] = 0;
	}
	shipFireCooldownTime = 0.0;
	EnemyAmplitude = 0.0;
}

void Game::setupSystem()
{
	srand(time(0));
	rendering.initialize();
}

void Game::initialize()
{
	shipFireCooldownTime = 0.0;
	EnemyAmplitude = 0.0;
	// инициализация уровня
	for (int r = 0; r < levelRows; r++)
	{
		for (int c = 0; c < levelColumns; c++)
		{
			char cellSymbol = level1[r][c];

			switch (cellSymbol)
			{
				// создание игрока
			case Symbol_Ship:
			{
				createObject(Type_Ship, ShipHealth, c, r, GetSymbol(cellSymbol), GetSymbColor(cellSymbol), GetBgColor(cellSymbol));
				break;
			}
			// создание врагов
			case Symbol_Alien:
			{
				GameObject* enemy = createObject(Type_Enemy, EnemyHealth, c, r, GetSymbol(cellSymbol), GetSymbColor(cellSymbol), GetBgColor(cellSymbol));
				break;
			}
			// создание укрытия
			case Symbol_Shield:
			{
				GameObject* shield = createObject(Type_Shield, ShieldHealth, c, r, GetSymbol(cellSymbol), GetSymbColor(cellSymbol), GetBgColor(cellSymbol));
				break;
			}
			}
		}
	}
}

bool Game::frame()
{
	clock_t clockNow = clock();
	clock_t deltaClock = clockNow - clockLastFrame;
	float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
	clockLastFrame = clockNow;
	render();
	update(deltaTime);
	return isGameActive;
}

void Game::clear()
{
	for (int i = 0; i < gameObjectsCountMax; i++)
		if (objects[i] != 0)
		{
			delete objects[i];
			objects[i] = 0;
		}
}
void Game::render()
{
	// обнуление буфера
	rendering.clear();
	// рисуем все обьекты на игровое поле
	int EnemyCount = 0;
	for (int i = 0; i < gameObjectsCountMax; i++)
		if (objects[i] != 0)
		{
			if (objects[i]->getType() == Type_Enemy)
			{
				EnemyCount++;
			}
			objects[i]->render(&rendering);
		}
	char buff[64];
	sprintf_s(buff, "Enemies: %d", EnemyCount);
	rendering.drawText(0, 33, buff, ConsoleColor_Green, ConsoleColor_Black);
	rendering.flush();
}

GameObject* Game::createObject(GameObjectType type, int health, float x, float y, char symbol, ConsoleColor color, ConsoleColor bgColor)
{
	for (int i = 0; i < gameObjectsCountMax; i++)
	{
		if (objects[i] == 0)
		{
			GameObject* object = new GameObject();
			object->setHealth(health);
			object->setType(type);
			object->setX(x);
			object->setY(y);
			object->setSymbol(symbol);
			object->setColor(color);
			object->setBackgroundColor(bgColor);
			objects[i] = object;
			return object;
		}
	}
	return 0;
}
void Game::destroyObject(GameObject* object)
{
	for (int i = 0; i < gameObjectsCountMax; i++)
	{
		if (objects[i] == object)
		{
			delete objects[i];
			objects[i] = 0;
			return;
		}
	}
}

void Game::update(float dt)
{
	bool AliveEnemy = false;
	bool ClearEnemyShot = false;
	for (int i = 0; i < gameObjectsCountMax; i++)
	{
		GameObject* object = objects[i];
		if (object != 0)
		{
			object->update(dt);

			switch (object->getType())
			{
			case Type_Ship:
			{
				// Ограничение движения по полю игрока
				if (object->getX() < 0)
					object->setX(0);
				else
					if (object->getX() > screenColumns - 1)
						object->setX(screenColumns - 1);
				//движение
				if (_kbhit()) {
					int key = _getch();
					if (key == KEY::CURSOR1 || key == KEY::CURSOR2) {
						key = _getch();
					}
					while (_kbhit()) _getch();
					if (key == KEY::LEFT)
					{
						object->setXSpeed(-shipSpeed);
					}
					else
					{
						if (key == KEY::RIGHT)
						{
							object->setXSpeed(shipSpeed);
						}
						else
						{
							object->setXSpeed(0);
						}
					}
					if (key == KEY::SPACE)
					{
						if (shipFireCooldownTime <= 0.0)
						{
							shipFireCooldownTime = shipFireCooldown;
							//создание пули
							GameObject* bullet = createObject(Type_Bullet, 1, object->getX(), object->getY() - 1,
								GetSymbol(Symbol_Bullet), GetSymbColor(Symbol_Bullet), GetBgColor(Symbol_Bullet));
							bullet->setYSpeed(-bulletSpeed);
							ClearEnemyShot = true;
						}
					}
				}
			}
			// Пуля
			case Type_Bullet:
			{
				if (object->getY() < 0)
				{
					destroyObject(object);
				}
				else
				{
					for (int e = 0; e < gameObjectsCountMax; e++)
					{
						GameObject* anotherObject = objects[e];
						if (anotherObject != 0)
						{
							if (anotherObject->getType() == Type_Enemy || anotherObject->getType() == Type_Shield)
							{
								if (anotherObject->Peresechenie(object))
								{
									destroyObject(anotherObject);
									destroyObject(object);
									break;
								}
							}
						}
					}
				}
				break;
			}
			case Type_EnemyBullet:
			{
				if (object->getY() > screenRows)
				{
					destroyObject(object);
				}
				else
				{
					for (int e = 0; e < gameObjectsCountMax; e++)
					{
						GameObject* anotherObject = objects[e];
						if (anotherObject != 0)
						{
							if (anotherObject->getType() == Type_Ship || anotherObject->getType() == Type_Shield)
							{
								if (anotherObject->Peresechenie(object))
								{
									destroyObject(anotherObject);
									destroyObject(object);
									break;
								}
							}
						}
					}
				}
				break;
			}
			case Type_Enemy:
			{
				AliveEnemy = true;
				object->setXSpeed(alienAmplitude * cos(EnemyAmplitude));

				break;
			}
			case Type_Shield:
			{
				object->setX(object->getX());
				object->setY(object->getY());
				break;
			}
			}
		}
	}
	if (AliveEnemy)
	{
		int ReadyToShot = rand() % 2500;
		if (ReadyToShot == 5)
		{
			int lifeEnemy = 0;
			for (int i = 0; i < gameObjectsCountMax; i++)
			{
				if (objects[i] != 0)
				{
					if (objects[i]->getType() == Type_Enemy)
					{
						lifeEnemy++;
					}
				}
			}
			int index = rand() % lifeEnemy;
			if (objects[index] != 0)
			{
				if (objects[index]->getType() == Type_Enemy)
				{
					GameObject* EnBullet = createObject(Type_EnemyBullet, 1, objects[index]->getX(), objects[index]->getY() - 1,
						GetSymbol(Symbol_EnemyBullet), GetSymbColor(Symbol_EnemyBullet), GetBgColor(Symbol_Bullet));
					EnBullet->setYSpeed(bulletSpeed);
				}
			}
		}
		ClearEnemyShot = false;
	}

	if (shipFireCooldownTime > 0.0)
		shipFireCooldownTime -= dt;

	//амлетуда движения противников
	EnemyAmplitude += dt;
	//Victory
	if (!AliveEnemy)
	{
		isGameActive = false;
		system("cls");
		rendering.setPos(10, 10);
		rendering.setColor(ConsoleColor_Green, ConsoleColor_Black);
		cout << "Congratulations, You won!";
		cin.get(); cin.ignore();
	}
	//Game over
	int PlayerCount = 0;
	for (int i = 0; i < gameObjectsCountMax; i++)
	{
		if (objects[i] != 0)
		{
			if (objects[i]->getType() == Type_Ship)
			{
				PlayerCount++;
			}
		}
	}
	if (PlayerCount == 0)
	{
		isGameActive = false;
		system("cls");
		rendering.setPos(10, 10);
		rendering.setColor(ConsoleColor_Green, ConsoleColor_Black);
		cout << "Game over :( ";
		cin.get(); cin.ignore();
	}
}
