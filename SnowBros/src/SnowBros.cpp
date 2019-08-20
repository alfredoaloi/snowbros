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
#include "PowerupAction.h"
#include "TileDescriptor.h"
#include "ActorDescriptor.h"
#include "SpritesheetManager.h"
#include "PlayerCollisionHandler.h"
#include "BulletCollisionHandler.h"
#include "EnemyCollisionHandler.h"
#include "PowerupCollisionHandler.h"
#include "PlayerScore.h"

const float FPS = 10.0;
const int BOUNCER_SIZE = 30;

enum GAME_STATE
{
	MAIN_MENU,
	MAIN_MENU_TRANSITION,
	IN_GAME,
	IN_GAME_TRANSITION,
	LEVEL_TRANSITION,
	END_MENU,
	END_MENU_TRANSITION,
	GAME_OVER_MENU,
	GAME_OVER_MENU_TRANSITION
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

	bool key[6] = { false, false, false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	const int nLevels = 4;

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

	Level* levels[nLevels];

	levels[0] = new Level("./res/Level1.txt", al_load_bitmap("./res/Livello1.bmp"));
	levels[1] = new Level("./res/Level2.txt", al_load_bitmap("./res/Livello2.bmp"));
	levels[2] = new Level("./res/Level3.txt", al_load_bitmap("./res/Livello3.bmp"));
	levels[3] = new Level("./res/Level4.txt", al_load_bitmap("./res/Livello4.bmp"));

	// player
	SpritesheetManager* playerSpritesheetManager = new SpritesheetManager();
	playerSpritesheetManager->setNewSpritesheet("camminaL", new Spritesheet(al_load_bitmap("./res/player/camminaL.bmp"), 3));
	playerSpritesheetManager->setNewSpritesheet("camminaR", new Spritesheet(al_load_bitmap("./res/player/camminaR.bmp"), 3));
	playerSpritesheetManager->setNewSpritesheet("fermoL", new Spritesheet(al_load_bitmap("./res/player/fermoL.bmp"), 1));
	playerSpritesheetManager->setNewSpritesheet("fermoR", new Spritesheet(al_load_bitmap("./res/player/fermoR.bmp"), 1));
	playerSpritesheetManager->setNewSpritesheet("morto", new Spritesheet(al_load_bitmap("./res/player/morto.bmp"), 3));
	playerSpritesheetManager->setNewSpritesheet("respawn", new Spritesheet(al_load_bitmap("./res/player/respawn.bmp"), 4));
	playerSpritesheetManager->setNewSpritesheet("saltaL", new Spritesheet(al_load_bitmap("./res/player/veroSaltaL.bmp"), 1));
	playerSpritesheetManager->setNewSpritesheet("saltaR", new Spritesheet(al_load_bitmap("./res/player/veroSaltaR.bmp"), 1));
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
	enemy1SpritesheetManager->setNewSpritesheet("poca", new Spritesheet(al_load_bitmap("./res/others/pallaPoca.bmp"), 1));
	enemy1SpritesheetManager->setNewSpritesheet("tanta", new Spritesheet(al_load_bitmap("./res/others/pallaTanta.bmp"), 1));
	enemy1SpritesheetManager->setNewSpritesheet("piena", new Spritesheet(al_load_bitmap("./res/others/pallaPiena.bmp"), 1));
	enemy1SpritesheetManager->setNewSpritesheet("rotola", new Spritesheet(al_load_bitmap("./res/others/pallaRotola.bmp"), 4));
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
	enemy2SpritesheetManager->setNewSpritesheet("poca", new Spritesheet(al_load_bitmap("./res/others/pallaPoca.bmp"), 1));
	enemy2SpritesheetManager->setNewSpritesheet("tanta", new Spritesheet(al_load_bitmap("./res/others/pallaTanta.bmp"), 1));
	enemy2SpritesheetManager->setNewSpritesheet("piena", new Spritesheet(al_load_bitmap("./res/others/pallaPiena.bmp"), 1));
	enemy2SpritesheetManager->setNewSpritesheet("rotola", new Spritesheet(al_load_bitmap("./res/others/pallaRotola.bmp"), 4));
	enemy2SpritesheetManager->setWidth(25);
	enemy2SpritesheetManager->setHeight(30);

	// enemy 3
	SpritesheetManager* enemy3SpritesheetManager = new SpritesheetManager();
	enemy3SpritesheetManager->setNewSpritesheet("camminaL", new Spritesheet(al_load_bitmap("./res/enemy3/camminaL.bmp"), 3));
	enemy3SpritesheetManager->setNewSpritesheet("camminaR", new Spritesheet(al_load_bitmap("./res/enemy3/camminaR.bmp"), 3));
	enemy3SpritesheetManager->setNewSpritesheet("fermoL", new Spritesheet(al_load_bitmap("./res/enemy3/fermoL.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("fermoR", new Spritesheet(al_load_bitmap("./res/enemy3/fermoR.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("saltaL", new Spritesheet(al_load_bitmap("./res/enemy3/saltaL.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("mortoL", new Spritesheet(al_load_bitmap("./res/enemy3/mortoL.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("mortoR", new Spritesheet(al_load_bitmap("./res/enemy3/mortoR.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("saltaR", new Spritesheet(al_load_bitmap("./res/enemy3/saltaR.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("poca", new Spritesheet(al_load_bitmap("./res/others/pallaPoca.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("tanta", new Spritesheet(al_load_bitmap("./res/others/pallaTanta.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("piena", new Spritesheet(al_load_bitmap("./res/others/pallaPiena.bmp"), 1));
	enemy3SpritesheetManager->setNewSpritesheet("rotola", new Spritesheet(al_load_bitmap("./res/others/pallaRotola.bmp"), 4));
	enemy3SpritesheetManager->setWidth(25);
	enemy3SpritesheetManager->setHeight(30);

	// enemy 2 bullet
	SpritesheetManager* fireSpritesheetManager = new SpritesheetManager();
	fireSpritesheetManager->setNewSpritesheet("left", new Spritesheet(al_load_bitmap("./res/others/proiettileFuocoL.bmp"), 1));
	fireSpritesheetManager->setNewSpritesheet("right", new Spritesheet(al_load_bitmap("./res/others/proiettileFuocoR.bmp"), 1));
	fireSpritesheetManager->setWidth(25);
	fireSpritesheetManager->setHeight(16);

	SpritesheetManager* powerupSpritesheetManager = new SpritesheetManager();
	powerupSpritesheetManager->setNewSpritesheet("powerup", new Spritesheet(al_load_bitmap("./res/others/pozione.bmp"), 1));
	powerupSpritesheetManager->setWidth(16);
	powerupSpritesheetManager->setHeight(16);

	levels[0]->registerEntity("T", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "T"));
	levels[0]->registerEntity("TL", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TL"));
	levels[0]->registerEntity("TR", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TR"));
	levels[0]->registerEntity("P", new ActorDescriptor(new Dimensions(25, 30),  6, 32, 10, 10, new Controller(key), new PlayerAction(), new PlayerCollisionHandler(), playerSpritesheetManager, "Player"));
	levels[0]->registerEntity("BL", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletLeft"));
	levels[0]->registerEntity("BR", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletRight"));
	levels[0]->registerEntity("BPL", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletPLeft"));
	levels[0]->registerEntity("BPR", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletPRight"));
	levels[0]->registerEntity("E1", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy1SpritesheetManager, "Enemy1"));
	levels[0]->registerEntity("E2", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy2SpritesheetManager, "Enemy2"));
	levels[0]->registerEntity("E3", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy3SpritesheetManager, "Enemy3"));
	levels[0]->registerEntity("FL", new ActorDescriptor(new Dimensions(25, 16),  6, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), fireSpritesheetManager, "FireLeft"));
	levels[0]->registerEntity("FR", new ActorDescriptor(new Dimensions(25, 16),  6, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), fireSpritesheetManager, "FireRight"));
	levels[0]->registerEntity("G", new ActorDescriptor(new Dimensions(16, 16),  6, 0, 0, 0, new Controller(key), new PowerupAction(), new PowerupCollisionHandler(), powerupSpritesheetManager, "Powerup"));

	levels[1]->registerEntity("T", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "T"));
	levels[1]->registerEntity("TL", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TL"));
	levels[1]->registerEntity("TR", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TR"));
	levels[1]->registerEntity("P", new ActorDescriptor(new Dimensions(25, 30),  6, 32, 10, 10, new Controller(key), new PlayerAction(), new PlayerCollisionHandler(), playerSpritesheetManager, "Player"));
	levels[1]->registerEntity("BL", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletLeft"));
	levels[1]->registerEntity("BR", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletRight"));
	levels[1]->registerEntity("BPL", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletPLeft"));
	levels[1]->registerEntity("BPR", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletPRight"));
	levels[1]->registerEntity("E1", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy1SpritesheetManager, "Enemy1"));
	levels[1]->registerEntity("E2", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy2SpritesheetManager, "Enemy2"));
	levels[1]->registerEntity("E3", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy3SpritesheetManager, "Enemy3"));
	levels[1]->registerEntity("FL", new ActorDescriptor(new Dimensions(25, 16),  6, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), fireSpritesheetManager, "FireLeft"));
	levels[1]->registerEntity("FR", new ActorDescriptor(new Dimensions(25, 16),  6, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), fireSpritesheetManager, "FireRight"));
	levels[1]->registerEntity("G", new ActorDescriptor(new Dimensions(16, 16),  6, 0, 0, 0, new Controller(key), new PowerupAction(), new PowerupCollisionHandler(), powerupSpritesheetManager, "Powerup"));

	levels[2]->registerEntity("T", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "T"));
	levels[2]->registerEntity("TL", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TL"));
	levels[2]->registerEntity("TR", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TR"));
	levels[2]->registerEntity("P", new ActorDescriptor(new Dimensions(25, 30),  6, 32, 10, 10, new Controller(key), new PlayerAction(), new PlayerCollisionHandler(), playerSpritesheetManager, "Player"));
	levels[2]->registerEntity("BL", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletLeft"));
	levels[2]->registerEntity("BR", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletRight"));
	levels[2]->registerEntity("BPL", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletPLeft"));
	levels[2]->registerEntity("BPR", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletPRight"));
	levels[2]->registerEntity("E1", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy1SpritesheetManager, "Enemy1"));
	levels[2]->registerEntity("E2", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy2SpritesheetManager, "Enemy2"));
	levels[2]->registerEntity("E3", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy3SpritesheetManager, "Enemy3"));
	levels[2]->registerEntity("FL", new ActorDescriptor(new Dimensions(25, 16),  6, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), fireSpritesheetManager, "FireLeft"));
	levels[2]->registerEntity("FR", new ActorDescriptor(new Dimensions(25, 16),  6, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), fireSpritesheetManager, "FireRight"));
	levels[2]->registerEntity("G", new ActorDescriptor(new Dimensions(16, 16),  6, 0, 0, 0, new Controller(key), new PowerupAction(), new PowerupCollisionHandler(), powerupSpritesheetManager, "Powerup"));

	levels[3]->registerEntity("T", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "T"));
	levels[3]->registerEntity("TL", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TL"));
	levels[3]->registerEntity("TR", new TileDescriptor(new Dimensions(16, 16), EntityDescriptor::createBitmapFromColor(new Dimensions(16, 16), 255, 255, 255), "TR"));
	levels[3]->registerEntity("P", new ActorDescriptor(new Dimensions(25, 30),  6, 32, 10, 10, new Controller(key), new PlayerAction(), new PlayerCollisionHandler(), playerSpritesheetManager, "Player"));
	levels[3]->registerEntity("BL", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletLeft"));
	levels[3]->registerEntity("BR", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletRight"));
	levels[3]->registerEntity("BPL", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletPLeft"));
	levels[3]->registerEntity("BPR", new ActorDescriptor(new Dimensions(6, 11),  11, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), bulletSpritesheetManager, "BulletPRight"));
	levels[3]->registerEntity("E1", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy1SpritesheetManager, "Enemy1"));
	levels[3]->registerEntity("E2", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy2SpritesheetManager, "Enemy2"));
	levels[3]->registerEntity("E3", new ActorDescriptor(new Dimensions(25, 30), 6, 32, 10, 10, new Controller(key), new EnemyAction(), new EnemyCollisionHandler(), enemy3SpritesheetManager, "Enemy3"));
	levels[3]->registerEntity("FL", new ActorDescriptor(new Dimensions(25, 16),  6, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), fireSpritesheetManager, "FireLeft"));
	levels[3]->registerEntity("FR", new ActorDescriptor(new Dimensions(25, 16),  6, 0, 0, 0, new Controller(key), new BulletAction(), new BulletCollisionHandler(), fireSpritesheetManager, "FireRight"));
	levels[3]->registerEntity("G", new ActorDescriptor(new Dimensions(16, 16),  6, 0, 0, 0, new Controller(key), new PowerupAction(), new PowerupCollisionHandler(), powerupSpritesheetManager, "Powerup"));

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

	al_flip_display();

	al_start_timer(timer);

	int highScore = 50, nLives = 2, nReplays = 9;

	int blinkCounter = 0;
	int infBlink = 0, supBlink = 1;

	unsigned transparency = 0;
	int tmp = 0;

	GameState gameState = MAIN_MENU;

	int levelCounter = 0;

	EnemyCounter* enemyCounter = EnemyCounter::getinstance();
	PlayerScore* playerScore = PlayerScore::getInstance();
	highScore = playerScore->readHighScore("./res/HighScore.txt");

	while (!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			if(gameState == MAIN_MENU)
			{
				if(key[KEY_SPACE])
				{
					gameState = IN_GAME_TRANSITION;
					blinkCounter = 0;
					infBlink = 0;
					supBlink = 1;

					transparency = 0;
					tmp = 0;
				}
			}
			else if(gameState == IN_GAME)
			{
				if(nReplays >= 0)
				{
					if(nLives < 0)
					{
						if(key[KEY_SPACE])
						{
							nLives = 2;
							nReplays--;
						}
					}
					if(enemyCounter->getEnemiesNumber() == 0)
					{
						levelCounter++;

						if(levelCounter >= nLevels)
						{
							gameState = END_MENU_TRANSITION;
							blinkCounter = 0;
							infBlink = 0;
							supBlink = 1;

							transparency = 0;
							tmp = 0;

							levels[levelCounter - 1]->clearLevel();
						}
						else
						{
							gameState = LEVEL_TRANSITION;
							blinkCounter = 0;
							infBlink = 0;
							supBlink = 1;

							transparency = 0;
							tmp = 0;

							levels[levelCounter - 1]->clearLevel();
						}
					}
				}
				else
				{
					gameState = GAME_OVER_MENU_TRANSITION;
					blinkCounter = 0;
					infBlink = 0;
					supBlink = 1;

					transparency = 0;
					tmp = 0;
				}
				if(levelCounter < nLevels)
				{
					levels[levelCounter]->processLevel(nLives);
					if(playerScore->getScore() >= highScore)
						highScore = playerScore->getScore();
				}
			}
			else if(gameState == GAME_OVER_MENU)
			{
				if(key[KEY_SPACE])
				{
					gameState = MAIN_MENU_TRANSITION;
					blinkCounter = 0;
					infBlink = 0;
					supBlink = 1;

					transparency = 0;
					tmp = 0;

					nLives = 2;
					nReplays = 9;

					levelCounter = 0;
				}
				else if(key[KEY_ESCAPE])
					doexit = true;
			}
			else if(gameState == END_MENU)
			{
				if(key[KEY_SPACE])
				{
					gameState = MAIN_MENU_TRANSITION;
					blinkCounter = 0;
					infBlink = 0;
					supBlink = 1;

					transparency = 0;
					tmp = 0;

					nLives = 2;
					nReplays = 9;

					levelCounter = 0;

					playerScore->addScore(playerScore->getScore() * (-1));
				}
				else if(key[KEY_ESCAPE])
					doexit = true;
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
				key[KEY_ESCAPE] = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_set_target_bitmap(al_get_backbuffer(display));
			ALLEGRO_TRANSFORM trans2;

			//TRANSIZIONI
			if (gameState == IN_GAME_TRANSITION)
			{
				if(transparency <= 255)
				{
					al_draw_filled_rectangle(0, 0, 256, 224, al_map_rgba(0, 0, 0, transparency));
				}
				else
				{
					al_draw_textf(font, al_map_rgb(255, 80, 0), 129, 112, ALLEGRO_ALIGN_CENTRE, "LEVEL %d", levelCounter + 1);
					al_draw_textf(font, al_map_rgb(255, 255, 255), 128, 112, ALLEGRO_ALIGN_CENTRE, "LEVEL %d", levelCounter + 1);
					if(tmp > 20)
						gameState = IN_GAME;
					tmp++;
				}
				transparency += 25;
			}
			else if (gameState == MAIN_MENU_TRANSITION)
			{
				if(transparency <= 255)
				{
					al_draw_filled_rectangle(0, 0, 256, 224, al_map_rgba(0, 0, 0, transparency));
				}
				else
					gameState = MAIN_MENU;

				transparency += 25;
			}
			else if (gameState == GAME_OVER_MENU_TRANSITION)
			{
				if(transparency <= 255)
				{
					al_draw_filled_rectangle(0, 0, 256, 224, al_map_rgba(0, 0, 0, transparency));
				}
				else
					gameState = GAME_OVER_MENU;

				transparency += 25;
			}
			else if (gameState == END_MENU_TRANSITION)
			{
				if(transparency <= 255)
				{
					al_draw_filled_rectangle(0, 0, 256, 224, al_map_rgba(0, 0, 0, transparency));
				}
				else
					gameState = END_MENU;

				transparency += 25;
			}
			if (gameState == LEVEL_TRANSITION)
			{
				al_draw_filled_rectangle(0, 0, 256, 24, al_map_rgb(0, 0, 0));

				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 18, 6);
				al_use_transform(&trans2);
				al_draw_text(font, al_map_rgb(255, 80, 0), 0, 0, 0, "1P");
				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 18, 14);
				al_use_transform(&trans2);
				al_draw_textf(font, al_map_rgb(255, 80, 0), 0, 0, 0, "%07d", playerScore->getScore());
				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 17, 6);
				al_use_transform(&trans2);
				al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "1P");
				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 17, 14);
				al_use_transform(&trans2);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "%07d", playerScore->getScore());
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


				if(transparency <= 255)
				{
					al_draw_filled_rectangle(0, 24, 256, 224, al_map_rgba(0, 0, 0, transparency));
				}
				else
				{
					al_draw_textf(font, al_map_rgb(255, 80, 0), 129, 112, ALLEGRO_ALIGN_CENTRE, "LEVEL %d", levelCounter + 1);
					al_draw_textf(font, al_map_rgb(255, 255, 255), 128, 112, ALLEGRO_ALIGN_CENTRE, "LEVEL %d", levelCounter + 1);
					if(tmp > 20)
					{
						gameState = IN_GAME;
						blinkCounter = 0;
						infBlink = 0;
						supBlink = 1;

						transparency = 0;
						tmp = 0;
					}
					tmp++;
				}
				transparency += 25;
			}
			//

			//STATI
			else if(gameState == MAIN_MENU)
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
			else if(gameState == IN_GAME)
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_hold_bitmap_drawing(1);
				levels[levelCounter]->drawLevel();
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
				al_draw_textf(font, al_map_rgb(255, 80, 0), 0, 0, 0, "%07d", playerScore->getScore());
				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 17, 6);
				al_use_transform(&trans2);
				al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "1P");
				al_identity_transform(&trans2);
				al_scale_transform(&trans2, 1, 0.77);
				al_translate_transform(&trans2, 17, 14);
				al_use_transform(&trans2);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "%07d", playerScore->getScore());

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
			else if (gameState == GAME_OVER_MENU)
			{
				al_draw_text(font, al_map_rgb(255, 80, 0), 129, 64, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
				al_draw_text(font, al_map_rgb(255, 80, 0), 129, 94, ALLEGRO_ALIGN_CENTRE, "[SPACE] MAIN MENU");
				al_draw_text(font, al_map_rgb(255, 80, 0), 129, 124, ALLEGRO_ALIGN_CENTRE, "[ESC] EXIT");
				al_draw_text(font, al_map_rgb(255, 255, 255), 128, 64, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
				al_draw_text(font, al_map_rgb(255, 255, 255), 128, 94, ALLEGRO_ALIGN_CENTRE, "[SPACE] MAIN MENU");
				al_draw_text(font, al_map_rgb(255, 255, 255), 128, 124, ALLEGRO_ALIGN_CENTRE, "[ESC] EXIT");
			}
			else if (gameState == END_MENU)
			{
				al_draw_text(font, al_map_rgb(255, 80, 0), 129, 64, ALLEGRO_ALIGN_CENTRE, "YOU WON!");
				al_draw_textf(font, al_map_rgb(255, 80, 0), 129, 94, ALLEGRO_ALIGN_CENTRE, "YOUR SCORE IS: %d", playerScore->getScore());
				al_draw_text(font, al_map_rgb(255, 80, 0), 129, 124, ALLEGRO_ALIGN_CENTRE, "[SPACE] MAIN MENU");
				al_draw_text(font, al_map_rgb(255, 80, 0), 129, 154, ALLEGRO_ALIGN_CENTRE, "[ESC] EXIT");
				al_draw_text(font, al_map_rgb(255, 255, 255), 128, 64, ALLEGRO_ALIGN_CENTRE, "YOU WON!");
				al_draw_textf(font, al_map_rgb(255, 255, 255), 128, 94, ALLEGRO_ALIGN_CENTRE, "YOUR SCORE IS: %d", playerScore->getScore());
				al_draw_text(font, al_map_rgb(255, 255, 255), 128, 124, ALLEGRO_ALIGN_CENTRE, "[SPACE] MAIN MENU");
				al_draw_text(font, al_map_rgb(255, 255, 255), 128, 154, ALLEGRO_ALIGN_CENTRE, "[ESC] EXIT");
				playerScore->writeHighScore("./res/HighScore.txt", highScore);
			}

			//
			al_flip_display();
		}
	}
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
