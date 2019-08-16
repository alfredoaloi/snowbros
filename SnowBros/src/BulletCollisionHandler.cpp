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
		// dovrebbe essere distrutta
		return true;
	}

	else if (checkCollision(other) && other->getType() == "Enemy")
	{
		// palla di neve e cazzi vari
		return true;
	}

	else if (!checkCollision(other))
	{
		return false;
	}
}
