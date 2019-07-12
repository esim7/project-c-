#include "gameObject.h"

GameObject::GameObject()
{
	type = Type_None;

	xPOS = 0.0;
	yPOS = 0.0;
	xSPEED = 0.0;
	ySPEED = 0.0;

	obj_symbol = '?';
	m_color = ConsoleColor_White;
	m_backgroundColor = ConsoleColor_Black;
}

void GameObject::render(GameRender* gr)
{
	int row = int(yPOS);
	int column = int(xPOS);

	gr->drawChar(row, column, obj_symbol, m_color, m_backgroundColor);
}

void GameObject::update(float dt)
{
	yPOS += ySPEED * dt;
	xPOS += xSPEED * dt;
}

bool GameObject::Peresechenie(GameObject* object)
{
	if (int(yPOS) == int(object->yPOS)
		&& int(xPOS) == int(object->xPOS))
		return true;

	return false;

}

void GameObject::shot(GameObject * obj, float speed)
{
	obj->setYSpeed(speed);
}


