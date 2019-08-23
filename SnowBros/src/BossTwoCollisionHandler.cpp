/*
 * BossTwoCollisionHandler.cpp
 *
 *  Created on: 23 ago 2019
 *      Author: laolr
 */

#include "BossTwoCollisionHandler.h"

BossTwoCollisionHandler::BossTwoCollisionHandler() {
	// TODO Auto-generated constructor stub

}

BossTwoCollisionHandler::~BossTwoCollisionHandler() {
	// TODO Auto-generated destructor stub
}

bool BossTwoCollisionHandler::handleCollision(Entity* other)
{
	Actor* tmp = dynamic_cast<Actor*>(entity);

	if (!checkCollision(other))
	{
		return false;
	}

	if (checkCollision(other) == SIDE_DOWN && (other->getType() == "T" || other->getType() == "TL" || other->getType() == "TR"))
	{
		tmp->setPosY(other->getPosY() - tmp->getDim()->y);
		tmp->setCanJump(true);
		tmp->setFalling(false);
	}

	if (checkCollision(other) && (other->getType() == "BulletLeft" || other->getType() == "BulletRight"))
	{
		tmp->setVita(tmp->getVita() - 1);
		PlayerScore* playerScore = PlayerScore::getInstance();
		playerScore->addScore(50);
	}

	return true;
}

CollisionHandler* BossTwoCollisionHandler::clone() { return new BossTwoCollisionHandler(); }
