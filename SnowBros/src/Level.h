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

class Level {
	static constexpr int dim_x = 10;
	static constexpr int dim_y = 10;
	std::string tileMap[dim_x][dim_y];
	std::unordered_map<std::string, EntityDescriptor* > entities;
	std::unordered_map<std::string, EntityDescriptor* > players;
	std::list<Controller*> playerControllers;
	std::list<Entity*> constructedEntities;
	std::list<Controller*> constructedControllers;
	void constructLevel();
public:
	void registerEntity(std::string, EntityDescriptor*);
	void registerPlayer(std::string ,EntityDescriptor*);
	void registerController(Controller*);
	void processLevel();
	Level(std::string);
	~Level();
	void drawLevel();
};

#endif /* LEVEL_H_ */
