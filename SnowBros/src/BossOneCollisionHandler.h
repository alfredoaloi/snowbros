/*
 * BossOneCollisionHandler.h
 *
 *  Created on: 21 ago 2019
 *      Author: laolr
 */

#ifndef BOSSONECOLLISIONHANDLER_H_
#define BOSSONECOLLISIONHANDLER_H_

#include "CollisionHandler.h"
#include "Actor.h"
#include "PlayerScore.h"

class BossOneCollisionHandler: public CollisionHandler {
public:
	BossOneCollisionHandler();
	virtual ~BossOneCollisionHandler();
	virtual bool handleCollision(Entity* other) override;
	virtual CollisionHandler* clone() override;
};

#endif /* BOSSONECOLLISIONHANDLER_H_ */
