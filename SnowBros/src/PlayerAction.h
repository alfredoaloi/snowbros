/*
 * PlayerAction.h
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#ifndef PLAYERACTION_H_
#define PLAYERACTION_H_

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ESCAPE
};

#include "Action.h"
#include "Actor.h"
#include <string>

class PlayerAction: public Action {
	int spawnCounter;
	int mortoCounter;
	int invCounter;
public:
	PlayerAction();
	//PlayerAction(Player*);
	virtual ~PlayerAction();
	virtual void onAction(bool*) override;
	virtual Action* clone();
};

#endif /* PLAYERACTION_H_ */
