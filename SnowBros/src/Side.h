/*
 * Lato.h
 *
 *  Created on: 9 ago 2019
 *      Author: Francesco
 */

#ifndef SIDE_H_
#define SIDE_H_

class Side;
#include "Entity.h"

enum SIDE
{
	NO_COLLISION,
	SIDE_RIGHT,
	SIDE_LEFT,
	SIDE_UP,
	SIDE_DOWN
};
typedef SIDE Side_t;

class Side {
public:
	Side(Side_t);
	virtual ~Side();
	Entity* entity;
	Side_t sideType;
	void setEntity(Entity*);
	Side_t getSideType();
	bool checkCollision(Entity*);
};

#endif /* SIDE_H_ */
