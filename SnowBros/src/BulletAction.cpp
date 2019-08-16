/*
 * BulletAction.cpp
 *
 *  Created on: 16 ago 2019
 *      Author: laolr
 */

#include "BulletAction.h"
#include <iostream>

BulletAction::BulletAction() {
}

BulletAction::~BulletAction() {
}

void BulletAction::onAction(bool* key) {
	// MAXhEIGT VIENE IDENTIFICATO COME LA MASSIMA DISTANZA IN TERMINI DI X PRIMA CHE IL PROIETTILE INIZI A CADERE
	Actor* tmp = dynamic_cast<Actor*>(entity);

	if (tmp->getType() == "BulletLeft" && !(tmp->getLastDirection() == LEFT) && !(tmp->getLastDirection() == DOWN))
	{
		tmp->setLastDirection(LEFT);
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("left");
		tmp->setMaxHeight(tmp->getPosX() - 100);
	}

	else if (tmp->getType() == "BulletRight" && !(tmp->getLastDirection() == RIGHT) && !(tmp->getLastDirection() == DOWN))
	{
		tmp->setLastDirection(RIGHT);
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("right");
		tmp->setMaxHeight(tmp->getPosX() + 100);
	}

	if (tmp->getLastDirection() == LEFT && tmp->getPosX() > tmp->getMaxHeight())
	{
		tmp->setPosX(tmp->getPosX() - tmp->getSpeed());
	}

	if (tmp->getLastDirection() == RIGHT && tmp->getPosX() < tmp->getMaxHeight())
	{
		tmp->setPosX(tmp->getPosX() + tmp->getSpeed());
	}

	if (tmp->getLastDirection() == LEFT && tmp->getPosX() < tmp->getMaxHeight())
	{
		tmp->setLastDirection(DOWN);
	}

	if (tmp->getLastDirection() == RIGHT && tmp->getPosX() > tmp->getMaxHeight())
	{
		tmp->setLastDirection(DOWN);
	}

	if (tmp->getLastDirection() == DOWN)
	{
		tmp->setPosY(tmp->getPosY() + tmp->getSpeed());
	}

	tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
}

Action* BulletAction::clone() { return new BulletAction(); }
