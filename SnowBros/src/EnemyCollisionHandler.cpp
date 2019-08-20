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
	if (!checkCollision(other))
	{
		return false;
	}

	Actor* tmp = dynamic_cast<Actor*>(entity);
	if(checkCollision(other) == SIDE_DOWN && (other->getType() == "T" || other->getType() == "TL" || other->getType() == "TR") && tmp->isFalling())
	{
		tmp->setPosY(other->getPosY() - tmp->getDim()->y);
		tmp->setCanJump(true);
		tmp->setFalling(false);
	}

	if (checkCollision(other) && (other->getType() == "BulletLeft" || other->getType() == "BulletRight" || other->getType() == "BulletPLeft" || other->getType() == "BulletPRight") &&!(tmp->getLivelloPalla() == ROTOLA))
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
	}

	if(checkCollision(other) == SIDE_LEFT && other->getType() == "TR" && tmp->isFalling() && !tmp->isJumping())
	{
		tmp->setPosX(other->getPosX() + other->getDim()->x);
		tmp->setLastDirection(ROTOLA_RIGHT);
	}

	if(checkCollision(other) == SIDE_RIGHT && other->getType() == "TL" && tmp->isFalling() && !tmp->isJumping())
	{
		tmp->setPosX(other->getPosX() - tmp->getDim()->x);
		tmp->setLastDirection(ROTOLA_LEFT);
	}

	if (checkCollision(other) && tmp->getLivelloPalla() == ROTOLA && (other->getType() == "Enemy1" || other->getType() == "Enemy2" || other->getType() == "Enemy3"))
	{
		Actor* tmp2 = dynamic_cast<Actor*>(other);
		if (!(tmp2->getLivelloPalla() == ROTOLA))
		{
			tmp2->setDestroyed(true);
			int x = rand() % 10;
			// if (x == 0)
				tmp->getSpawner()->spawnEntity("G", tmp->getPosX(), tmp->getPosY());
		}
	}

	return true;
}

CollisionHandler* EnemyCollisionHandler::clone() { return new EnemyCollisionHandler(); }
