/*
 * Actor.h
 *
 *  Created on: 17 mar 2019
 *      Author: francesco
 */

#ifndef ACTOR_H_
#define ACTOR_H_
#include <allegro5/allegro.h>
#include "Entity.h"
#include "SpritesheetManager.h"
#include <list>

const int screenWidth = 256;
const int screenHeight = 224;

enum LAST_DIRECTION {
	NO_DIRECTION_LEFT = 1,
	NO_DIRECTION_RIGHT = 1 << 1 ,
	LEFT = 1 << 2,
	RIGHT = 1 << 3,
	UP = 1 << 4,
	SHOOTING_LEFT = 1 << 5,
	SHOOTING_RIGHT = 1 << 6,
	JUMPING_LEFT = 1 << 7,
	JUMPING_RIGHT = 1 << 8,
	FALLING_LEFT = 1 << 9,
	FALLING_RIGHT = 1 << 10,
	SPAWN = 1 << 11,
	DOWN = 1 << 12,
	ROTOLA_LEFT = 1 << 13,
	ROTOLA_RIGHT = 1 << 14,
	SHOOTING = SHOOTING_LEFT | SHOOTING_RIGHT,
	NO_DIRECTION = NO_DIRECTION_LEFT | NO_DIRECTION_RIGHT,
	JUMPING = JUMPING_LEFT | JUMPING_RIGHT,
	FALLING = FALLING_LEFT | FALLING_RIGHT
};

enum LIVELLO_PALLA { NULLA, POCA, TANTA, PIENA, ROTOLA };

typedef LIVELLO_PALLA LivelloPalla;
typedef LAST_DIRECTION LastDirection;

class Actor : public Entity {
protected:
	bool immobile;
	bool spinge = false;
	bool jumping;
	bool falling;
	bool canJump;
	bool canFall;
	bool shooting;
	bool moving;
	bool spawning;
	float speed;
	float max_height;
	float f_speed; //falling speed
	float j_speed; //jumping speed
	ALLEGRO_BITMAP* bitmap;
	SpritesheetManager* spritesheetManager;
	LastDirection lastDirection;
	LivelloPalla livelloPalla = NULLA;

public:
	Actor(float x, float y, Dimensions* d, float s, float h, float f_s, float j_s, std::string t, SpritesheetManager* ssm) :
			Entity(x, y, d, t), speed(s), max_height(h), f_speed(f_s), j_speed(j_s), spritesheetManager(ssm)
	{
		bitmap = al_create_bitmap(d->x, d->y);
		lastDirection = SPAWN;
		livelloPalla = NULLA;

		immobile = false;
		jumping = false;
		falling = false;
		canJump = true;
		canFall = true;
		shooting = false;
		moving = false;
		spawning = true;
	}

	virtual ~Actor() { al_destroy_bitmap(bitmap); }
	void onRedraw() override { al_draw_bitmap(bitmap, pos_x, pos_y, 0); }

	ALLEGRO_BITMAP* getBitmap() const {
		return bitmap;
	}

	void setBitmap(ALLEGRO_BITMAP* bitmap) {
		this->bitmap = bitmap;
	}

	float get_f_speed() const {
		return f_speed;
	}

	void set_f_speed(float speed) {
		f_speed = speed;
	}

	bool isFalling() const {
		return falling;
	}

	void setFalling(bool falling = false) {
		this->falling = falling;
	}

	float get_j_speed() const {
		return j_speed;
	}

	void set_j_speed(float speed) {
		j_speed = speed;
	}

	bool isJumping() const {
		return jumping;
	}

	void setJumping(bool jumping = false) {
		this->jumping = jumping;
	}

	float getMaxHeight() const {
		return max_height;
	}

	void setMaxHeight(float maxHeight) {
		max_height = maxHeight;
	}

	float getSpeed() const {
		return speed;
	}

	void setSpeed(float speed) {
		this->speed = speed;
	}

	SpritesheetManager* getSpritesheetManager() const {
		return spritesheetManager;
	}

	void setSpritesheetManager(SpritesheetManager* spritesheetManager) {
		this->spritesheetManager = spritesheetManager;
	}

	LastDirection getLastDirection() const {
		return lastDirection;
	}

	void setLastDirection(LastDirection lastDirection) {
		this->lastDirection = lastDirection;
	}

	bool isCanFall() const {
		return canFall;
	}

	void setCanFall(bool canFall = true) {
		this->canFall = canFall;
	}

	bool isCanJump() const {
		return canJump;
	}

	void setCanJump(bool canJump = true) {
		this->canJump = canJump;
	}

	bool isMoving() const {
		return moving;
	}

	void setMoving(bool moving = false) {
		this->moving = moving;
	}

	bool isShooting() const {
		return shooting;
	}

	void setShooting(bool shooting = false) {
		this->shooting = shooting;
	}

	bool isSpawning() const {
		return spawning;
	}

	void setSpawning(bool spawning) {
		this->spawning = spawning;
	}

	bool getImmobile() { return immobile; }

	void setImmobile(bool immobile) { this->immobile = immobile; }

	LivelloPalla getLivelloPalla() { return livelloPalla; }

	void setLivelloPalla(LivelloPalla livelloPalla) { this->livelloPalla = livelloPalla; }

	bool getSpinge() { return spinge; }

	void setSpinge(bool spinge) { this->spinge = spinge; }
};

#endif /* ACTOR_H_ */
