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
#include <vector>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <sstream>
#include <iostream>
#include "EntityDescriptor.h"
#include "Controller.h"
#include "Actor.h"

class Level;
#include "LevelSpawner.h"

class Level {
	static constexpr int dim_x = 16;
	static constexpr int dim_y = 12;
	std::string tileMap[dim_y][dim_x];
	std::unordered_map<std::string, EntityDescriptor*> entities;
	std::vector<Entity*> constructedEntities;
	std::vector<Controller*> constructedControllers;
	std::vector<CollisionHandler*> constructedCollisionHandlers;
	ALLEGRO_BITMAP* levelBackground;
	void constructLevel();
public:
	void registerEntity(std::string, EntityDescriptor*);
	void registerPlayer(std::string ,EntityDescriptor*);
	void registerController(Controller*);
	void setLevelbackground(ALLEGRO_BITMAP*);
	void processLevel(int&, int&, int&, int&);
	Level(std::string, ALLEGRO_BITMAP*);
	~Level();
	void drawLevel();
	void spawn(std::string, double, double);
	void spawnPlayer();
};

#endif /* LEVEL_H_ */
