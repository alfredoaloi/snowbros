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
	Entity(Entity*);
	virtual void onRedraw();
	virtual Action* getAction();
	virtual ~Entity();
	//void setAction(const Action*& action);
	Dimensions getDim() const;
	void setDim(Dimensions dim);
	float getPosX() const;
	void setPosX(float posX);
	float getPosY() const;
	void setPosY(float posY);
};

#endif /* ENTITY_H_ */
