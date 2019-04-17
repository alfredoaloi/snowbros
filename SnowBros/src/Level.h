/*
 * Level.h
 *
 *  Created on: 17 apr 2019
 *      Author: francesco
 */

#ifndef LEVEL_H_
#define LEVEL_H_
#include <list>
#include <fstream>
#include <allegro5/allegro.h>
#include <string>
#include <sstream>
#include <iostream>
#include "Entity.h"


class Level : public std::list<Entity>{
	static constexpr int dim_x = 10;
	static constexpr int dim_y = 10;
	int tileMap[dim_x][dim_y];
public:
	Level(std::string);
	virtual ~Level();
};

#endif /* LEVEL_H_ */
