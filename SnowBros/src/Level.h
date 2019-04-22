/*
 * Level.h
 *
 *  Created on: 17 apr 2019
 *      Author: francesco
 */

#ifndef LEVEL_H_
#define LEVEL_H_
#include <unordered_map>
//#include <list>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <sstream>
#include <iostream>
#include "Entity.h"

class Level : public std::unordered_map<int, Entity* >{
	static constexpr int dim_x = 10;
	static constexpr int dim_y = 10;
	std::string tileMap[dim_x][dim_y];
public:
	void addEntity(int, Entity*);
	Level(std::string);
	~Level();
	void drawLevel();
};

#endif /* LEVEL_H_ */
