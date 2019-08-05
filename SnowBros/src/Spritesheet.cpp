/*
 * Spritesheet.cpp
 *
 *  Created on: 5 ago 2019
 *      Author: Francesco
 */

#include "Spritesheet.h"

Spritesheet::Spritesheet() {
	spritesheet = al_create_bitmap(500, 500);
	nSprites = 0;
}

Spritesheet::Spritesheet(ALLEGRO_BITMAP* spritesheet, int nSprites)
{
	this->spritesheet = spritesheet;
	this->nSprites = nSprites;
}

Spritesheet::~Spritesheet() {
	al_destroy_bitmap(spritesheet);
}

int Spritesheet::getnSprites()
{
	return nSprites;
}

void Spritesheet::getSpritesheet(ALLEGRO_BITMAP*& sprite)
{
	al_set_target_bitmap(sprite);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_draw_bitmap(spritesheet, 0, 0, 0);
}

Spritesheet& Spritesheet::operator=(const Spritesheet& other)
{
	al_set_target_bitmap(this->spritesheet);
	al_clear_to_color(al_map_rgba(255, 255, 255, 0));
	al_draw_bitmap(other.spritesheet, 0, 0, 0);
	this->nSprites = other.nSprites;

	return *this;
}

