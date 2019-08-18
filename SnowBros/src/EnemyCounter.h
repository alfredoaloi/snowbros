/*
 * EnemyCounter.h
 *
 *  Created on: 18 ago 2019
 *      Author: franc
 */

#ifndef ENEMYCOUNTER_H_
#define ENEMYCOUNTER_H_

class EnemyCounter {
	static EnemyCounter* instance;
	int counter;
protected:
	EnemyCounter();
	virtual ~EnemyCounter();
public:
	static EnemyCounter* getinstance();
	void incCounter();
	void decCounter();
	int getEnemiesNumber();
};

#endif /* ENEMYCOUNTER_H_ */
