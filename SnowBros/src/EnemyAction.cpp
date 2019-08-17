/*
 * EnemyAction.cpp
 *
 *  Created on: 17 ago 2019
 *      Author: laolr
 */

#include "EnemyAction.h"
#include <iostream>

EnemyAction::EnemyAction() {
	// TODO Auto-generated constructor stub

}

EnemyAction::~EnemyAction() {
	// TODO Auto-generated destructor stub
}

void EnemyAction::onAction(bool* key)
{
	Actor* tmp = dynamic_cast<Actor*>(entity);
	int x = rand() % 4;
	randAction action;
	switch (x) {
		case 0:
			action = left;
			break;
		case 1:
			action = right;
			break;
		case 2:
			action = up;
			break;
		case 3:
			if (tmp->getType() == "Enemy2")
				action = shoot;
			else
				action = fermo;
			break;
	}

	tmp->setSpawning(false);
	tmp->setShooting(false);

	if (!tmp->isJumping())
	{
		tmp->setMaxHeight(tmp->getPosY() - 32);
	}

	if(action == shoot)
	{
		if((!tmp->isShooting() && tmp->getLastDirection() == RIGHT) || (!tmp->isShooting() && tmp->getLastDirection() == NO_DIRECTION_RIGHT) || (!tmp->isShooting() && tmp->getLastDirection() == JUMPING_RIGHT) || (!tmp->isShooting() && tmp->getLastDirection() == FALLING_RIGHT))
		{
			tmp->getSpritesheetManager()->selectCurrentSpritesheet("sparaR");
			tmp->setLastDirection(SHOOTING_RIGHT);
		}
		else if((!tmp->isShooting() && tmp->getLastDirection() == LEFT) || (!tmp->isShooting() && tmp->getLastDirection() == NO_DIRECTION_LEFT) || (!tmp->isShooting() && tmp->getLastDirection() == JUMPING_LEFT) || (!tmp->isShooting() && tmp->getLastDirection() == FALLING_LEFT))
		{
			tmp->getSpritesheetManager()->selectCurrentSpritesheet("sparaL");
			tmp->setLastDirection(SHOOTING_LEFT);
		}

		if(!tmp->isJumping() && !tmp->isFalling())
		{
			tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
			tmp->setShooting(true);
			if (tmp->getLastDirection() == SHOOTING_LEFT)
				tmp->getSpawner()->spawnEntity("FL", tmp->getPosX(), tmp->getPosY());
			if (tmp->getLastDirection() == SHOOTING_RIGHT)
				tmp->getSpawner()->spawnEntity("FR", tmp->getPosX() + tmp->getDim()->x, tmp->getPosY());
		}
	}

	if(!(action == shoot))
	{
		tmp->setShooting(false);
	}

	if (action == left && tmp->getPosX() >= tmp->getSpeed())
	{
		if(!tmp->isShooting() && !tmp->isJumping())
		{
			if(!(tmp->getLastDirection() == LEFT))
				tmp->getSpritesheetManager()->selectCurrentSpritesheet("camminaL");
			tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
			tmp->setLastDirection(LEFT);
		}
		else if(tmp->isShooting() && tmp->getLastDirection() == SHOOTING_RIGHT)
		{
			tmp->getSpritesheetManager()->selectCurrentSpritesheet("sparaL");
			tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
			tmp->setLastDirection(SHOOTING_LEFT);
		}
		else
		{
			tmp->setLastDirection(SHOOTING_LEFT);
		}

		tmp->setPosX(tmp->getPosX() - tmp->getSpeed());
		tmp->setMoving(true);
	}

	if (action == right && tmp->getPosX() <= screenWidth - tmp->getDim()->x - tmp->getSpeed()) {
		if(!tmp->isShooting() && !tmp->isJumping())
		{
			if(!(tmp->getLastDirection() == RIGHT))
				tmp->getSpritesheetManager()->selectCurrentSpritesheet("camminaR");
			tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
			tmp->setLastDirection(RIGHT);
		}
		else if(tmp->isShooting() && tmp->getLastDirection() == SHOOTING_LEFT)
		{
			tmp->getSpritesheetManager()->selectCurrentSpritesheet("sparaR");
			tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
			tmp->setLastDirection(SHOOTING_RIGHT);
		}
		else
		{
			tmp->setLastDirection(SHOOTING_RIGHT);
		}

		tmp->setPosX(tmp->getPosX() + tmp->getSpeed());
		tmp->setMoving(true);
	}

	if (action == up && tmp->isCanJump()) {
		tmp->setJumping(true);
		tmp->setFalling(false);
		tmp->setCanJump(false);
		if(tmp->getLastDirection() == RIGHT || tmp->getLastDirection() == NO_DIRECTION_RIGHT || tmp->getLastDirection() == SHOOTING_RIGHT)
		{
			tmp->getSpritesheetManager()->selectCurrentSpritesheet("saltaR");
			tmp->setLastDirection(JUMPING_RIGHT);
		}
		else if(tmp->getLastDirection() == LEFT || tmp->getLastDirection() == NO_DIRECTION_LEFT || tmp->getLastDirection() == SHOOTING_LEFT)
		{
			tmp->getSpritesheetManager()->selectCurrentSpritesheet("saltaL");
			tmp->setLastDirection(JUMPING_LEFT);
		}
		tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		tmp->setShooting(false);
		tmp->setMoving(true);
	}

	if(!tmp->isJumping())
		tmp->setFalling(true);

	if (tmp->getPosY() <= tmp->getMaxHeight())
	{
		tmp->setJumping(false);
		tmp->setCanJump(false);
		tmp->setFalling(true);
	}

	if (tmp->isFalling() && tmp->getPosY() <= screenHeight - tmp->getDim()->y - tmp->get_f_speed()) {
		tmp->setPosY(tmp->getPosY() + tmp->get_f_speed());
		tmp->setCanFall(false);
		tmp->setCanJump(false);
	}

	if (tmp->isJumping() && !tmp->isFalling()) {
		tmp->setPosY(tmp->getPosY() - tmp->get_j_speed());
		tmp->setMoving(true);
	}

	if((!tmp->isMoving() && tmp->getLastDirection() == RIGHT) || tmp->getLastDirection() == NO_DIRECTION || (!tmp->isMoving() && !tmp->isShooting() && tmp->getLastDirection() == NO_DIRECTION_RIGHT) || (!tmp->isMoving() && !tmp->isShooting() && tmp->getLastDirection() == SHOOTING_RIGHT) || (!tmp->isMoving() && !tmp->isShooting() && tmp->getLastDirection() == JUMPING_RIGHT) || (!tmp->isMoving() && !tmp->isShooting() && tmp->getLastDirection() == FALLING_RIGHT))
	{
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("fermoR");
		tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		tmp->setLastDirection(NO_DIRECTION_RIGHT);
	}
	else if ((!tmp->isMoving() && tmp->getLastDirection() == LEFT) || (!tmp->isMoving() && !tmp->isShooting() && tmp->getLastDirection() == NO_DIRECTION_LEFT) || (!tmp->isMoving() && !tmp->isShooting() && tmp->getLastDirection() == SHOOTING_LEFT) || (!tmp->isMoving() && !tmp->isShooting() && tmp->getLastDirection() == JUMPING_LEFT) || (!tmp->isMoving() && !tmp->isShooting() && tmp->getLastDirection() == FALLING_LEFT))
	{
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("fermoL");
		tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		tmp->setLastDirection(NO_DIRECTION_LEFT);
	}

	tmp->setMoving(false);
}

Action* EnemyAction::clone() { return new EnemyAction(); }
