/*
 * BulletCollisionHandler.cpp
 *
 *  Created on: 16 ago 2019
 *      Author: laolr
 */

#include "BulletCollisionHandler.h"

BulletCollisionHandler::BulletCollisionHandler() { }

BulletCollisionHandler::~BulletCollisionHandler() { }

bool BulletCollisionHandler::handleCollision(Entity* other)
{
	Actor* tmp = dynamic_cast<Actor*>(entity);
	if (checkCollision(other) == SIDE_DOWN && (other->getType() == "T" || other->getType() == "TL" || other->getType() == "TR"))
	{
		tmp->setDestroyed(true);
		return true;
	}

	else if (tmp->getPosX() < 0 || tmp->getPosX() > screenWidth)
	{
		tmp->setDestroyed(true);
		return true;
	}

	else if (checkCollision(other) == SIDE_RIGHT && other->getType() == "TL")
	{
		tmp->setDestroyed(true);
		return true;
	}

	else if (checkCollision(other) == SIDE_LEFT && other->getType() == "TR")
	{
		tmp->setDestroyed(true);
		return true;
	}

	else if (checkCollision(other) && (entity->getType() == "BulletLeft" || entity->getType() == "BulletRight") && (other->getType() == "Enemy1" || other->getType() == "Enemy2" || other->getType() == "Enemy3" || other->getType() == "BossOne" || other->getType() == "BossTwo"))
	{
		tmp->setDestroyed(true);
		return true;
	}

	else if (!checkCollision(other))
	{
		return false;
	}
}

CollisionHandler* BulletCollisionHandler::clone() { return new BulletCollisionHandler(); }

