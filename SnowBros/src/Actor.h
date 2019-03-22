/*
 * Actor.h
 *
 *  Created on: 17 mar 2019
 *      Author: francesco
 */

#ifndef ACTOR_H_
#define ACTOR_H_
#include <allegro5/allegro.h>

class Actor {
protected:
	int dim = 32;
	float pos_x;
	float pos_y;
	float speed;
	float max_height;
	float f_speed; //falling speed
	float j_speed; //jumping speed
	ALLEGRO_BITMAP* bitmap;
public:
	Actor(float x, float y, float s, float h, float f_s, float j_s, ALLEGRO_BITMAP* bit)
		:pos_x(x), pos_y(y), speed(s), max_height(h), f_speed(f_s), j_speed(j_s), bitmap(bit){};
	virtual ~Actor() {};
	//virtual void onAction() = 0;
	virtual void onRedraw() = 0;
};

#endif /* ACTOR_H_ */
