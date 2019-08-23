/*
 * EnemyCollisionHandler.cpp
 *
 *  Created on: 17 ago 2019
 *      Author: laolr
 */

#include "EnemyCollisionHandler.h"

EnemyCollisionHandler::EnemyCollisionHandler() {
	soundBank = SoundBank::getInstance();
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

	if (checkCollision(other) && (other->getType() == "BulletLeft" || other->getType() == "BulletRight" || other->getType() == "BulletPLeft" || other->getType() == "BulletPRight") && !(tmp->getLivelloPalla() == ROTOLA))
	{
		tmp->setImmobile(true);
		tmp->setLastDirection(NO_DIRECTION);
		if (tmp->getLivelloPalla() == NULLA)
			tmp->setLivelloPalla(POCA);
		else if (tmp->getLivelloPalla() == POCA)
			tmp->setLivelloPalla(TANTA);
		else if (tmp->getLivelloPalla() == TANTA)
			tmp->setLivelloPalla(PIENA);
	}

	if(checkCollision(other) == SIDE_LEFT && other->getType() == "TR" && tmp->isFalling() && !tmp->isJumping() && tmp->getLivelloPalla() == NULLA)
	{
		tmp->setPosX(other->getPosX() + other->getDim()->x);
	}

	if(checkCollision(other) == SIDE_LEFT && other->getType() == "TR" && tmp->isFalling() && !tmp->isJumping() && tmp->getLivelloPalla() == NULLA)
	{
		tmp->setPosX(other->getPosX() + other->getDim()->x);
	}

	if(checkCollision(other) == SIDE_LEFT && other->getType() == "TR" && tmp->isFalling() && !tmp->isJumping() && tmp->getLivelloPalla() == ROTOLA)
	{
		tmp->setPosX(other->getPosX() + other->getDim()->x);
		tmp->setLastDirection(ROTOLA_RIGHT);
	}

	if(checkCollision(other) == SIDE_RIGHT && other->getType() == "TL" && tmp->isFalling() && !tmp->isJumping() && tmp->getLivelloPalla() == ROTOLA)
	{
		tmp->setPosX(other->getPosX() - tmp->getDim()->x);
		tmp->setLastDirection(ROTOLA_LEFT);
	}

	if (checkCollision(other) && tmp->getLivelloPalla() == ROTOLA && (other->getType() == "Enemy1" || other->getType() == "Enemy2" || other->getType() == "Enemy3" || other->getType() == "MinionOne" || other->getType() == "MinionTwo" || other->getType() == "BossOne" || other->getType() == "BossTwo"))
	{
		Actor* tmp2 = dynamic_cast<Actor*>(other);
		if (tmp2->getType() == "BossOne" || tmp2->getType() == "BossTwo")
		{
			soundBank->playSample("delball");
			tmp2->setVita(tmp2->getVita() - 10);
			tmp->setDestroyed(true);
			PlayerScore* p = PlayerScore::getInstance();
			p->addScore(500);
		}

		else if (!(tmp2->getLivelloPalla() == ROTOLA))
		{
			soundBank->playSample("enemy_ball");
			if (tmp2->getLastDirection() == LEFT)
				tmp2->setLastDirection(NO_DIRECTION_LEFT);
			else
				tmp2->setLastDirection(NO_DIRECTION_RIGHT);
			tmp2->setImmobile(true);
			tmp2->setSpawning(true);
			tmp2->setPosY(tmp2->getPosY() - 20);
		}
	}

	return true;
}

CollisionHandler* EnemyCollisionHandler::clone() { return new EnemyCollisionHandler(); }
