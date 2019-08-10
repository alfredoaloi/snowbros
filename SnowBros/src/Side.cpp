/*
 * Lato.cpp
 *
 *  Created on: 9 ago 2019
 *      Author: Francesco
 */

#include "Side.h"

Side::Side(Side_t sideType) {
	this->sideType = sideType;
	this->entity = nullptr;
}

Side::~Side() {

}

void Side::setEntity(Entity* entity) { this->entity = entity; }

bool Side::checkCollision(Entity* other)
{
	if(sideType == SIDE_RIGHT)
	{
		if(other->getPosX() > entity->getPosX() + entity->getDim()->x - 1)
			return false;
	}
	else if(sideType == SIDE_LEFT)
	{
		if(entity->getPosX() > other->getPosX() + other->getDim()->x - 1)
			return false;
	}
	else if(sideType == SIDE_UP)
	{
		if(entity->getPosY() > other->getPosY() + other->getDim()->y - 1)
			return false;
	}
	else if(sideType == SIDE_DOWN)
	{
		if(other->getPosY() > entity->getPosY() + entity->getDim()->y - 1)
			return false;
	}

	return true;
}

Side_t Side::getSideType() { return sideType; }

