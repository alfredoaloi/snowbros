/*
 * Entity.h
 *
 *  Created on: 17 apr 2019
 *      Author: francesco
 */

#ifndef ENTITY_H_
#define ENTITY_H_

struct Dimensions
{
	float x;
	float y;
};

class Entity {
protected:
	float pos_x;
	float pos_y;
	Dimensions dim;

public:
	Entity(float x, float y, Dimensions d) : pos_x(x), pos_y(y), dim(d) {};
	virtual ~Entity() {};
};

#endif /* ENTITY_H_ */
