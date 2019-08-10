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
//	if(other->getPosX() + other->getDim()->x - 1 > entity->getPosX() && other->getPosX() - 1 < entity->getPosX() + entity->getDim()->x && entity->getPosY() == other->getPosY())
//		return SIDE_LEFT;
//	if(entity->getPosX() + entity->getDim()->x - 1 > other->getPosX() && entity->getPosX() - 1 < other->getPosX() + other->getDim()->x && entity->getPosY() == other->getPosY())
//		return SIDE_RIGHT;
	if(entity->getPosY() + entity->getDim()->y > other->getPosY() && entity->getPosY() + entity->getDim()->y < other->getPosY() + other->getDim()->y && entity->getPosX() >= other->getPosX() - other->getDim()->x && entity->getPosX() <= other->getPosX() + other->getDim()->x)
		return SIDE_DOWN;
//	if(other->getPosY() + other->getDim()->y - 1 > entity->getPosY() && other->getPosY() - 1 < entity->getPosY() + entity->getDim()->y && entity->getPosX() == other->getPosX())
//		return SIDE_UP;

	return NO_COLLISION;
}

Entity* CollisionHandler::getEntity(){ return entity; }
