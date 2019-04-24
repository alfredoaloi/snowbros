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

class EntityDescriptor {
protected:
	Dimensions dim;
	ALLEGRO_BITMAP* bitmap;
	Action* action;

public:
	EntityDescriptor(Dimensions d, ALLEGRO_BITMAP* b, Action* a): dim(d), bitmap(b), action(a){}
	virtual ~EntityDescriptor() {}

	static ALLEGRO_BITMAP* createBitmapFromColor(Dimensions d, int r, int g, int b)
	{
		ALLEGRO_BITMAP* tmp;
		tmp = al_create_bitmap(d.x, d.y);
		al_set_target_bitmap(tmp);
		al_clear_to_color(al_map_rgb(r, g, b));
		return tmp;
	}

	virtual Entity* getDescripted(float x, float y)
	{
		return new Entity(x, y, dim, action);
	}
};

#endif /* ENTITYDESCRIPTOR_H_ */
