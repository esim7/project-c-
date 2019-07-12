#pragma once

#include "GameRender.h"

enum GameObjectType
{
	Type_None,
	Type_Ship,
	Type_Bullet,
	Type_Enemy,
	Type_EnemyBullet,
	Type_Shield,
};

class GameObject
{
private:
	float xPOS;
	float yPOS;
	float xSPEED;
	float ySPEED;
	int obj_health;
	char obj_symbol;
	GameObjectType type;
	ConsoleColor m_color;
	ConsoleColor m_backgroundColor;
public:
	GameObject();
	void render(GameRender* rs);
	void update(float dt);

	bool Peresechenie(GameObject* object);

	void setType(GameObjectType _type) { type = _type; }
	GameObjectType getType() { return type; }

	void setX(float _x) { xPOS = _x; }
	float getX() { return xPOS; }

	void setY(float _y) { yPOS = _y; }
	float getY() { return yPOS; }

	void setXSpeed(float _x) { xSPEED = _x; }
	float getXSpeed() { return xSPEED; }

	void setYSpeed(float _y) { ySPEED = _y; }
	float getYSpeed() { return ySPEED; }

	void setHealth(int _h) { obj_health = _h; }
	int getHealth() { return obj_health; }

	void setSymbol(char _symbol) { obj_symbol = _symbol; }
	char getSymbol() { return obj_symbol; }

	void setColor(ConsoleColor _color) { m_color = _color; }
	ConsoleColor getColor() { return m_color; }

	void setBackgroundColor(ConsoleColor _backgroundColor) { m_backgroundColor = _backgroundColor; }
	ConsoleColor getBackgroundColor() { return m_backgroundColor; }

	void shot(GameObject* obj, float speed);
};



#pragma once
