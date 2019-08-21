/*
 * BossOneCollisionHandler.cpp
 *
 *  Created on: 21 ago 2019
 *      Author: laolr
 */

#include "BossOneCollisionHandler.h"

BossOneCollisionHandler::BossOneCollisionHandler() {
	// TODO Auto-generated constructor stub

}

BossOneCollisionHandler::~BossOneCollisionHandler() {
	// TODO Auto-generated destructor stub
}

bool BossOneCollisionHandler::handleCollision(Entity* other)
{
	Actor* tmp = dynamic_cast<Actor*>(entity);

	if (!checkCollision(other))
	{
		return false;
	}

	if (checkCollision(other) == SIDE_DOWN && !tmp->getImmobile() && (other->getType() == "T" || other->getType() == "TL" || other->getType() == "TR"))
	{
		tmp->setPosY(other->getPosY() - tmp->getDim()->y);
		tmp->setCanJump(true);
		tmp->setFalling(false);
	}

	if (checkCollision(other) && (other->getType() == "BulletLeft" || other->getType() == "BulletRight"))
	{
		tmp->setVita(tmp->getVita() - 1);
	}

	return true;
}

CollisionHandler* BossOneCollisionHandler::clone() { return new BossOneCollisionHandler(); }
