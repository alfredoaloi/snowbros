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
	if(other->getPosY() + other->getDim()->y > entity->getPosY() && other->getPosY() + other->getDim()->y < entity->getPosY() + entity->getDim()->y && entity->getPosX() == other->getPosX())
		{ /*std::cout << "side_up" << std::endl << std::flush;*/ return SIDE_UP; }
	if(entity->getPosY() + entity->getDim()->y > other->getPosY() && entity->getPosY() + entity->getDim()->y < other->getPosY() + other->getDim()->y && entity->getPosX() + entity->getDim()->x > other->getPosX() && entity->getPosX() < other->getPosX() + other->getDim()->x)
		{ /*std::cout << "side_down" << std::endl << std::flush;*/ return SIDE_DOWN; }
	if(other->getPosX() + other->getDim()->x > entity->getPosX() && other->getPosX() < entity->getPosX() + entity->getDim()->x && ((other->getPosY() + other->getDim()->y > entity->getPosY() && other->getPosY() < entity->getPosY() + entity->getDim()->y)))
		{ /*std::cout << "side_left" << std::endl << std::flush;*/ return SIDE_LEFT; }
	if(entity->getPosX() + entity->getDim()->x > other->getPosX() && entity->getPosX() < other->getPosX() + other->getDim()->x && ((other->getPosY() + other->getDim()->y > entity->getPosY() && other->getPosY() < entity->getPosY() + entity->getDim()->y)))
		{ /*std::cout << "side_right" << std::endl << std::flush;*/ return SIDE_RIGHT; }

	return NO_COLLISION;
}

Entity* CollisionHandler::getEntity(){ return entity; }

CollisionHandler* CollisionHandler::clone() { return new CollisionHandler(); }
