/*
 * PlayerCollisionHandler.cpp
 *
 *  Created on: 9 ago 2019
 *      Author: Francesco
 */

#include "PlayerCollisionHandler.h"

PlayerCollisionHandler::PlayerCollisionHandler() { }

PlayerCollisionHandler::~PlayerCollisionHandler() { }

bool PlayerCollisionHandler::handleCollision(Entity* other)
{
	Actor* tmp = dynamic_cast<Actor*>(entity);
	if(checkCollision(other) == SIDE_DOWN && other->getType() == "Tile" && tmp->isFalling())
	{
//		double tmp_x1 = tmp->getPosX();
//		double tmp_y1 = tmp->getPosY();
//
//		double tmp_x2 = tmp_x1 + tmp->getDim()->x;
//		double tmp_y2 = tmp_y1;
//
//		double tmp_x3 = tmp_x1;
//		double tmp_y3 = tmp_y1 + tmp->getDim()->y;
//
//		double tmp_x4 = tmp_x2;
//		double tmp_y4 = tmp_y3;
//
//		double other_x1 = other->getPosX();
//		double other_y1 = other->getPosY();
//
//		double other_x2 = other_x1 + other->getDim()->x;
//		double other_y2 = other_y1;
//
//		double other_x3 = other_x1;
//		double other_y3 = other_y1 + other->getDim()->y;
//
//		double other_x4 = other_x2;
//		double other_y4 = other_y3;
//
//		double dist = sqrt(pow(tmp_x3 - other_x1, 2) + pow(tmp_y3 - other_y1, 2));

		tmp->setPosY(other->getPosY() - tmp->getDim()->y);
		tmp->setCanJump(true);
		tmp->setFalling(false);
		return true;
	}

	else if(!checkCollision(other))
	{
//		if(!tmp->isJumping())
//		{
//			tmp->setCanFall(true);
//			tmp->setCanJump(false);
//		}
//		else
//		{
//			tmp->setCanFall(false);
//			tmp->setCanJump(true);
//		}

		return false;
	}
}

