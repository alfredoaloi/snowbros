/*
 * Entity.h
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Dimensions.h"

class Entity; //NON LO ELIMINARE TI PREGO
#include "Action.h"

class Entity {
protected:
	float pos_x;
	float pos_y;
	Dimensions dim;
	Action* action;

public:
	Entity();
	Entity(float x, float y, Dimensions d, Action* a);
	virtual void onRedraw();
	Action* getAction();
	virtual ~Entity();
};

#endif /* ENTITY_H_ */
