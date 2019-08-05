//============================================================================
// Name        : SnowBros.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : SnowBros
//============================================================================
#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include "Actor.h"
#include "Level.h"
#include "Controller.h"
#include "PlayerAction.h"
#include "TileDescriptor.h"
#include "SpritesheetManager.h"

/*extern const int screenHeight;
extern const int screenWidth;*/
const float FPS = 60.0;
const int BOUNCER_SIZE = 50;
/*enum MYKEYS {
 KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
 };*/

void collisionDetection(Actor& a1, Actor& a2)
{
	if ((a1.getPosX() > a2.getPosX() + a2.getDim().x - 1) || // is b1 on the right side of b2?
		(a1.getPosY() > a2.getPosY() + a2.getDim().y - 1) || // is b1 under b2?
		(a2.getPosX() > a1.getPosX() + a1.getDim().x - 1) || // is b2 on the right side of b1?
		(a2.getPosY() > a1.getPosY() + a1.getDim().y - 1))   // is b2 under b1?
	{
		return;
	}

	float x1 = a1.getPosX() + a1.getDim().x / 2;
	float y1 = a1.getPosY() + a1.getDim().y / 2;
	float x2 = a2.getPosX() + a2.getDim().x / 2;
	float y2 = a2.getPosY() + a2.getDim().y / 2;

	float x3 = x1;
	float y3 = y2;
	float x4 = x2;
	float y4 = y1;

	al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 255, 255), 1);
	al_draw_line(x2, y2, x3, y3, al_map_rgb(255, 0, 0), 1);
	al_draw_line(x2, y2, x4, y4, al_map_rgb(0, 0, 255), 1);

	float distX = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
	float distY = sqrt(pow(x2 - x4, 2) + pow(y2 - y4, 2));

	if(distX <= a2.getDim().x && x1 < x2 && (y1 > y2 - a2.getDim().y / 2 && y1 < y2 + a2.getDim().y / 2))
		a1.setPosX(a1.getPosX() - (a2.getDim().x - distX));
	if(distX <= a2.getDim().x && x1 > x2 && (y1 > y2 - a2.getDim().y / 2 && y1 < y2 + a2.getDim().y / 2))
		a1.setPosX(a1.getPosX() + (a2.getDim().x - distX));
	if(distY <= a2.getDim().y && y1 < y2 && (x1 > x2 - a2.getDim().x / 2 && x1 < x2 + a2.getDim().x / 2))
		a1.setPosY(a1.getPosY() - (a2.getDim().y - distY));
}

int main() {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *bouncer2 = NULL;

	al_init_image_addon();

	Level l("./res/Level1.txt");

	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	if (!al_init()) {
		std::cerr << "Failed to initialize allegro!";
		return -1;
	}

	if (!al_install_keyboard()) {
		std::cerr << "Failed to initialize keyboard!";
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		std::cerr << "Failed to initialize timer!";
		return -1;
	}

	SpritesheetManager m;
	m.setNewSpritesheet("player1", new Spritesheet(al_load_bitmap("./res/player4.bmp"), 4));
	m.setWidth(50);
	m.setHeight(50);

	l.registerEntity("e1", new TileDescriptor(Dimensions::createDimensions(80, 60), al_load_bitmap("./res/tile1.bmp")));

	al_init_primitives_addon();
//	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
//	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
//	//display = al_create_display(disp_data.width, disp_data.height);*/
//
//	float windowWidth = disp_data.width;
//	float windowHeight = disp_data.height;
//
//	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
//	display = al_create_display(windowWidth, windowHeight);
//	al_clear_to_color(al_map_rgb(100, 100, 100));
//
//	windowWidth = al_get_display_width(display);
//	windowHeight = al_get_display_height(display);
//
//	float sx = windowWidth / (float) screenWidth;
//	float sy = windowHeight / (float) screenHeight;
//
//	//Provare il metodo dello stretched buffer
//	ALLEGRO_TRANSFORM trans;
//	al_identity_transform(&trans);
//	al_scale_transform(&trans, sx, sy);
//	al_use_transform(&trans);

	display = al_create_display(800, 600);

	if (!display) {
		std::cerr << "Failed to create display!";
		al_destroy_timer(timer);
		return -1;
	}

	//Da far fare ai livelli
	float bouncer_x = 0;
	float bouncer_y = screenHeight - BOUNCER_SIZE;
	bouncer = al_create_bitmap(50, 50);
	bouncer2 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);

	if (!bouncer) {
		std::cerr << "Failed to create bitmap!";
		al_destroy_timer(timer);
		al_destroy_display(display);
		return -1;
	}

//	ALLEGRO_BITMAP* spritesheet = al_load_bitmap("./res/player1.bmp");
//	al_set_target_bitmap(bouncer);
//	al_draw_bitmap_region(spritesheet, 0, 0, 28, 28, 0, 0, 0);
	al_set_target_bitmap(bouncer2);
	al_clear_to_color(al_map_rgb(255, 0, 255));

	Actor p(bouncer_x, bouncer_y, Dimensions::createDimensions(50, 50), 6, 150, 10, 10, bouncer, new PlayerAction());
	Actor p2(bouncer_x + 100, bouncer_y, Dimensions::createDimensions(50, 50), 6, 150, 10, 6, bouncer2, nullptr);
	//

	event_queue = al_create_event_queue();
	if (!event_queue) {
		std::cerr << "Failed to create event queue!";
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_bitmap(bouncer);
		return -1;
	}
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//Lo sfondo non serve dopo aver gestito le mappe
	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(100, 100, 100));

	al_flip_display();

	al_start_timer(timer);

	//bool jumping = false;
	//bool falling = false;
	Controller* c = new Controller(p.getAction(), key);
	while (!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			//p.onAction(key);
			l.processLevel();
			c->processAction();
			collisionDetection(p, p2);
			redraw = true;
		} else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			m.selectCurrentSpritesheet("player1");
			m.nextSprite(bouncer);
			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(100, 100, 100));
			l.drawLevel();
			p.onRedraw();
			p2.onRedraw();


			al_flip_display();
		}
	}
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
