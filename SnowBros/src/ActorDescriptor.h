/*
 * ActorDescriptor.h
 *
 *  Created on: 10 ago 2019
 *      Author: Francesco
 */

#ifndef ACTORDESCRIPTOR_H_
#define ACTORDESCRIPTOR_H_

#include "EntityDescriptor.h"
#include "Actor.h"

class ActorDescriptor: public EntityDescriptor {
	float speed;
	float max_height;
	float f_speed; //falling speed
	float j_speed; //jumping speed

public:
	ActorDescriptor(Dimensions* d, float s, float h, float f_s, float j_s, Controller* c, Action* a, CollisionHandler* ch, SpritesheetManager* ssm, std::string t): EntityDescriptor(d, nullptr, c, a, ch, ssm, t), speed(s), max_height(h), f_speed(f_s), j_speed(j_s) {}
	virtual ~ActorDescriptor() {}
	Entity* getDescripted(float x, float y)
	{
		return new Actor(x, y, dim, speed, max_height, f_speed, j_speed, type, spritesheetManager->clone());
	}
};

#endif /* ACTORDESCRIPTOR_H_ */
