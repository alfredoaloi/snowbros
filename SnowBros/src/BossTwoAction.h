/*
 * BossTwoAction.h
 *
 *  Created on: 23 ago 2019
 *      Author: laolr
 */

#ifndef BOSSTWOACTION_H_
#define BOSSTWOACTION_H_

#include "Action.h"
#include "Actor.h"
#include "EnemyCounter.h"
#include "PlayerScore.h"

class BossTwoAction: public Action {
	int mortoCounter;
	int sparaCounter;
	int morenteCounter;
public:
	BossTwoAction();
	virtual ~BossTwoAction();
	virtual void onAction(bool*) override;
	virtual Action* clone();
};

#endif /* BOSSTWOACTION_H_ */
