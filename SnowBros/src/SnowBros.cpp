//============================================================================
// Name        : SnowBros.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include "Player.h"
/*
 const int screenWidth = 800;
 const int screenHeight = 600;*/
const float FPS = 60;
const int BOUNCER_SIZE = 32;
/*enum MYKEYS {
 KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
 };*/

int main() {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;

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

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	//display = al_create_display(disp_data.width, disp_data.height);*/

	float windowWidth = disp_data.width;
	float windowHeight = disp_data.height;

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	display = al_create_display(windowWidth, windowHeight);
	al_clear_to_color(al_map_rgb(100, 100, 100));

	windowWidth = al_get_display_width(display);
	windowHeight = al_get_display_height(display);

	float sx = windowWidth / (float) screenWidth;
	float sy = windowHeight / (float) screenHeight;

	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);
	al_scale_transform(&trans, sx, sy);
	al_use_transform(&trans);

	if (!display) {
		std::cerr << "Failed to create display!";
		al_destroy_timer(timer);
		return -1;
	}

	float bouncer_x = 0;
	float bouncer_y = screenHeight - BOUNCER_SIZE;
	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);

	if (!bouncer) {
		std::cerr << "Failed to create bitmap!";
		al_destroy_timer(timer);
		al_destroy_display(display);
		return -1;
	}

	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(display));

	Player p(bouncer_x, bouncer_y, 6, 150, 10, 6, bouncer);

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

	al_clear_to_color(al_map_rgb(100, 100, 100));

	al_flip_display();

	al_start_timer(timer);

	//bool jumping = false;
	//bool falling = false;
	while (!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			p.onAction(key);
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

			al_clear_to_color(al_map_rgb(100, 100, 100));
			p.onRedraw();
			al_flip_display();
		}
	}
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
