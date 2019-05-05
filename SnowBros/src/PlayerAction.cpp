/*
 * PlayerAction.cpp
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#include "PlayerAction.h"

//PlayerAction::PlayerAction(Player* e) : Action(e) { }

PlayerAction::PlayerAction() { }

PlayerAction::~PlayerAction() { }

void PlayerAction::onAction(bool* key)
{
	Actor* tmp = dynamic_cast<Actor* >(entity);
	if (key[KEY_UP] && !tmp->isJumping()) {
		tmp->setJumping(true);
	}

	if (key[KEY_LEFT] && tmp->getPosX() >= tmp->getSpeed()) {
		tmp->setPosX(tmp->getPosX() - tmp->getSpeed());
	}

	if (key[KEY_RIGHT] && tmp->getPosX() <= screenWidth - tmp->getDim().x - tmp->getSpeed()) {
		tmp->setPosX(tmp->getPosX() + tmp->getSpeed());
	}

	if (tmp->isJumping() && !tmp->isFalling() && tmp->getPosY() >= screenHeight - tmp->getDim().y - tmp->getMaxHeight()) {
		tmp->setPosY(tmp->getPosY() - tmp->get_j_speed());
	}

	if (tmp->getPosY() <= screenHeight - tmp->getDim().y - tmp->getMaxHeight()) {
		tmp->setFalling(true);
	}

	if (tmp->isFalling() && tmp->getPosY() <= screenHeight - tmp->getDim().y - tmp->get_f_speed()) {
		tmp->setPosY(tmp->getPosY() + tmp->get_f_speed());
	}

	if (tmp->getPosY() >= screenHeight - tmp->getDim().y) {
		tmp->setJumping(false);
		tmp->setFalling(false);
	}
}
