/*
 * BulletAction.h
 *
 *  Created on: 16 ago 2019
 *      Author: laolr
 */

#ifndef BULLETACTION_H_
#define BULLETACTION_H_

#include "Action.h"
#include "Actor.h"
#include <string>

class BulletAction: public Action {
	bool spawn = true;
public:
	BulletAction();
	virtual ~BulletAction();
	virtual void onAction(bool*) override;
	virtual Action* clone();
};

#endif /* BULLETACTION_H_ */
