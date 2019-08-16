/*
 * BulletCollisionHandler.h
 *
 *  Created on: 16 ago 2019
 *      Author: laolr
 */

#ifndef BULLETCOLLISIONHANDLER_H_
#define BULLETCOLLISIONHANDLER_H_

#include "CollisionHandler.h"
#include "Actor.h"

class BulletCollisionHandler: public CollisionHandler {
public:
	BulletCollisionHandler();
	virtual ~BulletCollisionHandler();
	virtual bool handleCollision(Entity* other) override;
	virtual CollisionHandler* clone() override;
};

#endif /* BULLETCOLLISIONHANDLER_H_ */
