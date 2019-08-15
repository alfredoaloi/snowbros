/*
 * EntitySpawner.cpp
 *
 *  Created on: 15 ago 2019
 *      Author: franc
 */

#include "EntitySpawner.h"

EntitySpawner::EntitySpawner(Entity* entity, Level* level) {
	this->entity = entity;
	this->level = level;
}

EntitySpawner::~EntitySpawner() {  }

void EntitySpawner::spawnEntity(std::string entity)
{

}

