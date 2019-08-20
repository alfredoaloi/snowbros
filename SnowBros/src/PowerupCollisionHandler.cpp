/*
 * PowerupCollisionHandler.cpp
 *
 *  Created on: 20 ago 2019
 *      Author: laolr
 */

#include "PowerupCollisionHandler.h"

PowerupCollisionHandler::PowerupCollisionHandler() {
	// TODO Auto-generated constructor stub

}

PowerupCollisionHandler::~PowerupCollisionHandler() {
	// TODO Auto-generated destructor stub
}

bool PowerupCollisionHandler::handleCollision(Entity* other)
{
	Actor* tmp = dynamic_cast<Actor*>(entity);
	if (checkCollision(other) == SIDE_DOWN && (other->getType() == "T" || other->getType() == "TL" || other->getType() == "TR"))
	{
		tmp->setPosY(other->getPosY() - tmp->getDim()->y);
		return true;
	}

	if (!checkCollision(other))
	{
		return false;
	}
}

CollisionHandler* PowerupCollisionHandler::clone() { return new PowerupCollisionHandler(); }
