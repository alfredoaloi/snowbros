/*
 * Spawner.h
 *
 *  Created on: 16 ago 2019
 *      Author: franc
 */

#ifndef SPAWNER_H_
#define SPAWNER_H_

#include <string>

class Spawner {
public:
	Spawner();
	virtual ~Spawner();
	virtual void spawnEntity(std::string, double x, double y) = 0;
};

#endif /* SPAWNER_H_ */
