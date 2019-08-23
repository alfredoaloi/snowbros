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
#include "PlayerScore.h"

class BossOneAction: public Action {
	int saltaCounter;
	int mortoCounter;
	int pocoMortoCounter;
	int quasiMortoCounter;
public:
	BossOneAction();
	virtual ~BossOneAction();
	virtual void onAction(bool*) override;
	virtual Action* clone();
};

#endif /* BOSSONEACTION_H_ */
