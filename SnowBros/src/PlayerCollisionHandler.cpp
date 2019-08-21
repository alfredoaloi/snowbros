/*
 * PlayerCollisionHandler.cpp
 *
 *  Created on: 9 ago 2019
 *      Author: Francesco
 */

#include "PlayerCollisionHandler.h"

PlayerCollisionHandler::PlayerCollisionHandler() { }

PlayerCollisionHandler::~PlayerCollisionHandler() { }

bool PlayerCollisionHandler::handleCollision(Entity* other)
{
	if(!checkCollision(other))
	{
		return false;
	}

	Actor* tmp = dynamic_cast<Actor*>(entity);
	if(checkCollision(other) == SIDE_DOWN && (other->getType() == "T" || other->getType() == "TL" || other->getType() == "TR") && tmp->isFalling())
	{
//		double tmp_x1 = tmp->getPosX();
//		double tmp_y1 = tmp->getPosY();
//
//		double tmp_x2 = tmp_x1 + tmp->getDim()->x;
//		double tmp_y2 = tmp_y1;
//
//		double tmp_x3 = tmp_x1;
//		double tmp_y3 = tmp_y1 + tmp->getDim()->y;
//
//		double tmp_x4 = tmp_x2;
//		double tmp_y4 = tmp_y3;
//
//		double other_x1 = other->getPosX();
//		double other_y1 = other->getPosY();
//
//		double other_x2 = other_x1 + other->getDim()->x;
//		double other_y2 = other_y1;
//
//		double other_x3 = other_x1;
//		double other_y3 = other_y1 + other->getDim()->y;
//
//		double other_x4 = other_x2;
//		double other_y4 = other_y3;
//
//		double dist = sqrt(pow(tmp_x3 - other_x1, 2) + pow(tmp_y3 - other_y1, 2));

		tmp->setPosY(other->getPosY() - tmp->getDim()->y);
		tmp->setCanJump(true);
		tmp->setFalling(false);
	}

	if(checkCollision(other) == SIDE_LEFT && other->getType() == "TR" && tmp->isFalling() && !tmp->isJumping())
	{
		tmp->setPosX(other->getPosX() + other->getDim()->x);
	}

	if(checkCollision(other) == SIDE_RIGHT && other->getType() == "TL" && tmp->isFalling() && !tmp->isJumping())
	{
		tmp->setPosX(other->getPosX() - tmp->getDim()->x);
	}

	if (checkCollision(other) && !(tmp->isSpawning()) && (other->getType() == "Enemy1" || other->getType() == "Enemy2" || other->getType() == "Enemy3" || other->getType() == "BossOne" || other->getType() == "BossTwo" || other->getType() == "MinionOne" || other->getType() == "MinionTwo" || other->getType() == "FireLeft" || other->getType() == "FireRight"))
	{
		Actor* tmp2 = dynamic_cast<Actor*>(other);
		if (tmp2->getLivelloPalla() == NULLA && !tmp->getImmobile() && !tmp2->getImmobile() && !tmp->getInvincibile())
		{
			tmp->setImmobile(true);
			tmp->setLastDirection(SPAWN);
		}
	}

	if (checkCollision(other) == SIDE_LEFT && (other->getType() == "Enemy1" || other->getType() == "Enemy2" || other->getType() == "Enemy3"))
	{
		Actor* tmp2 = dynamic_cast<Actor*>(other);
		if (tmp2->getLivelloPalla() == PIENA)
		{
			tmp->setSpinge(true);
			if (tmp->isShooting())
			{
				tmp2->setLivelloPalla(ROTOLA);
				tmp2->setLastDirection(ROTOLA_LEFT);
				tmp2->setSpeed(9);
				tmp2->getSpritesheetManager()->selectCurrentSpritesheet("rotola");
			}
			else if (tmp2->getPosX() <= 0)
			{
				tmp2->setPosX(0);
				tmp->setPosX(tmp2->getDim()->x);
			}
			else
				tmp2->setPosX(tmp->getPosX() - tmp2->getDim()->x);
		}
	}

	if (checkCollision(other) == SIDE_RIGHT && (other->getType() == "Enemy1" || other->getType() == "Enemy2" || other->getType() == "Enemy3"))
	{
		Actor* tmp2 = dynamic_cast<Actor*>(other);
		if (tmp2->getLivelloPalla() == PIENA)
		{
			tmp->setSpinge(true);
			if (tmp->isShooting())
			{
				tmp2->setLivelloPalla(ROTOLA);
				tmp2->setLastDirection(ROTOLA_RIGHT);
				tmp2->setSpeed(9);
				tmp2->getSpritesheetManager()->selectCurrentSpritesheet("rotola");
			}
			else if (tmp2->getPosX() + tmp2->getDim()->x >= screenWidth)
			{
				tmp2->setPosX(screenWidth - tmp2->getDim()->x);
				tmp->setPosX(tmp2->getPosX() - tmp->getDim()->x);
			}
			else
				tmp2->setPosX(tmp->getPosX() + tmp->getDim()->x);
		}
	}

	if (checkCollision(other) && other->getType() == "Powerup")
	{
		other->setDestroyed(true);
		tmp->setMaxGittata(100);
		PlayerScore* p = PlayerScore::getInstance();
		p->addScore(100);
	}

	return true;
}

CollisionHandler* PlayerCollisionHandler::clone() { return new PlayerCollisionHandler(); }

