/*
 * PlayerAction.h
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#ifndef PLAYERACTION_H_
#define PLAYERACTION_H_

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};

enum LAST_DIRECTION {
	NO_DIRECTION_LEFT = 1, NO_DIRECTION_RIGHT = 1 << 1 , LEFT = 1 << 2, RIGHT = 1 << 3, UP = 1 << 4, NO_DIRECTION = NO_DIRECTION_LEFT | NO_DIRECTION_RIGHT
};
typedef LAST_DIRECTION LastDirection;

#include "Action.h"
#include "Actor.h"
#include <string>

class PlayerAction: public Action {
public:
	PlayerAction();
	//PlayerAction(Player*);
	virtual ~PlayerAction();
	virtual void onAction(bool*) override;

	LastDirection lastDirection;
	bool isMoving;
	bool isShooting;
};

#endif /* PLAYERACTION_H_ */
