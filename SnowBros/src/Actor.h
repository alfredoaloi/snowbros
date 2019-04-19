/*
 * Actor.h
 *
 *  Created on: 17 mar 2019
 *      Author: francesco
 */

#ifndef ACTOR_H_
#define ACTOR_H_
#include <allegro5/allegro.h>
#include "Entity.h"

const int screenWidth = 800;
const int screenHeight = 600;

class Actor : public Entity {
protected:
	float speed;
	float max_height;
	float f_speed; //falling speed
	float j_speed; //jumping speed
	ALLEGRO_BITMAP* bitmap;
	Action action;
public:
	Actor(float x, float y, Dimensions d, float s, float h, float f_s, float j_s,
			ALLEGRO_BITMAP* bit, Action* a) :
			Entity(x, y, d, a), speed(s), max_height(h), f_speed(f_s), j_speed(
					j_s), bitmap(bit) {
	}
	virtual ~Actor() {}
	virtual void onAction() {}
	virtual void onAction(bool [4]) {}
	void onRedraw() override {};
};

#endif /* ACTOR_H_ */
