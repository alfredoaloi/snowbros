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

	if (tmp->getType() == "BulletPLeft" || tmp->getType() == "BulletPRight")
		tmp->setMaxGittata(100);

	if ((tmp->getType() == "BulletLeft" || tmp->getType() == "BulletPLeft" || tmp->getType() == "FireLeft") && !(tmp->getLastDirection() == LEFT) && !(tmp->getLastDirection() == DOWN))
	{
		tmp->setLastDirection(LEFT);
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("left");
		tmp->setGittata(tmp->getPosX() - tmp->getMaxGittata());
	}

	else if ((tmp->getType() == "BulletRight" || tmp->getType() == "BulletPRight" || tmp->getType() == "FireRight") && !(tmp->getLastDirection() == RIGHT) && !(tmp->getLastDirection() == DOWN))
	{
		tmp->setLastDirection(RIGHT);
		tmp->getSpritesheetManager()->selectCurrentSpritesheet("right");
		tmp->setGittata(tmp->getPosX() + tmp->getMaxGittata());
	}

	if (tmp->getType() == "BulletLeft" || tmp->getType() == "BulletRight" || tmp->getType() == "BulletPLeft" || tmp->getType() == "BulletPRight")
	{
		if (tmp->getLastDirection() == LEFT && tmp->getPosX() > tmp->getGittata())
		{
			tmp->setPosX(tmp->getPosX() - tmp->getSpeed());
		}

		if (tmp->getLastDirection() == RIGHT && tmp->getPosX() < tmp->getGittata())
		{
			tmp->setPosX(tmp->getPosX() + tmp->getSpeed());
		}

		if (tmp->getLastDirection() == LEFT && tmp->getPosX() < tmp->getGittata())
		{
			tmp->setLastDirection(DOWN);
		}

		if (tmp->getLastDirection() == RIGHT && tmp->getPosX() > tmp->getGittata())
		{
			tmp->setLastDirection(DOWN);
		}

		if (tmp->getLastDirection() == DOWN)
		{
			tmp->setPosY(tmp->getPosY() + tmp->getSpeed());
		}
	}
	else
	{
		if (tmp->getLastDirection() == LEFT)
		{
			tmp->setPosX(tmp->getPosX() - tmp->getSpeed());
		}

		if (tmp->getLastDirection() == RIGHT)
		{
			tmp->setPosX(tmp->getPosX() + tmp->getSpeed());
		}
	}

	tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
}

Action* BulletAction::clone() { return new BulletAction(); }
