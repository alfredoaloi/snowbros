/*
 * BossOneAction.h
 *
 *  Created on: 21 ago 2019
 *      Author: laolr
 */

#ifndef BOSSONEACTION_H_
#define BOSSONEACTION_H_

#include "Action.h"
#include "Actor.h"
#include "EnemyCounter.h"

class BossOneAction: public Action {
	int saltaCounter;
	int mortoCounter;
public:
	BossOneAction();
	virtual ~BossOneAction();
	virtual void onAction(bool*) override;
	virtual Action* clone();
};

#endif /* BOSSONEACTION_H_ */
