/*
 * PlayerScore.h
 *
 *  Created on: 18 ago 2019
 *      Author: franc
 */

#ifndef PLAYERSCORE_H_
#define PLAYERSCORE_H_

class PlayerScore {
	static PlayerScore* instance;
	int score;
protected:
	PlayerScore();
	virtual ~PlayerScore();
public:
	static PlayerScore* getInstance();
	void addScore(int);
	int getScore();
};

#endif /* PLAYERSCORE_H_ */
