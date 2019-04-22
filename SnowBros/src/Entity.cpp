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

Entity::~Entity() { }

Action* Entity::getAction() { return action; }
