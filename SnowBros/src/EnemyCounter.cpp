/*
 * EnemyCounter.cpp
 *
 *  Created on: 18 ago 2019
 *      Author: franc
 */

#include "EnemyCounter.h"

EnemyCounter* EnemyCounter::instance = 0;

EnemyCounter::EnemyCounter() { counter = 0;}

EnemyCounter::~EnemyCounter() {
	// TODO Auto-generated destructor stub
}

EnemyCounter* EnemyCounter::getinstance()
{
	//EnemyCounter* instance = 0;
	if(instance == 0)
	{
		instance = new EnemyCounter();
	}

	return instance;
}

void EnemyCounter::incCounter() { counter++; }

void EnemyCounter::decCounter() { counter--; }

int EnemyCounter::getEnemiesNumber() { return counter; }
