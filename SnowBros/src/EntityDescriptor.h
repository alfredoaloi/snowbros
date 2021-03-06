/*
 * EntityDescriptor.h
 *
 *  Created on: 18 apr 2019
 *      Author: francesco
 */

#ifndef ENTITYDESCRIPTOR_H_
#define ENTITYDESCRIPTOR_H_
#include "Dimensions.h"
#include <allegro5/allegro.h>
#include "Entity.h"
#include "Action.h"
#include "CollisionHandler.h"
#include "SpritesheetManager.h"
#include "Controller.h"

class EntityDescriptor {
protected:
	Dimensions* dim;
	ALLEGRO_BITMAP* bitmap;
	Controller* controller;
	Action* action;
	CollisionHandler* collisionHandler;
	SpritesheetManager* spritesheetManager;
	std::string type;

public:
	EntityDescriptor(Dimensions* d, ALLEGRO_BITMAP* b, Controller* c, Action* a, CollisionHandler* ch, SpritesheetManager* ssm, std::string t): dim(d), bitmap(b), controller(c), action(a), collisionHandler(ch), spritesheetManager(ssm), type(t) {}
	virtual ~EntityDescriptor()
	{
		delete dim;
		al_destroy_bitmap(bitmap);
		delete controller;
		delete action;
		delete collisionHandler;
	}

	static ALLEGRO_BITMAP* createBitmapFromColor(Dimensions* d, int r, int g, int b)
	{
		ALLEGRO_BITMAP* tmp;
		tmp = al_create_bitmap(d->x, d->y);
		al_set_target_bitmap(tmp);
		al_clear_to_color(al_map_rgb(r, g, b));
		return tmp;
	}

	virtual Entity* getDescripted(float x, float y)
	{
		return new Entity(x, y, dim, type);
	}

	CollisionHandler* getDescriptedCollisionHandler() { return (collisionHandler == nullptr) ? (collisionHandler) : (collisionHandler->clone()); }

	Action* getDescriptedAction() { return (action == nullptr) ? (action) : (action->clone()); }

	SpritesheetManager* getDescriptedSpritesheetManager() {  return (spritesheetManager == nullptr) ? (spritesheetManager) : (spritesheetManager->clone());}

	Controller* getDescriptedController() { return (controller == nullptr) ? (controller) : (controller->clone()); }
};

#endif /* ENTITYDESCRIPTOR_H_ */
