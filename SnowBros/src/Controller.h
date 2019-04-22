/*
 * Controller.h
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Action.h"

class Controller {
private:
	Action* action;
	bool* commands;
public:
	virtual void processAction()
	{
		if(action != nullptr && commands != nullptr)
			action->onAction(commands);
	}

	Controller() { action = nullptr; commands = nullptr; }

	Controller(Action* a, bool* c) :action(a) ,commands(c) { }

	void changeCommands(bool *c) { commands = c; }

	void changeAction(Action* a) { action = a; }

	virtual ~Controller() { delete action; delete[] commands; }
};

#endif /* CONTROLLER_H_ */
