/*
 * SpritesheetManager.h
 *
 *  Created on: 5 ago 2019
 *      Author: Francesco
 */

#ifndef SPRITESHEETMANAGER_H_
#define SPRITESHEETMANAGER_H_

#include <map>
#include <string>
#include <allegro5/allegro.h>
#include "Spritesheet.h"

class SpritesheetManager {

	std::map<std::string, Spritesheet*> spritesheets;

	Spritesheet* currentSpritesheet;

	float width, height;
	int currentSprite;

public:
	SpritesheetManager();
	virtual ~SpritesheetManager();
	void setNewSpritesheet(std::string, Spritesheet*);
	void selectCurrentSpritesheet(std::string);
	void nextSprite(ALLEGRO_BITMAP*);
	void setWidth(float);
	void setHeight(float);
};

#endif /* SPRITESHEETMANAGER_H_ */
