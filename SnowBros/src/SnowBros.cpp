//============================================================================
// Name        : SnowBros.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : SnowBros
// Dimensioni = 256X224
//============================================================================
#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "Actor.h"
#include "Level.h"
#include "Controller.h"
#include "PlayerAction.h"
#include "BulletAction.h"
#include "TileDescriptor.h"
#include "ActorDescriptor.h"
#include "SpritesheetManager.h"
#include "PlayerCollisionHandler.h"
#include "BulletCollisionHandler.h"

/*extern const int screenHeight;
extern const int screenWidth;*/
const float FPS = 10.0;
const int BOUNCER_SIZE = 30;
/*enum MYKEYS {
 KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
 };*/

//void collisionDetection(Actor& a1, Actor& a2)
//{
//	if ((a1.getPosX() > a2.getPosX() + a2.getDim().x - 1) || // is b1 on the right side of b2?
//		(a1.getPosY() > a2.getPosY() + a2.getDim().y - 1) || // is b1 under b2?
//		(a2.getPosX() > a1.getPosX() + a1.getDim().x - 1) || // is b2 on the right side of b1?
//		(a2.getPosY() > a1.getPosY() + a1.getDim().y - 1))   // is b2 under b1?
//	{
//		return;
//	}
//
//	float x1 = a1.getPosX() + a1.getDim().x / 2;
//	float y1 = a1.getPosY() + a1.getDim().y / 2;
//	float x2 = a2.getPosX() + a2.getDim().x / 2;
//	float y2 = a2.getPosY() + a2.getDim().y / 2;
//
//	float x3 = x1;
//	float y3 = y2;
//	float x4 = x2;
//	float y4 = y1;
//
//	float distX = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
//	float distY = sqrt(pow(x2 - x4, 2) + pow(y2 - y4, 2));
//
//	if(distX <= a2.getDim().x && x1 < x2 && (y1 > y2 - a2.getDim().y / 2 && y1 < y2 + a2.getDim().y / 2))
//		a1.setPosX(a1.getPosX() - (a2.getDim().x - distX));
//	if(distX <= a2.getDim().x && x1 > x2 && (y1 > y2 - a2.getDim().y / 2 && y1 < y2 + a2.getDim().y / 2))
//		a1.setPosX(a1.getPosX() + (a2.getDim().x - distX));
//	if(distY <= a2.getDim().y && y1 < y2 && (x1 > x2 - a2.getDim().x / 2 && x1 < x2 + a2.getDim().x / 2))
//		a1.setPosY(a1.getPosY() - (a2.getDim().y - distY));
//}

int main() {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT* font;

	al_init_image_addon();
	al_init_font_addon();

	bool key[5] = { false, false, false, false, false };
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

	Level l("./res/Level1.txt", al_load_bitmap("./res/Livello1.bmp"));

	SpritesheetManager* m = new SpritesheetManager();
	m->setNewSpritesheet("camminaL", new Spritesheet(al_load_bitmap("./res/player/camminaL.bmp"), 3));
	m->setNewSpritesheet("camminaR", new Spritesheet(al_load_bitmap("./res/player/camminaR.bmp"), 3));
	m->setNewSpritesheet("fermoL", new Spritesheet(al_load_bitmap("./res/player/fermoL.bmp"), 1));
	m->setNewSpritesheet("fermoR", new Spritesheet(al_load_bitmap("./res/player/fermoR.bmp"), 1));
	m->setNewSpritesheet("morto", new Spritesheet(al_load_bitmap("./res/player/morto.bmp"), 3));
	m->setNewSpritesheet("respawn", new Spritesheet(al_load_bitmap("./res/player/respawn.bmp"), 4));
	m->setNewSpritesheet("saltaL", new Spritesheet(al_load_bitmap("./res/player/saltaL.bmp"), 5));
	m->setNewSpritesheet("saltaR", new Spritesheet(al_load_bitmap("./res/player/saltaR.bmp"), 5));
	m->setNewSpritesheet("sparaL", new Spritesheet(al_load_bitmap("./res/player/sparaL.bmp"), 2));
	m->setNewSpritesheet("sparaR", new Spritesheet(al_load_bitmap("./res/player/sparaR.bmp"), 2));
	m->setNewSpritesheet("spingeL", new Spritesheet(al_load_bitmap("./res/player/spingeL.bmp"), 3));
	m->setNewSpritesheet("spingeR", new Spritesheet(al_load_bitmap("./res/player/spingeR.bmp"), 3));
	m->setWidth(25);
	m->setHeight(30);

	SpritesheetManager* m1 = new SpritesheetManager();
	m1->setNewSpritesheet("left", new Spritesheet(al_load_bitmap("./res/others/proiettileL.bmp"), 1));
	m1->setWidth(6);
	m1->setHeight(11);

	SpritesheetManager* m2 = new SpritesheetManager();
	m2->setNewSpritesheet("right", new Spritesheet(al_load_bitmap("./res/others/proiettileR.bmp"), 1));
	m2->setWidth(6);
	m2->setHeight(11);

	l.registerEntity("T", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "T"));
	l.registerEntity("TL", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TL"));
	l.registerEntity("TR", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TR"));
	l.registerEntity("P", new ActorDescriptor(new Dimensions(25, 30),  6, 32, 10, 10, new Controller(key), new PlayerAction(), new PlayerCollisionHandler(), m, "Player"));
	l.registerEntity("BL", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), m1, "BulletLeft"));
	l.registerEntity("BR", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), m2, "BulletRight"));

