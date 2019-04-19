#ifndef PLAYER_H_
#define PLAYER_H_

#include "Actor.h"

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

class Player: public Actor {
	bool jumping = false;
	bool falling = false;
public:
	Player(float, float, Dimensions, float, float, float, float, ALLEGRO_BITMAP*, Action*);
	~Player();
	//void onAction(bool[4]) override;
	void onRedraw() override;

	friend class PlayerAction;
};

#endif /* PLAYER_H_ */
