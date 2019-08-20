/*
 * PlayerAction.cpp
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#include "PlayerAction.h"

//PlayerAction::PlayerAction(Player* e) : Action(e) { }

PlayerAction::PlayerAction() { spawnCounter = 0; }

PlayerAction::~PlayerAction() { }

void PlayerAction::onAction(bool* key)
{
	Actor* tmp = dynamic_cast<Actor*>(entity);

	if(!tmp->isSpawning())
	{
		if (!tmp->isJumping())
		{
			tmp->setMaxHeight(tmp->getPosY() - 32);
		}

		if (key[KEY_LEFT] && tmp->getPosX() >= tmp->getSpeed()) {
			if(!tmp->isShooting() && !tmp->isJumping() && !tmp->getSpinge())
			{
				if(!(tmp->getLastDirection() == LEFT))
					tmp->getSpritesheetManager()->selectCurrentSpritesheet("camminaL");
				tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
				tmp->setLastDirection(LEFT);
			}
			else if(!tmp->isShooting() && !tmp->isJumping() && tmp->getSpinge())
			{
				tmp->getSpritesheetManager()->selectCurrentSpritesheet("spingeL");
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

		if (key[KEY_RIGHT] && tmp->getPosX() <= screenWidth - tmp->getDim()->x - tmp->getSpeed()) {
			if(!tmp->isShooting() && !tmp->isJumping() && !tmp->getSpinge())
			{
				if(!(tmp->getLastDirection() == RIGHT))
					tmp->getSpritesheetManager()->selectCurrentSpritesheet("camminaR");
				tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
				tmp->setLastDirection(RIGHT);
			}
			else if(!tmp->isShooting() && !tmp->isJumping() && tmp->getSpinge())
			{
				tmp->getSpritesheetManager()->selectCurrentSpritesheet("spingeR");
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

		if(key[KEY_SPACE])
		{
			if (tmp->getSpinge())
				tmp->setShooting(true);
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
					if (tmp->getMaxGittata() == 100)
						tmp->getSpawner()->spawnEntity("BPL", tmp->getPosX(), tmp->getPosY() + tmp->getDim()->y/2);
					else
						tmp->getSpawner()->spawnEntity("BL", tmp->getPosX(), tmp->getPosY() + tmp->getDim()->y/2);
				if (tmp->getLastDirection() == SHOOTING_RIGHT)
					if (tmp->getMaxGittata() == 100)
						tmp->getSpawner()->spawnEntity("BPR", tmp->getPosX(), tmp->getPosY() + tmp->getDim()->y/2);
					else
						tmp->getSpawner()->spawnEntity("BR", tmp->getPosX(), tmp->getPosY() + tmp->getDim()->y/2);			}
		}

		if(!key[KEY_SPACE])
		{
			tmp->setShooting(false);
			//lastDirection = NO_DIRECTION;
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
		//		isMoving = true;
		}

		if (tmp->isFalling() && tmp->getPosY() <= screenHeight - tmp->getDim()->y - tmp->get_f_speed()) {
			tmp->setPosY(tmp->getPosY() + tmp->get_f_speed());
			tmp->setCanFall(false);
			tmp->setCanJump(false);
		//		isMoving = true;
		}

		if (tmp->isJumping() && !tmp->isFalling()) {
			tmp->setPosY(tmp->getPosY() - tmp->get_j_speed());
			tmp->setMoving(true);
		}

		//	if (tmp->getPosY() >= screenHeight - tmp->getDim()->y) {
		//		tmp->setJumping(false);
		//		tmp->setFalling(false);
		//		//isMoving = true;
		//	}

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
	}

	else
	{
		if(!tmp->isJumping())
			tmp->setFalling(true);

		if (tmp->isFalling() && tmp->getPosY() <= screenHeight - tmp->getDim()->y - tmp->get_f_speed()) {
			tmp->setPosY(tmp->getPosY() + tmp->get_f_speed());
			tmp->setCanFall(false);
			tmp->setCanJump(false);
		//		isMoving = true;
		}

		if(spawnCounter > 24)
			tmp->setSpawning(false);
		if(spawnCounter % 6 == 0 && spawnCounter != 24)
		{
			if(tmp->getLastDirection() == SPAWN)
			{
				tmp->getSpritesheetManager()->selectCurrentSpritesheet("respawn");
				tmp->setLastDirection(NO_DIRECTION);
			}
			tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
		}
		spawnCounter++;
	}

	tmp->setSpinge(false);
	tmp->setMoving(false);
}

Action* PlayerAction::clone() { return new PlayerAction(); }
