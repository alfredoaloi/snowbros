/*
 * CollisionHandler.cpp
 *
 *  Created on: 9 ago 2019
 *      Author: Francesco
 */

#include "CollisionHandler.h"

CollisionHandler::CollisionHandler() {
	entity = nullptr;
}

CollisionHandler::~CollisionHandler() { }

bool CollisionHandler::handleCollision(Entity* other) { return false; }

void CollisionHandler::setEntity(Entity* e){ entity = e; }

Side_t CollisionHandler::checkCollision(Entity* other)
{
	if(other->getPosY() + other->getDim()->y > entity->getPosY() && other->getPosY() + other->getDim()->y < entity->getPosY() + entity->getDim()->y && other->getPosX() >= entity->getPosX() - entity->getPosX() && other->getPosX() <= entity->getPosX() + entity->getDim()->x)
		return SIDE_UP;
	if(entity->getPosY() + entity->getDim()->y > other->getPosY() && entity->getPosY() + entity->getDim()->y < other->getPosY() + other->getDim()->y && entity->getPosX() >= other->getPosX() - other->getDim()->x && entity->getPosX() <= other->getPosX() + other->getDim()->x)
		return SIDE_DOWN;
	if(other->getPosX() + other->getDim()->x > entity->getPosX() && other->getPosX() < entity->getPosX() + entity->getDim()->x && other->getPosY() >= entity->getPosY() - entity->getPosY() && other->getPosY() <= entity->getPosY() + entity->getDim()->y)
		return SIDE_LEFT;
	if(entity->getPosX() + entity->getDim()->x - 1 > other->getPosX() && entity->getPosX() - 1 < other->getPosX() + other->getDim()->x && other->getPosY() >= other->getPosY() - other->getPosY() && entity->getPosY() <= other->getPosY() + other->getDim()->y)
		return SIDE_RIGHT;

	return NO_COLLISION;
}

Entity* CollisionHandler::getEntity(){ return entity; }
