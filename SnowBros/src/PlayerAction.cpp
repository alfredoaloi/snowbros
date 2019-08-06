/*
 * PlayerAction.cpp
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#include "PlayerAction.h"

//PlayerAction::PlayerAction(Player* e) : Action(e) { }

PlayerAction::PlayerAction() { isMoving = false; isShooting = false; lastDirection = NO_DIRECTION; }

PlayerAction::~PlayerAction() { }

void PlayerAction::onAction(bool* key)
{
	Actor* tmp = dynamic_cast<Actor* >(entity);

	if(key[KEY_SPACE])
	{
		if((!isShooting && lastDirection == RIGHT) || (!isShooting && lastDirection == NO_DIRECTION_RIGHT))
			tmp->getSpritesheetManager()->selectCurrentSpritesheet("sparaR");
		else if((!isShooting && lastDirection == LEFT) || (!isShooting && lastDirection == NO_DIRECTION_LEFT))
			tmp->getSpritesheetManager()->selectCurrentSpritesheet("sparaL");

		tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		isShooting = true;
	}

	if(!key[KEY_SPACE])
	{
		isShooting = false;
		//lastDirection = NO_DIRECTION;
	}

	if (key[KEY_UP] && !tmp->isJumping()) {
		tmp->setJumping(true);
		isMoving = true;
	}
	if (key[KEY_LEFT] && tmp->getPosX() >= tmp->getSpeed()) {
		if(!isShooting)
		{
			if(!(lastDirection == LEFT))
				tmp->getSpritesheetManager()->selectCurrentSpritesheet("camminaL");
			tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		}

		tmp->setPosX(tmp->getPosX() - tmp->getSpeed());
		isMoving = true;
		lastDirection = LEFT;
	}

	if (key[KEY_RIGHT] && tmp->getPosX() <= screenWidth - tmp->getDim().x - tmp->getSpeed()) {
		if(!isShooting)
		{
			if(!(lastDirection == RIGHT))
				tmp->getSpritesheetManager()->selectCurrentSpritesheet("camminaR");
			tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		}

		tmp->setPosX(tmp->getPosX() + tmp->getSpeed());
		isMoving = true;
		lastDirection = RIGHT;
	}

	if (tmp->isJumping() && !tmp->isFalling() && tmp->getPosY() >= screenHeight - tmp->getDim().y - tmp->getMaxHeight()) {
		tmp->setPosY(tmp->getPosY() - tmp->get_j_speed());
		isMoving = true;
	}

	if (tmp->getPosY() <= screenHeight - tmp->getDim().y - tmp->getMaxHeight()) {
		tmp->setFalling(true);
		isMoving = true;
	}

	if (tmp->isFalling() && tmp->getPosY() <= screenHeight - tmp->getDim().y - tmp->get_f_speed()) {
		tmp->setPosY(tmp->getPosY() + tmp->get_f_speed());
		isMoving = true;
	}

	if (tmp->getPosY() >= screenHeight - tmp->getDim().y) {
		tmp->setJumping(false);
		tmp->setFalling(false);
		//isMoving = true;
	}

	if((!isMoving && lastDirection == RIGHT) || lastDirection == NO_DIRECTION || (!isMoving && !isShooting && lastDirection == NO_DIRECTION_RIGHT))
	{
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("fermoR");
		tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		lastDirection = NO_DIRECTION_RIGHT;
	}
	else if ((!isMoving && lastDirection == LEFT) || (!isMoving && !isShooting && lastDirection == NO_DIRECTION_LEFT))
	{
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("fermoL");
		tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		lastDirection = NO_DIRECTION_LEFT;
	}

	isMoving = false;
}
