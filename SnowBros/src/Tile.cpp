/*
 * Tile.cpp
 *
 *  Created on: 18 apr 2019
 *      Author: francesco
 */

#include "Tile.h"

Tile::Tile(float x, float y, Dimensions* d, ALLEGRO_BITMAP* b, std::string t) : Entity(x, y, d, t), bitmap(b){  }

Tile::~Tile() {
	al_destroy_bitmap(bitmap);
}

void Tile::onRedraw()
{
	//al_draw_bitmap(bitmap, pos_x, pos_y, 0);
}
