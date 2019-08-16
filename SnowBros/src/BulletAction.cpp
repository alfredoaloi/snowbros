/*
 * BulletAction.cpp
 *
 *  Created on: 16 ago 2019
 *      Author: laolr
 */

#include "BulletAction.h"

BulletAction::BulletAction() {
}

BulletAction::~BulletAction() {
}

void BulletAction::onAction(bool* key) {
	// MAXhEIGT VIENE IDENTIFICATO COME LA MASSIMA DISTANZA IN TERMINI DI X PRIMA CHE IL PROIETTILE INIZI A CADERE
	Actor* tmp = dynamic_cast<Actor*>(entity);

	if (tmp->getLastDirection() == LEFT && spawn)
	{
		spawn = false;
		tmp->setMaxHeight(tmp->getPosX() - 100);
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("left");
	}

	if (tmp->getLastDirection() == RIGHT && spawn)
	{
		spawn = false;
		tmp->setMaxHeight(tmp->getPosX() + 100);
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("right");
	}

	if (tmp->getLastDirection() == LEFT && tmp->getPosX() > tmp->getMaxHeight())
	{
		tmp->setPosX(tmp->getPosX() - tmp->getSpeed());
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("left");
	}

	if (tmp->getLastDirection() == RIGHT && tmp->getPosX() < tmp->getMaxHeight())
	{
		tmp->setPosX(tmp->getPosX() + tmp->getSpeed());
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("right");
	}

	if (tmp->getLastDirection() == LEFT && tmp->getPosX() < tmp->getMaxHeight())
	{
		tmp->setLastDirection(DOWN);
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("left");
	}

	if (tmp->getLastDirection() == RIGHT && tmp->getPosX() > tmp->getMaxHeight())
	{
		tmp->setLastDirection(DOWN);
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("right");
	}

	if (tmp->getLastDirection() == DOWN)
	{
		tmp->setPosY(tmp->getPosY() + tmp->getSpeed());
	}
}
