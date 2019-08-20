/*
 * PowerupCollisionHandler.h
 *
 *  Created on: 20 ago 2019
 *      Author: laolr
 */

#ifndef POWERUPCOLLISIONHANDLER_H_
#define POWERUPCOLLISIONHANDLER_H_

#include "CollisionHandler.h"
#include "Actor.h"

class PowerupCollisionHandler: public CollisionHandler {
public:
	PowerupCollisionHandler();
	virtual ~PowerupCollisionHandler();
	virtual bool handleCollision(Entity* other) override;
	virtual CollisionHandler* clone() override;
};

#endif /* POWERUPCOLLISIONHANDLER_H_ */
