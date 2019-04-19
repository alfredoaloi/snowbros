/*
 * Controller.h
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Action.h"
#include <unordered_map>

class Controller {
private:
	//std::unordered_map<int, Controller*> instances;
	int idController;
	Action* action;
	bool* commands;
public:
	virtual void processAction()
	{
		action->onAction(commands);
	}


	Controller() { action = nullptr; }

	Controller(Action* a, bool* c) : commands(c)
	{
		/*idController = instances.size();*/
		action = a;
		//instances[idController] = this;*/
	}

	/*void iterateControllers()
	{
		for(std::unordered_map<int ,Controller*>::iterator it = instances.begin(); it != instances.end(); it++)
		{
			it->second->processAction();
		}
	}*/

	void changeCommands(bool *c) { commands = c; }

	void changeAction(Action* a) { action = a; }

	virtual ~Controller()
	{
		delete action;
		//instances.erase(idController);
	}
};

#endif /* CONTROLLER_H_ */
