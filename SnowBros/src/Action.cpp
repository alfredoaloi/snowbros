/*
 * Action.cpp
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#include "Action.h"

Action::Action() { entity = nullptr; }

Action::Action(Entity* e) : entity(e) { }

void Action::onAction(bool*) { }

void Action::setEntity(Entity* e){ entity = e; }

Action::~Action() { }

Action* Action::clone() { return new Action(); }
