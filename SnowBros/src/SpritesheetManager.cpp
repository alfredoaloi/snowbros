/*
 * SpritesheetManager.cpp
 *
 *  Created on: 5 ago 2019
 *      Author: Francesco
 */

#include "SpritesheetManager.h"

SpritesheetManager::SpritesheetManager()
{
	currentSpritesheet = new Spritesheet();
	width = 0.0;
	height = 0.0;
	currentSprite = 0;
}

SpritesheetManager::~SpritesheetManager() { }

void SpritesheetManager::nextSprite(ALLEGRO_BITMAP* sprite)
{
	ALLEGRO_BITMAP* nextSprite = al_create_bitmap(width, height);
	ALLEGRO_BITMAP* spritesheet = al_create_bitmap(500, 500);
	currentSpritesheet->getSpritesheet(spritesheet);
	al_set_target_bitmap(nextSprite);

	if(currentSprite >= currentSpritesheet->getnSprites())
		currentSprite = 0;

	al_draw_bitmap_region(spritesheet, width * currentSprite, 0, width, height, 0, 0, 0);
	currentSprite++;

	al_set_target_bitmap(sprite);
	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(sprite, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(nextSprite, al_map_rgb(255, 0, 255));
	al_draw_bitmap(nextSprite, 0, 0, 0);
}

void SpritesheetManager::selectCurrentSpritesheet(std::string spritesheetID)
{
	std::map<std::string, Spritesheet*>::iterator it;
	it = spritesheets.find(spritesheetID);

	currentSpritesheet = it->second;

	currentSprite = 0;
}

void SpritesheetManager::setNewSpritesheet(std::string spritesheetID, Spritesheet* spritesheet)
{
	spritesheets[spritesheetID] = spritesheet;
}

void SpritesheetManager::setWidth(float width)
{
	this->width = width;
}

void SpritesheetManager::setHeight(float height)
{
	this->height = height;
}
