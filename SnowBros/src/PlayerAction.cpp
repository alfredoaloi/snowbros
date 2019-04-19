/*
 * PlayerAction.cpp
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#include "PlayerAction.h"

PlayerAction::PlayerAction(Player* e) : Action(e) { }

PlayerAction::PlayerAction() { }

PlayerAction::~PlayerAction() { }

void PlayerAction::onAction(bool* key)
{
	Player* tmp = dynamic_cast<Player* >(entity);
	if (key[KEY_UP] && !tmp->jumping) {
		tmp->jumping = true;
	}

	if (key[KEY_LEFT] && tmp->pos_x >= tmp->speed) {
		tmp->pos_x -= tmp->speed;
	}

	if (key[KEY_RIGHT] && tmp->pos_x <= screenWidth - tmp->dim.x - tmp->speed) {
		tmp->pos_x += tmp->speed;
	}

	if (tmp->jumping && !tmp->falling && tmp->pos_y >= screenHeight - tmp->dim.y - tmp->max_height) {
		tmp->pos_y -= tmp->j_speed;
	}

	if (tmp->pos_y <= screenHeight - tmp->dim.y - tmp->max_height) {
		tmp->falling = true;
	}

	if (tmp->falling && tmp->pos_y <= screenHeight - tmp->dim.y - tmp->f_speed) {
		tmp->pos_y += tmp->f_speed;
	}

	if (tmp->pos_y >= screenHeight - tmp->dim.y) {
		tmp->jumping = false;
		tmp->falling = false;
	}
}
