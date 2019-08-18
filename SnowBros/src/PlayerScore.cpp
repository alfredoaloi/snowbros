/*
 * PlayerScore.cpp
 *
 *  Created on: 18 ago 2019
 *      Author: franc
 */

#include "PlayerScore.h"

PlayerScore* PlayerScore::instance = 0;

PlayerScore::PlayerScore() { score = 0;}

PlayerScore::~PlayerScore() {
	// TODO Auto-generated destructor stub
}

PlayerScore* PlayerScore::getInstance()
{
	if(instance == 0)
	{
		instance = new PlayerScore();
	}

	return instance;
}

void PlayerScore::addScore(int n) { score += n; }

int PlayerScore::getScore() { return score; }
