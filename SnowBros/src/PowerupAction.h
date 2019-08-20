/*
 * PowerupAction.h
 *
 *  Created on: 20 ago 2019
 *      Author: laolr
 */

#ifndef POWERUPACTION_H_
#define POWERUPACTION_H_

#include "Action.h"
#include "Actor.h"

class PowerupAction: public Action {
public:
	PowerupAction();
	virtual ~PowerupAction();
	virtual void onAction(bool*) override;
	virtual Action* clone();
};

#endif /* POWERUPACTION_H_ */
