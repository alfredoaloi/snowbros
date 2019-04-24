/*
 * Entity.cpp
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#include "Entity.h"

Entity::Entity() { }

void Entity::onRedraw() { }

Entity::Entity(float x, float y, Dimensions d, Action* a) : pos_x(x), pos_y(y), dim(d), action(a)
{
	if(action != nullptr)
		action->setEntity(this);
}

Entity::Entity(Entity* e)
{
	this->pos_x = e->pos_x;
	this->pos_y = e->pos_y;
	this->dim = e->dim;
	this->action = e->action;
}

Entity::~Entity() { }

Action* Entity::getAction() { return action; }
