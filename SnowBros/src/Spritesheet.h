/*
 * Spritesheet.h
 *
 *  Created on: 5 ago 2019
 *      Author: Francesco
 */

#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include <allegro5/allegro.h>

class Spritesheet {

	ALLEGRO_BITMAP* spritesheet;
	int nSprites;

public:
	Spritesheet();
	Spritesheet(ALLEGRO_BITMAP*, int);
	virtual ~Spritesheet();
	int getnSprites();
	void getSpritesheet(ALLEGRO_BITMAP*&);
	Spritesheet& operator=(const Spritesheet& other);
};

#endif /* SPRITESHEET_H_ */
