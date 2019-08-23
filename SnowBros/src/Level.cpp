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
	this->playerDestroyed = false;
}

Level::~Level()
{
	for(std::unordered_map<std::string, EntityDescriptor*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		delete it->second;
	}
}

void Level::drawLevel() {

	if(constructedEntities.empty() || constructedControllers.empty())
		constructLevel();

	al_draw_bitmap(levelBackground, 0, 24, 0);
	for(std::vector<Entity*>::iterator it = constructedEntities.begin(); it != constructedEntities.end(); it++)
	{
		(*it)->onRedraw();
	}
}

void Level::processLevel(int& nLives)
{
	if(constructedEntities.empty() || constructedControllers.empty())
			constructLevel();

	unsigned j = 0;
	while(j < constructedEntities.size())
	{
		if (constructedEntities[j]->getDestroyed() && constructedEntities[j]->getType() == "Player")
		{
			nLives--;
			delete constructedEntities[j];
			constructedEntities.erase(constructedEntities.begin() + j);
			delete constructedControllers[j];
			constructedControllers.erase(constructedControllers.begin() + j);
			delete constructedCollisionHandlers[j];
			constructedCollisionHandlers.erase(constructedCollisionHandlers.begin() + j);
			playerDestroyed = true;
		}
		else if (constructedEntities[j]->getDestroyed())
		{
			delete constructedEntities[j];
			constructedEntities.erase(constructedEntities.begin() + j);
			delete constructedControllers[j];
			constructedControllers.erase(constructedControllers.begin() + j);
			delete constructedCollisionHandlers[j];
			constructedCollisionHandlers.erase(constructedCollisionHandlers.begin() + j);
		}
		else
			j++;

		if(playerDestroyed && nLives >= 0)
		{
			spawnPlayer();
			playerDestroyed = false;
		}
	}

	bool playerServed = false;
	auto playerIt = find_if(constructedEntities.begin(), constructedEntities.end(), [](Entity* e){ return e->getType() == "Player"; });
	unsigned playerPos = playerIt - constructedEntities.begin();
	for(unsigned i = 0; i < constructedControllers.size(); i++)
	{
		if(constructedControllers[i] != nullptr && i != playerPos)
			constructedControllers[i]->processAction();
		else if(constructedControllers[i] != nullptr && i == playerPos && !playerServed)
		{
			constructedControllers[i]->processAction();
			playerServed = true;
			playerIt = find_if(constructedEntities.begin(), constructedEntities.end(), [](Entity* e){ return e->getType() == "Player"; });
			playerPos = playerIt - constructedEntities.begin();
		}
	}

	for(unsigned i = 0; i < constructedCollisionHandlers.size(); i++)
	{
		if(constructedCollisionHandlers[i] != nullptr)
		{
			Actor* tmp = dynamic_cast<Actor*>(constructedCollisionHandlers[i]->getEntity());
			bool chk = false;
			for(j = 0; j < constructedEntities.size(); j++)
			{
				if(constructedCollisionHandlers[i]->getEntity() != constructedEntities[j])
				{
					if(constructedCollisionHandlers[i]->handleCollision(constructedEntities[j]))
					{
						chk = true;
					}
				}
			}

			if(!chk && tmp->getType() == "Player")
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
}

void Level::constructLevel()
{
	for(int i = 0; i < dim_y; i++)
	{
		for(int j = 0; j < dim_x; j++)
		{
			if(tileMap[i][j] != "P")
			{
				std::unordered_map<std::string, EntityDescriptor*>::iterator it;
				it = entities.find(tileMap[i][j]);
				if(it != entities.end())
				{
					Entity* tmpEntity = it->second->getDescripted((float)j * (float)16, (float)i * (float)16 + (float)24);
					if(it->second->getDescriptedController() != nullptr)
					{
						Controller* tmpController = it->second->getDescriptedController();
						Action* action = it->second->getDescriptedAction();
						tmpEntity->setSpawner(new LevelSpawner(this));
						action->setEntity(tmpEntity);
						tmpController->changeAction(action);
						constructedControllers.push_back(tmpController);
					}
					else
						constructedControllers.push_back(nullptr);

					if(it->second->getDescriptedCollisionHandler() != nullptr)
					{
						CollisionHandler* tmpCollisionhandler = it->second->getDescriptedCollisionHandler();
						tmpCollisionhandler->setEntity(tmpEntity);
						constructedCollisionHandlers.push_back(tmpCollisionhandler);
					}
					else
						constructedCollisionHandlers.push_back(nullptr);

					constructedEntities.push_back(tmpEntity);
				}
			}
		}
	}

	//entities.clear();
}

void Level::registerEntity(std::string key, EntityDescriptor* e) { entities[key] = e; }

void Level::setLevelbackground(ALLEGRO_BITMAP* levelBackground) { this->levelBackground = levelBackground; }

void Level::spawn(std::string entity, double x, double y)
{
	auto playerIt = find_if(constructedEntities.begin(), constructedEntities.end(), [](Entity* e){ return e->getType() == "Player"; });
	if(playerIt != constructedEntities.end())
	{
		unsigned playerPos = playerIt - constructedEntities.begin();
		std::unordered_map<std::string, EntityDescriptor*>::iterator it;
		it = entities.find(entity);
		if(it != entities.end())
		{
			Entity* tmpEntity = it->second->getDescripted(x, y);
			if(it->second->getDescriptedController() != nullptr)
			{
				Controller* tmpController = it->second->getDescriptedController();
				Action* action = it->second->getDescriptedAction();
				action->setEntity(tmpEntity);
				tmpEntity->setSpawner(new LevelSpawner(this));
				tmpController->changeAction(action);
				constructedControllers.insert(constructedControllers.begin() + playerPos, tmpController);
			}
			else
				constructedControllers.insert(constructedControllers.begin() + playerPos, nullptr);

			if(it->second->getDescriptedCollisionHandler() != nullptr)
			{
				CollisionHandler* tmpCollisionhandler = it->second->getDescriptedCollisionHandler();
				tmpCollisionhandler->setEntity(tmpEntity);
				constructedCollisionHandlers.insert(constructedCollisionHandlers.begin() + playerPos, tmpCollisionhandler);
			}
			else
				constructedCollisionHandlers.insert(constructedCollisionHandlers.begin() + playerPos, nullptr);

			constructedEntities.insert(playerIt, tmpEntity);
		}
	}
}

void Level::spawnPlayer()
{
	std::unordered_map<std::string, EntityDescriptor*>::iterator it;
	it = entities.find("P");
	for(int i = 0; i < dim_y; i++)
	{
		for(int j = 0; j < dim_x; j++)
		{
			if(tileMap[i][j] == "P")
			{
				Entity* tmpEntity = it->second->getDescripted((float)j * (float)16, (float)i * (float)16 + (float)24);
				if(it->second->getDescriptedController() != nullptr)
				{
					Controller* tmpController = it->second->getDescriptedController();
					Action* action = it->second->getDescriptedAction();
					tmpEntity->setSpawner(new LevelSpawner(this));
					action->setEntity(tmpEntity);
					tmpController->changeAction(action);
					constructedControllers.push_back(tmpController);
				}
				else
					constructedControllers.push_back(nullptr);

				if(it->second->getDescriptedCollisionHandler() != nullptr)
				{
					CollisionHandler* tmpCollisionhandler = it->second->getDescriptedCollisionHandler();
					tmpCollisionhandler->setEntity(tmpEntity);
					constructedCollisionHandlers.push_back(tmpCollisionhandler);
				}
				else
					constructedCollisionHandlers.push_back(nullptr);

				constructedEntities.push_back(tmpEntity);
			}
		}
	}
}

void Level::clearLevel()
{
	constructedEntities.clear();
	constructedControllers.clear();
	constructedCollisionHandlers.clear();
}
