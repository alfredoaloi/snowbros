#include "Player.h"

Player::Player(float x, float y, Dimensions d, float s, float h, float f_s, float j_s,
		ALLEGRO_BITMAP* bit, Action* a) :
		Actor(x, y, d, s, h, f_s, j_s, bit, a) {
}

Player::~Player() {
	al_destroy_bitmap(bitmap);
}

/*void Player::onAction(bool key[4]) {
	if (key[KEY_UP] && !jumping) {
		jumping = true;
	}

	if (key[KEY_LEFT] && pos_x >= speed) {
		pos_x -= speed;
	}

	if (key[KEY_RIGHT] && pos_x <= screenWidth - dim.x - speed) {
		pos_x += speed;
	}

	if (jumping && !falling && pos_y >= screenHeight - dim.y - max_height) {
		pos_y -= j_speed;
	}

	if (pos_y <= screenHeight - dim.y - max_height) {
		falling = true;
	}

	if (falling && pos_y <= screenHeight - dim.y - f_speed) {
		pos_y += f_speed;
	}

	if (pos_y >= screenHeight - dim.y) {
		jumping = false;
		falling = false;
	}
}*/

void Player::onRedraw() {
	al_draw_bitmap(bitmap, pos_x, pos_y, 0);
}
