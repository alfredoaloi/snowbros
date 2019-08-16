/*
 * LevelSpawner.h
 *
 *  Created on: 16 ago 2019
 *      Author: franc
 */

#ifndef LEVELSPAWNER_H_
#define LEVELSPAWNER_H_

#include "Spawner.h"
#include "Level.h"

class LevelSpawner: public Spawner {

	Level* level;

public:
	LevelSpawner(Level*);
	virtual ~LevelSpawner();
	virtual void spawnEntity(std::string, double, double);
};

#endif /* LEVELSPAWNER_H_ */
