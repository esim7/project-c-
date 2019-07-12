#pragma once
#include <ctime>
#include "GameRender.h"
#include "gameObject.h"
#include <vector>
using namespace std;
const int gameObjectsCountMax = 512;

class Game
{
private:
	/*vector<GameObject*> objects;*/
	bool isGameActive;
	clock_t clockLastFrame;
	GameRender rendering;
	GameObject* objects[gameObjectsCountMax];
	float shipFireCooldownTime;
	float EnemyAmplitude;
	float EnemyFireCooldownTime;

public:
	void render();
	void update(float dt);
	GameObject* createObject(GameObjectType type, int health, float x, float y, char symbol, ConsoleColor color, ConsoleColor bgColor);
	void destroyObject(GameObject* object);
	Game();
	void setupSystem();
	void initialize();
	bool frame();
	void clear();

};