//	al_init_primitives_addon();
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

	display = al_create_display(256, 224);

	if (!display) {
		std::cerr << "Failed to create display!";
		al_destroy_timer(timer);
		return -1;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		std::cerr << "Failed to create event queue!";
		al_destroy_timer(timer);
		al_destroy_display(display);
		return -1;
	}
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	font = al_load_font("./res/fixed_font.tga", 0, 0);

	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_bitmap(al_load_bitmap("./res/Livello1.bmp"), 0, 24, 0);

	al_flip_display();

	al_start_timer(timer);

	while (!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			l.processLevel();
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
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
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
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_hold_bitmap_drawing(1);
			l.drawLevel();
			al_hold_bitmap_drawing(0);

			//DISEGNO INTERFACCIA GRAFICA
			ALLEGRO_TRANSFORM trans2;
			al_identity_transform(&trans2);
			al_scale_transform(&trans2, 1, 0.77);
			al_translate_transform(&trans2, 18, 6);
			al_use_transform(&trans2);
			al_draw_text(font, al_map_rgb(255, 80, 0), 0, 0, 0, "1P");
			al_identity_transform(&trans2);
			al_scale_transform(&trans2, 1, 0.77);
			al_translate_transform(&trans2, 18, 14);
			al_use_transform(&trans2);
			al_draw_textf(font, al_map_rgb(255, 80, 0), 0, 0, 0, "%07d", 0);
			al_identity_transform(&trans2);
			al_scale_transform(&trans2, 1, 0.77);
			al_translate_transform(&trans2, 17, 6);
			al_use_transform(&trans2);
			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "1P");
			al_identity_transform(&trans2);
			al_scale_transform(&trans2, 1, 0.77);
			al_translate_transform(&trans2, 17, 14);
			al_use_transform(&trans2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "%07d", 0);
			al_identity_transform(&trans2);
			al_scale_transform(&trans2, 1, 0.77);
			al_translate_transform(&trans2, 82, 14);
			al_use_transform(&trans2);
			al_draw_textf(font, al_map_rgb(255, 80, 0), 0, 0, 0, "%d", 2);
			al_identity_transform(&trans2);
			al_scale_transform(&trans2, 1, 0.77);
			al_translate_transform(&trans2, 81, 14);
			al_use_transform(&trans2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "%d", 2);
			al_identity_transform(&trans2);
			al_scale_transform(&trans2, 1, 0.77);
			al_translate_transform(&trans2, 98, 6);
			al_use_transform(&trans2);
			al_draw_text(font, al_map_rgb(255, 80, 0), 0, 0, 0, "HI");
			al_identity_transform(&trans2);
			al_scale_transform(&trans2, 1, 0.77);
			al_translate_transform(&trans2, 97, 6);
			al_use_transform(&trans2);
			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "HI");
			al_identity_transform(&trans2);
			al_scale_transform(&trans2, 1, 0.77);
			al_translate_transform(&trans2, 98, 14);
			al_use_transform(&trans2);
			al_draw_textf(font, al_map_rgb(255, 80, 0), 0, 0, 0, "%07d", 0);
			al_identity_transform(&trans2);
			al_scale_transform(&trans2, 1, 0.77);
			al_translate_transform(&trans2, 97, 14);
			al_use_transform(&trans2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "%07d", 0);
			al_identity_transform(&trans2);
			al_use_transform(&trans2);
			//al_use_transform(&trans);

			al_flip_display();
		}
	}
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
