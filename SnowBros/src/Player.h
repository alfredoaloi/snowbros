/*
 * Player.h
 *
 *  Created on: 17 mar 2019
 *      Author: francesco
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Actor.h"

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

class Player : public Actor {
	bool jumping = false;
	bool falling = false;
public:
	Player(float x, float, float, float, float, float, ALLEGRO_BITMAP*);
	~Player();
	void onAction(bool[4]);
	void onRedraw() override;
};

#endif /* PLAYER_H_ */
