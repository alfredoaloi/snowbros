/*
 * PlayerAction.cpp
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#include "PlayerAction.h"

//PlayerAction::PlayerAction(Player* e) : Action(e) { }

PlayerAction::PlayerAction() { isMoving = false; isShooting = false; }

PlayerAction::~PlayerAction() { }

void PlayerAction::onAction(bool* key)
{
	Actor* tmp = dynamic_cast<Actor*>(entity);

	if(key[KEY_SPACE])
	{
		if((!isShooting && tmp->getLastDirection() == RIGHT) || (!isShooting && tmp->getLastDirection() == NO_DIRECTION_RIGHT))
		{
			tmp->getSpritesheetManager()->selectCurrentSpritesheet("sparaR");
			tmp->setLastDirection(SHOOTING_RIGHT);
		}
		else if((!isShooting && tmp->getLastDirection() == LEFT) || (!isShooting && tmp->getLastDirection() == NO_DIRECTION_LEFT))
		{
			tmp->getSpritesheetManager()->selectCurrentSpritesheet("sparaL");
			tmp->setLastDirection(SHOOTING_LEFT);
		}

		tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		isShooting = true;
	}

	if(!key[KEY_SPACE])
	{
		isShooting = false;
		//lastDirection = NO_DIRECTION;
	}
	if (key[KEY_LEFT] && tmp->getPosX() >= tmp->getSpeed()) {
		if(!isShooting)
		{
			if(!(tmp->getLastDirection() == LEFT))
				tmp->getSpritesheetManager()->selectCurrentSpritesheet("camminaL");
			tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
			tmp->setLastDirection(LEFT);
		}
		else if(isShooting && tmp->getLastDirection() == SHOOTING_RIGHT)
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
		isMoving = true;
	}

	if (key[KEY_RIGHT] && tmp->getPosX() <= screenWidth - tmp->getDim()->x - tmp->getSpeed()) {
		if(!isShooting)
		{
			if(!(tmp->getLastDirection() == RIGHT))
				tmp->getSpritesheetManager()->selectCurrentSpritesheet("camminaR");
			tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
			tmp->setLastDirection(RIGHT);
		}
		else if(isShooting && tmp->getLastDirection() == SHOOTING_LEFT)
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
		isMoving = true;
	}

//	if (tmp->getPosY() <= screenHeight - tmp->getDim()->y - tmp->getMaxHeight() && tmp->isCanFall()) {
//		tmp->setFalling(true);
//		tmp->setCanFall(false);
//		tmp->setCanJump(false);
//		isMoving = true;
//	}

	if (key[KEY_UP] && tmp->isCanJump()) {
		tmp->setJumping(true);
		tmp->setFalling(false);
		tmp->setCanJump(false);
		isMoving = true;
	}

	if(!tmp->isJumping())
		tmp->setFalling(true);

	if (tmp->getPosY() <= screenHeight - tmp->getDim()->y - tmp->getMaxHeight())
	{
		tmp->setJumping(false);
		tmp->setFalling(true);
		isMoving = true;
	}

	if (tmp->isFalling() && tmp->getPosY() <= screenHeight - tmp->getDim()->y - tmp->get_f_speed()) {
		tmp->setPosY(tmp->getPosY() + tmp->get_f_speed());
		tmp->setCanFall(false);
		isMoving = true;
	}

	if (tmp->isJumping() && !tmp->isFalling()) {
		tmp->setPosY(tmp->getPosY() - tmp->get_j_speed());
		isMoving = true;
	}

//	if (tmp->getPosY() >= screenHeight - tmp->getDim()->y) {
//		tmp->setJumping(false);
//		tmp->setFalling(false);
//		//isMoving = true;
//	}

	if((!isMoving && tmp->getLastDirection() == RIGHT) || tmp->getLastDirection() == NO_DIRECTION || (!isMoving && !isShooting && tmp->getLastDirection() == NO_DIRECTION_RIGHT) || (!isMoving && !isShooting && tmp->getLastDirection() == SHOOTING_RIGHT))
	{
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("fermoR");
		tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		tmp->setLastDirection(NO_DIRECTION_RIGHT);
	}
	else if ((!isMoving && tmp->getLastDirection() == LEFT) || (!isMoving && !isShooting && tmp->getLastDirection() == NO_DIRECTION_LEFT) || (!isMoving && !isShooting && tmp->getLastDirection() == SHOOTING_LEFT))
	{
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("fermoL");
		tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		tmp->setLastDirection(NO_DIRECTION_LEFT);
	}

	isMoving = false;
}
