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

	if(constructedEntities.empty() || constructedControllers.empty())
		constructLevel();

	al_draw_bitmap(levelBackground, 0, 0, 0);

	for(std::list<Entity*>::iterator it = constructedEntities.begin(); it != constructedEntities.end(); it++)
	{
		(*it)->onRedraw();
	}
}

void Level::processLevel()
{
	if(constructedEntities.empty() || constructedControllers.empty())
			constructLevel();

	for(std::list<Controller*>::iterator it = constructedControllers.begin(); it != constructedControllers.end(); it++)
	{
		(*it)->processAction();
	}

	for(std::list<CollisionHandler*>::iterator it1 = constructedCollisionHandlers.begin(); it1 != constructedCollisionHandlers.end(); it1++)
	{
		Actor* tmp = dynamic_cast<Actor*>((*it1)->getEntity());
		bool chk = false;
		for(std::list<Entity*>::iterator it2 = constructedEntities.begin(); it2 != constructedEntities.end(); it2++)
		{
			if((*it1)->getEntity() != *it2)
			{
				if((*it1)->handleCollision(*it2))
				{
					chk = true;
				}
			}
		}

		if(!chk)
		{
			if(!tmp->isJumping())
			{
				if(tmp->getLastDirection() == RIGHT || tmp->getLastDirection() == NO_DIRECTION_RIGHT || tmp->getLastDirection() == SHOOTING_RIGHT || tmp->getLastDirection() == JUMPING_RIGHT)
				{
					tmp->getSpritesheetManager()->selectCurrentSpritesheet("saltaR");
					tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
					tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
					tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
					tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
					tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
					tmp->setLastDirection(FALLING_RIGHT);
				}
				else if(tmp->getLastDirection() == LEFT || tmp->getLastDirection() == NO_DIRECTION_LEFT || tmp->getLastDirection() == SHOOTING_LEFT || tmp->getLastDirection() == JUMPING_LEFT)
				{
					tmp->getSpritesheetManager()->selectCurrentSpritesheet("saltaL");
					tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
					tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
					tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
					tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
					tmp->getSpritesheetManager()->nextSprite(tmp->getBitmap());
					tmp->setLastDirection(FALLING_LEFT);
				}
				tmp->setShooting(false);
			}
		}
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
				if(it->second->getDescriptedController() != nullptr)
				{
					Controller* tmpController = it->second->getDescriptedController();
					Action* action = it->second->getDescriptedAction();
					action->setEntity(tmpEntity);
					tmpController->changeAction(action);
					constructedControllers.push_back(tmpController);
				}
				if(it->second->getDescriptedCollisionHandler() != nullptr)
				{
					CollisionHandler* tmpCollisionhandler = it->second->getDescriptedCollisionHandler();
					tmpCollisionhandler->setEntity(tmpEntity);
					constructedCollisionHandlers.push_back(tmpCollisionhandler);
				}
				constructedEntities.push_back(tmpEntity);
			}
		}
	}

	entities.clear();
}

void Level::registerEntity(std::string key, EntityDescriptor* e) { entities[key] = e; }

void Level::setLevelbackground(ALLEGRO_BITMAP* levelBackground) { this->levelBackground = levelBackground; }
