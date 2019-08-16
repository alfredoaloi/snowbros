/*
 * Entity.cpp
 *
 *  Created on: 19 apr 2019
 *      Author: francesco
 */

#include "Entity.h"

Entity::Entity() { }

void Entity::onRedraw() { }

Entity::Entity(float x, float y, Dimensions* d, std::string t) : pos_x(x), pos_y(y), dim(d), type(t), spawner(nullptr)
{

}

Entity::Entity(Entity* e)
{
	this->pos_x = e->pos_x;
	this->pos_y = e->pos_y;
	this->dim = e->dim;
	this->type = e->type;
	this->spawner = e->spawner;
}

Entity::~Entity() { }

/*void Entity::setAction(Action*& action) {
	this->action = action;
}*/

Dimensions* Entity::getDim() const {
	return dim;
}

void Entity::setDim(Dimensions* dim) {
	this->dim = dim;
}

float Entity::getPosX() const {
	return pos_x;
}

void Entity::setPosX(float posX) {
	pos_x = posX;
}

float Entity::getPosY() const {
	return pos_y;
}

void Entity::setPosY(float posY) {
	pos_y = posY;
}

std::string Entity::getType() { return type; }

Spawner* Entity::getSpawner() { return spawner; }

void Entity::setSpawner(Spawner* spawner) { this->spawner = spawner; }

void Entity::setDestroyed(bool destroyed) { this->destroyed = destroyed; }

bool Entity::getDestroyed() { return destroyed; }
