/*
 * EnemyCollisionHandler.cpp
 *
 *  Created on: 17 ago 2019
 *      Author: laolr
 */

#include "EnemyCollisionHandler.h"

EnemyCollisionHandler::EnemyCollisionHandler() {
}

EnemyCollisionHandler::~EnemyCollisionHandler() {
}

bool EnemyCollisionHandler::handleCollision(Entity* other)
{
	Actor* tmp = dynamic_cast<Actor*>(entity);
	if(checkCollision(other) == SIDE_DOWN && (other->getType() == "T" || other->getType() == "TL" || other->getType() == "TR") && tmp->isFalling())
	{
		tmp->setPosY(other->getPosY() - tmp->getDim()->y);
		tmp->setCanJump(true);
		tmp->setFalling(false);
		return true;
	}

	else if (checkCollision(other) && (other->getType() == "BulletLeft" || other->getType() == "BulletRight"))
	{
		tmp->setImmobile(true);
		if (!(tmp->getLastDirection() == NO_DIRECTION))
			tmp->setLastDirection(NO_DIRECTION);
		if (tmp->getLivelloPalla() == NULLA)
			tmp->setLivelloPalla(POCA);
		else if (tmp->getLivelloPalla() == POCA)
			tmp->setLivelloPalla(TANTA);
		else if (tmp->getLivelloPalla() == TANTA)
			tmp->setLivelloPalla(PIENA);
		return true;
	}

	else if (!checkCollision(other))
	{
		return false;
	}
}

CollisionHandler* EnemyCollisionHandler::clone() { return new EnemyCollisionHandler(); }
