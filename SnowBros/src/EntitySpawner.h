/*
 * EntitySpawner.h
 *
 *  Created on: 15 ago 2019
 *      Author: franc
 */

#ifndef ENTITYSPAWNER_H_
#define ENTITYSPAWNER_H_

#include "Level.h"
#include "Entity.h"
#include <string>

class EntitySpawner {

	Entity* entity;
	Level* level;

public:
	EntitySpawner(Entity*, Level*);
	virtual ~EntitySpawner();
	void spawnEntity(std::string);
};

#endif /* ENTITYSPAWNER_H_ */
