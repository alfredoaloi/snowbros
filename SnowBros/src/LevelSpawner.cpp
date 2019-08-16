/*
 * LevelSpawner.cpp
 *
 *  Created on: 16 ago 2019
 *      Author: franc
 */

#include "LevelSpawner.h"

LevelSpawner::LevelSpawner(Level* level) : level(level) {  }

LevelSpawner::~LevelSpawner() {  }

void LevelSpawner::spawnEntity(std::string entity, double x, double y)
{
	level->spawn(entity, x, y);
}

