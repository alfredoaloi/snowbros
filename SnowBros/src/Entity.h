/*
 * Entity.h
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Dimensions.h"
#include <string>
#include <list>

class Entity {
protected:
	float pos_x;
	float pos_y;
	Dimensions* dim;
	std::string type;

public:
	Entity();
	Entity(float, float, Dimensions*, std::string);
	Entity(Entity*);
	virtual void onRedraw();
	virtual ~Entity();
	Dimensions* getDim() const;
	void setDim(Dimensions*);
	float getPosX() const;
	void setPosX(float);
	float getPosY() const;
	void setPosY(float);
	std::string getType();
};

#endif /* ENTITY_H_ */
