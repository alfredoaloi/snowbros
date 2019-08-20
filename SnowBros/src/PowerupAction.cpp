/*
 * PowerupAction.cpp
 *
 *  Created on: 20 ago 2019
 *      Author: laolr
 */

#include "PowerupAction.h"

PowerupAction::PowerupAction() {
	// TODO Auto-generated constructor stub

}

PowerupAction::~PowerupAction() {
	// TODO Auto-generated destructor stub
}

void PowerupAction::onAction(bool* key) {
	Actor* tmp = dynamic_cast<Actor*>(entity);

	tmp->setFalling(true);

	if (tmp->isFalling())
	{
		tmp->setPosY(tmp->getPosY() + tmp->getSpeed());
	}

	tmp->getSpritesheetManager()->selectCurrentSpritesheet("powerup");
	tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
}

Action* PowerupAction::clone() { return new PowerupAction(); }
