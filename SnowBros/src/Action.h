/*
 * Action.h
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#ifndef ACTION_H_
#define ACTION_H_

#include "Entity.h"

class Action {
protected:
	Entity* entity;

public:
	Action();

	Action(Entity* e);

	virtual ~Action();

	virtual void onAction(bool*);

	void setEntity(Entity* e);
};

#endif /* ACTION_H_ */
