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

/*Level::~Level() {
	for(std::unordered_map<int, Entity>::iterator it = this->begin(); it != this->end(); it++)
		it->second.~Entity();
}*/

void Level::drawLevel() {
	for(int i = 0; i < dim_y; i++) {
		for(int j = 0; j < dim_x; j++) {
			if(tileMap[i][j] == "e1"){
				al_draw_filled_rectangle((float)j * (float)80, (float)i * (float)60, (float)j * 80 + (float)80,(float)i * 60 + (float)60, al_map_rgb(255, 255, 255));
			}
		}
	}
}

void Level::addEntity(int key, Entity e){
	(*this)[key] = e;
}
