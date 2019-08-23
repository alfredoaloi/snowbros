/*
 * BossTwoCollisionHandler.h
 *
 *  Created on: 23 ago 2019
 *      Author: laolr
 */

#ifndef BOSSTWOCOLLISIONHANDLER_H_
#define BOSSTWOCOLLISIONHANDLER_H_

#include "CollisionHandler.h"
#include "Actor.h"
#include "PlayerScore.h"

class BossTwoCollisionHandler: public CollisionHandler {
public:
	BossTwoCollisionHandler();
	virtual ~BossTwoCollisionHandler();
	virtual bool handleCollision(Entity* other) override;
	virtual CollisionHandler* clone() override;
};

#endif /* BOSSTWOCOLLISIONHANDLER_H_ */
