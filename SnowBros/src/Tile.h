/*
 * Tile.h
 *
 *  Created on: 18 apr 2019
 *      Author: francesco
 */

#ifndef TILE_H_
#define TILE_H_
#include <allegro5/allegro.h>
#include "Entity.h"

class Tile : public Entity{
	ALLEGRO_BITMAP *bitmap;
public:
	Tile(float x, float y, Dimensions d, ALLEGRO_BITMAP* b, Action*);
	virtual ~Tile();
	void onRedraw() override;
};

#endif /* TILE_H_ */
