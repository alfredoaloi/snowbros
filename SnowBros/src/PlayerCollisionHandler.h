/*
 * PlayerCollisionHandler.h
 *
 *  Created on: 9 ago 2019
 *      Author: Francesco
 */

#ifndef PLAYERCOLLISIONHANDLER_H_
#define PLAYERCOLLISIONHANDLER_H_

#include "CollisionHandler.h"
#include "Actor.h"
#include <cmath>
#include "SoundBank.h"

class PlayerCollisionHandler: public CollisionHandler {
	SoundBank* soundBank;
public:
	PlayerCollisionHandler();
	virtual ~PlayerCollisionHandler();
	virtual bool handleCollision(Entity* other) override;
	virtual CollisionHandler* clone() override;
};

#endif /* PLAYERCOLLISIONHANDLER_H_ */
