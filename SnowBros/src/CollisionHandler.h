/*
 * CollisionHandler.h
 *
 *  Created on: 9 ago 2019
 *      Author: Francesco
 */

#ifndef COLLISIONHANDLER_H_
#define COLLISIONHANDLER_H_

#include "Entity.h"
#include <iostream>

enum SIDE
{
	NO_COLLISION,
	SIDE_RIGHT,
	SIDE_LEFT,
	SIDE_UP,
	SIDE_DOWN
};
typedef SIDE Side_t;

class CollisionHandler {
protected:
	Entity* entity;
public:
	CollisionHandler();
	virtual ~CollisionHandler();
	virtual bool handleCollision(Entity* other);
	void setEntity(Entity*);
	Entity* getEntity();
	Side_t checkCollision(Entity*);
};

#endif /* COLLISIONHANDLER_H_ */
