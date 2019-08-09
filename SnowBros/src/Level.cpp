/*
 * Level.cpp
 *
 *  Created on: 17 apr 2019
 *      Author: francesco
 */

#include "Level.h"

Level::Level(std::string fileName, ALLEGRO_BITMAP* levelBackground) {
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

	this->levelBackground = levelBackground;
}

Level::~Level() { }

void Level::drawLevel() {

	if(constructedEntities.empty()/* || constructedControllers.empty()*/)
		constructLevel();

	al_draw_bitmap(levelBackground, 0, 0, 0);

	for(std::list<Entity*>::iterator it = constructedEntities.begin(); it != constructedEntities.end(); it++)
	{
		(*it)->onRedraw();
	}
}

void Level::processLevel()
{
	if(constructedEntities.empty()/* || constructedControllers.empty()*/)
			constructLevel();

	for(std::list<Controller*>::iterator it = constructedControllers.begin(); it != constructedControllers.end(); it++)
	{
		(*it)->processAction();
	}
}

void Level::constructLevel()
{
	for(int i = 0; i < dim_y; i++)
	{
		for(int j = 0; j < dim_x; j++)
		{
			std::unordered_map<std::string, EntityDescriptor*>::iterator it;
			it = entities.find(tileMap[i][j]);
			if(it != entities.end())
			{
				Entity* tmpEntity = it->second->getDescripted((float)j * (float)16, (float)i * (float)16);
				if(tmpEntity->getAction() != nullptr)
				{
					Controller* tmpController = new Controller();
					tmpController->changeAction(tmpEntity->getAction());
					constructedControllers.push_back(tmpController);
				}
				constructedEntities.push_back(tmpEntity);
			}
//			//Non testato, ma dovrebbe funzionare
//			else
//			{
//				it = players.find(tileMap[i][j]);
//				if(it != players.end())
//				{
//					Entity* tmpEntity = it->second->getDescripted((float)j * (float)50, (float)i * (float)46.154);
//					if(!playerControllers.empty() && playerControllers.front() != nullptr)
//					{
//						Controller* tmpController = new Controller(*playerControllers.front());
//						playerControllers.pop_front();
//						tmpController->changeAction(tmpEntity->getAction());
//						constructedControllers.push_back(tmpController);
//					}
//					constructedEntities.push_back(tmpEntity);
//				}
//			}//
		}
	}

	entities.clear();
	players.clear();
	playerControllers.clear();
}

void Level::registerEntity(std::string key, EntityDescriptor* e) { entities[key] = e; }

void Level::registerPlayer(std::string key, EntityDescriptor* e) { players[key] = e; }

void Level::registerController(Controller* c) { playerControllers.push_back(c); }

void Level::setLevelbackground(ALLEGRO_BITMAP* levelBackground) { this->levelBackground = levelBackground; }
