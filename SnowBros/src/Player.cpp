/*
 * Player.cpp
 *
 *  Created on: 17 mar 2019
 *      Author: francesco
 */

#include "Player.h"

Player::Player(float x, float y, float s, float h, float f_s, float j_s, ALLEGRO_BITMAP* bit) : Actor(x, y, s, h, f_s, j_s, bit)
{}

Player::~Player() {
	al_destroy_bitmap(bitmap);
}

void Player::onAction(bool key[4]) {
	if (key[KEY_UP] && !jumping) {
		jumping = true;
	}

	/*if (key[KEY_DOWN] && pos_y <= 2160 - dim - 4.0) {
	 pos_y += 15.0;
	 }*/

	if (key[KEY_LEFT] && pos_x >= 15.0) {
		pos_x -= 15.0;
	}

	if (key[KEY_RIGHT] && pos_x <= 3840 - dim - 15.0) {
		pos_x += 15.0;
	}

	if (jumping && !falling && pos_y >= 2160 - dim - max_height) {
		pos_y -= j_speed;
	}

	if (pos_y <= 2160 - dim - max_height) {
		falling = true;
	}

	if (falling && pos_y <= 2160 - dim - f_speed) {
		pos_y += f_speed;
	}

	if (pos_y >= 2160 - dim) {
		jumping = false;
		falling = false;
	}
}

void Player::onRedraw() {
	al_draw_bitmap(bitmap, pos_x, pos_y, 0);
}
