/*
 * Level.h
 *
 *  Created on: 17 apr 2019
 *      Author: francesco
 */

#ifndef LEVEL_H_
#define LEVEL_H_
#include <unordered_map>
#include <list>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <sstream>
#include <iostream>
#include "Entity.h"
#include "EntityDescriptor.h"
#include "Controller.h"
#include "Actor.h"

class Level {
	static constexpr int dim_x = 16;
	static constexpr int dim_y = 12;
	std::string tileMap[dim_y][dim_x];
	std::unordered_map<std::string, EntityDescriptor*> entities;
	std::list<Entity*> constructedEntities;
	std::list<Controller*> constructedControllers;
	std::list<CollisionHandler*> constructedCollisionHandlers;
	ALLEGRO_BITMAP* levelBackground;
	void constructLevel();
public:
	void registerEntity(std::string, EntityDescriptor*);
	void registerPlayer(std::string ,EntityDescriptor*);
	void registerController(Controller*);
	void setLevelbackground(ALLEGRO_BITMAP*);
	void processLevel();
	Level(std::string, ALLEGRO_BITMAP*);
	~Level();
	void drawLevel();
};

#endif /* LEVEL_H_ */
