/*
 * EnemyAction.h
 *
 *  Created on: 17 ago 2019
 *      Author: laolr
 */

#ifndef ENEMYACTION_H_
#define ENEMYACTION_H_

#include "Action.h"
#include "Actor.h"
#include "stdlib.h"
#include "SoundBank.h"

enum randAction { left, right, up, shoot, fermo };

class EnemyAction: public Action {
	int cooldown;
	int mortoCounter;
	SoundBank* soundBank;
public:
	EnemyAction();
	virtual ~EnemyAction();
	virtual void onAction(bool*) override;
	virtual Action* clone();
};

#endif /* ENEMYACTION_H_ */
