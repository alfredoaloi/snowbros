/*
 * Level.cpp
 *
 *  Created on: 17 apr 2019
 *      Author: francesco
 */

#include "Level.h"

Level::Level(std::string fileName) {
	std::ifstream file(fileName);

	if(file.fail())
	{
		std::cout << "Unable to open the file";
		return;
	}

	/*for(int i = 0; i < dim_y; i++)
	{
		for(int j = 0; j < dim_x; j++)
		{
			tileMap[i][j] = 0;
		}
	}*/

	for(int i = 0; i < dim_y; i++)
	{
		std::string s;
		std::getline(file, s);
		std::stringstream ss(s);
		for(int j = 0; j < dim_x; j++)
		{
			ss >> tileMap[i][j];
		}
	}
}

Level::~Level() {
	// TODO Auto-generated destructor stub
}

