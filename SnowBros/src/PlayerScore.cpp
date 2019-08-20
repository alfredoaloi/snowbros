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

int PlayerScore::readHighScore(std::string fileName)
{
	std::ifstream file(fileName);

	if(file.fail())
	{
		return 0;
	}

	std::string s;
	std::getline(file, s);
	std::stringstream ss(s);

	int x;
	ss >> x;

	return x;
}

void PlayerScore::writeHighScore(std::string fileName, int highScore)
{
	std::ofstream file(fileName);

	if(file.fail())
	{
		return;
	}

	file << highScore;
}
