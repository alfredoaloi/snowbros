//============================================================================
// Name        : SnowBros.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : SnowBros
// Dimensioni = 256X224
//============================================================================
#include <iostream>
#include <climits>
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
#include "EnemyAction.h"
#include "TileDescriptor.h"
#include "ActorDescriptor.h"
#include "SpritesheetManager.h"
#include "PlayerCollisionHandler.h"
#include "BulletCollisionHandler.h"
#include "EnemyCollisionHandler.h"

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

enum GAME_STATE
{
	MAIN_MENU,
	MAIN_MENU_TRANSITION,
	IN_GAME,
	LEVEL_TRANSITION,
	END_MENU
};
typedef GAME_STATE GameState;

int main() {
	srand(time(0));
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

	// player
	SpritesheetManager* playerSpritesheetManager = new SpritesheetManager();
	playerSpritesheetManager->setNewSpritesheet("camminaL", new Spritesheet(al_load_bitmap("./res/player/camminaL.bmp"), 3));
	playerSpritesheetManager->setNewSpritesheet("camminaR", new Spritesheet(al_load_bitmap("./res/player/camminaR.bmp"), 3));
	playerSpritesheetManager->setNewSpritesheet("fermoL", new Spritesheet(al_load_bitmap("./res/player/fermoL.bmp"), 1));
	playerSpritesheetManager->setNewSpritesheet("fermoR", new Spritesheet(al_load_bitmap("./res/player/fermoR.bmp"), 1));
	playerSpritesheetManager->setNewSpritesheet("morto", new Spritesheet(al_load_bitmap("./res/player/morto.bmp"), 3));
	playerSpritesheetManager->setNewSpritesheet("respawn", new Spritesheet(al_load_bitmap("./res/player/respawn.bmp"), 4));
	playerSpritesheetManager->setNewSpritesheet("saltaL", new Spritesheet(al_load_bitmap("./res/player/saltaL.bmp"), 5));
	playerSpritesheetManager->setNewSpritesheet("saltaR", new Spritesheet(al_load_bitmap("./res/player/saltaR.bmp"), 5));
	playerSpritesheetManager->setNewSpritesheet("sparaL", new Spritesheet(al_load_bitmap("./res/player/sparaL.bmp"), 2));
	playerSpritesheetManager->setNewSpritesheet("sparaR", new Spritesheet(al_load_bitmap("./res/player/sparaR.bmp"), 2));
	playerSpritesheetManager->setNewSpritesheet("spingeL", new Spritesheet(al_load_bitmap("./res/player/spingeL.bmp"), 3));
	playerSpritesheetManager->setNewSpritesheet("spingeR", new Spritesheet(al_load_bitmap("./res/player/spingeR.bmp"), 3));
	playerSpritesheetManager->setWidth(25);
	playerSpritesheetManager->setHeight(30);

	// player bullet
	SpritesheetManager* bulletSpritesheetManager = new SpritesheetManager();
	bulletSpritesheetManager->setNewSpritesheet("left", new Spritesheet(al_load_bitmap("./res/others/proiettileL.bmp"), 1));
	bulletSpritesheetManager->setNewSpritesheet("right", new Spritesheet(al_load_bitmap("./res/others/proiettileR.bmp"), 1));
	bulletSpritesheetManager->setWidth(6);
	bulletSpritesheetManager->setHeight(11);

	// enemy 1
	SpritesheetManager* enemy1SpritesheetManager = new SpritesheetManager();
	enemy1SpritesheetManager->setNewSpritesheet("camminaL", new Spritesheet(al_load_bitmap("./res/enemy1/camminaL.bmp"), 2));
	enemy1SpritesheetManager->setNewSpritesheet("camminaR", new Spritesheet(al_load_bitmap("./res/enemy1/camminaR.bmp"), 2));
	enemy1SpritesheetManager->setNewSpritesheet("fermoL", new Spritesheet(al_load_bitmap("./res/enemy1/fermoL.bmp"), 1));
	enemy1SpritesheetManager->setNewSpritesheet("fermoR", new Spritesheet(al_load_bitmap("./res/enemy1/fermoR.bmp"), 1));
	enemy1SpritesheetManager->setNewSpritesheet("mortoL", new Spritesheet(al_load_bitmap("./res/enemy1/mortoL.bmp"), 1));
	enemy1SpritesheetManager->setNewSpritesheet("mortoR", new Spritesheet(al_load_bitmap("./res/enemy1/mortoR.bmp"), 1));
	enemy1SpritesheetManager->setNewSpritesheet("saltaL", new Spritesheet(al_load_bitmap("./res/enemy1/saltaL.bmp"), 1));
	enemy1SpritesheetManager->setNewSpritesheet("saltaR", new Spritesheet(al_load_bitmap("./res/enemy1/saltaR.bmp"), 1));
	enemy1SpritesheetManager->setWidth(25);
	enemy1SpritesheetManager->setHeight(30);

	// enemy 2
	SpritesheetManager* enemy2SpritesheetManager = new SpritesheetManager();
	enemy2SpritesheetManager->setNewSpritesheet("camminaL", new Spritesheet(al_load_bitmap("./res/enemy2/camminaL.bmp"), 2));
	enemy2SpritesheetManager->setNewSpritesheet("camminaR", new Spritesheet(al_load_bitmap("./res/enemy2/camminaR.bmp"), 2));
	enemy2SpritesheetManager->setNewSpritesheet("fermoL", new Spritesheet(al_load_bitmap("./res/enemy2/fermoL.bmp"), 1));
	enemy2SpritesheetManager->setNewSpritesheet("fermoR", new Spritesheet(al_load_bitmap("./res/enemy2/fermoR.bmp"), 1));
	enemy2SpritesheetManager->setNewSpritesheet("mortoL", new Spritesheet(al_load_bitmap("./res/enemy2/mortoL.bmp"), 1));
	enemy2SpritesheetManager->setNewSpritesheet("mortoR", new Spritesheet(al_load_bitmap("./res/enemy2/mortoR.bmp"), 1));
	enemy2SpritesheetManager->setNewSpritesheet("saltaL", new Spritesheet(al_load_bitmap("./res/enemy2/saltaL.bmp"), 1));
	enemy2SpritesheetManager->setNewSpritesheet("saltaR", new Spritesheet(al_load_bitmap("./res/enemy2/saltaR.bmp"), 1));
	enemy2SpritesheetManager->setNewSpritesheet("sparaL", new Spritesheet(al_load_bitmap("./res/enemy2/sparaL.bmp"), 1));
	enemy2SpritesheetManager->setNewSpritesheet("sparaR", new Spritesheet(al_load_bitmap("./res/enemy2/sparaR.bmp"), 1));
	enemy2SpritesheetManager->setWidth(24);
	enemy2SpritesheetManager->setHeight(30);

	// enemy 3
	SpritesheetManager* enemy3SpritesheetManager = new SpritesheetManager();
	enemy3SpritesheetManager->setNewSpritesheet("camminaL", new Spritesheet(al_load_bitmap("./res/enemy3/camminaL.bmp"), 3));
	enemy3SpritesheetManager->setNewSpritesheet("camminaR", new Spritesheet(al_load_bitmap("./res/enemy3/camminaR.bmp"), 3));
	enemy3SpritesheetManager->setNewSpritesheet("fermoL", new Spritesheet(al_load_bitmap("./res/enemy3/fermoL.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("fermoR", new Spritesheet(al_load_bitmap("./res/enemy3/fermoR.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("saltaL", new Spritesheet(al_load_bitmap("./res/enemy3/saltaL.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("saltaR", new Spritesheet(al_load_bitmap("./res/enemy3/saltaR.bmp"), 1));
	enemy3SpritesheetManager->setWidth(25);
	enemy3SpritesheetManager->setHeight(30);

	// player bullet
	SpritesheetManager* fireSpritesheetManager = new SpritesheetManager();
	fireSpritesheetManager->setNewSpritesheet("left", new Spritesheet(al_load_bitmap("./res/others/proiettileFuocoL.bmp"), 1));
	fireSpritesheetManager->setNewSpritesheet("right", new Spritesheet(al_load_bitmap("./res/others/proiettileFuocoR.bmp"), 1));
	fireSpritesheetManager->setWidth(25);
	fireSpritesheetManager->setHeight(16);

	l.registerEntity("T", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "T"));
	l.registerEntity("TL", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TL"));
	l.registerEntity("TR", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TR"));
	l.registerEntity("P", new ActorDescriptor(new Dimensions(25, 30),  6, 32, 10, 10, new Controller(key), new PlayerAction(), new PlayerCollisionHandler(), playerSpritesheetManager, "Player"));
	l.registerEntity("BL", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletLeft"));
	l.registerEntity("BR", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletRight"));
	l.registerEntity("E1", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy1SpritesheetManager, "Enemy1"));
	l.registerEntity("E2", new ActorDescriptor(new Dimensions(24, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy2SpritesheetManager, "Enemy2"));
	l.registerEntity("E3", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy2SpritesheetManager, "Enemy3"));
	l.registerEntity("FL", new ActorDescriptor(new Dimensions(25, 16),  6, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), fireSpritesheetManager, "FireLeft"));
	l.registerEntity("FR", new ActorDescriptor(new Dimensions(25, 16),  6, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), fireSpritesheetManager, "FireRight"));

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

	//al_draw_bitmap(al_load_bitmap("./res/Livello1.bmp"), 0, 24, 0);

	al_flip_display();

	al_start_timer(timer);

	int playerScore = 0, highScore = 50, nLives = 2, nReplays = 9;

	int blinkCounter = 0;
	int infBlink = 0, supBlink = 1;

	unsigned transparency = 0;
	int tmp = 0;

	GameState gameState = MAIN_MENU;

	while (!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			if(gameState == MAIN_MENU)
			{
				if(key[KEY_SPACE])
				{
					gameState = MAIN_MENU_TRANSITION;
					blinkCounter = 0;
					infBlink = 0;
					supBlink = 1;

					transparency = 0;
					tmp = 0;
				}
			}
			else if(gameState == IN_GAME)
			{
				if(nLives < 0)
				{
					if(key[KEY_SPACE])
					{
						nLives = 2;
						nReplays--;
					}
				}

				l.processLevel(playerScore, highScore, nLives, nReplays);
			}

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
			ALLEGRO_TRANSFORM trans2;

			if(gameState == MAIN_MENU)
			{
				al_draw_bitmap(al_load_bitmap("./res/MainMenu.bmp"), 0, 0, 0);
				if(blinkCounter >= INT_MAX)
					blinkCounter = 0;

				if(blinkCounter >= 20 * infBlink && blinkCounter <= 20 * supBlink)
				{
					al_identity_transform(&trans2);
					al_translate_transform(&trans2, 87, 168);
					al_use_transform(&trans2);
					al_draw_text(font, al_map_rgb(255, 80, 0), 0, 0, 0, "PRESS SPACE");
					al_identity_transform(&trans2);
					al_translate_transform(&trans2, 86, 168);
					al_use_transform(&trans2);
					al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "PRESS SPACE");
					blinkCounter++;
				}
				else
				{
					if(blinkCounter >= 20 * infBlink && blinkCounter <= 20 * (supBlink + 1))
						blinkCounter++;
					else
					{
						infBlink = supBlink + 1;
						supBlink = supBlink + 2;
					}
				}
				al_identity_transform(&trans2);
				al_use_transform(&trans2);
			}
			else if (gameState == MAIN_MENU_TRANSITION)
			{
				if(transparency <= 255)
				{
					al_draw_filled_rectangle(0, 0, 256, 224, al_map_rgba(0, 0, 0, transparency));
				}
				else
				{
					al_draw_text(font, al_map_rgb(255, 255, 255), 128, 112, ALLEGRO_ALIGN_CENTRE, "LEVEL 1");
					if(tmp > 20)
						gameState = IN_GAME;
				}

				transparency += 25;
				tmp++;
			}
			else if(gameState == IN_GAME)
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_hold_bitmap_drawing(1);
				l.drawLevel();
				al_hold_bitmap_drawing(0);

				//DISEGNO INTERFACCIA GRAFICA

				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 18, 6);
				al_use_transform(&trans2);
				al_draw_text(font, al_map_rgb(255, 80, 0), 0, 0, 0, "1P");
				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 18, 14);
				al_use_transform(&trans2);
				al_draw_textf(font, al_map_rgb(255, 80, 0), 0, 0, 0, "%07d", playerScore);
				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 17, 6);
				al_use_transform(&trans2);
				al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "1P");
				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 17, 14);
				al_use_transform(&trans2);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "%07d", playerScore);

				if(nLives < 0)
				{
					if(blinkCounter >= INT_MAX)
						blinkCounter = 0;

					if(blinkCounter >= 20 * infBlink && blinkCounter <= 20 * supBlink)
					{
						al_identity_transform(&trans2);
						al_scale_transform(&trans2, 1, 0.77);
						al_translate_transform(&trans2, 82, 14);
						al_use_transform(&trans2);
						al_draw_textf(font, al_map_rgb(255, 80, 0), 0, 0, 0, "%d", nReplays);
						al_identity_transform(&trans2);
						al_scale_transform(&trans2, 1, 0.77);
						al_translate_transform(&trans2, 81, 14);
						al_use_transform(&trans2);
						al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "%d", nReplays);
						blinkCounter++;
					}
					else
					{
						if(blinkCounter >= 20 * infBlink && blinkCounter <= 20 * (supBlink + 1))
							blinkCounter++;
						else
						{
							infBlink = supBlink + 1;
							supBlink = supBlink + 2;
						}
					}
				}
				else
				{
					al_identity_transform(&trans2);
					al_scale_transform(&trans2, 1, 0.77);
					al_translate_transform(&trans2, 82, 14);
					al_use_transform(&trans2);
					al_draw_textf(font, al_map_rgb(255, 80, 0), 0, 0, 0, "%d", nLives);
					al_identity_transform(&trans2);
					al_scale_transform(&trans2, 1, 0.77);
					al_translate_transform(&trans2, 81, 14);
					al_use_transform(&trans2);
					al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "%d", nLives);
					blinkCounter = 0;
					infBlink = 0;
					supBlink = 1;
				}

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
				al_draw_textf(font, al_map_rgb(255, 80, 0), 0, 0, 0, "%07d", highScore);
				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 97, 14);
				al_use_transform(&trans2);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "%07d", highScore);
				al_identity_transform(&trans2);
				al_use_transform(&trans2);
				//al_use_transform(&trans);

				//
			}

			al_flip_display();
		}
	}
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
