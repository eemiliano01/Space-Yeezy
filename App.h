#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "TexRect.h"
#include "AnimatedRect.h"
#include "Army.h"
#include "Player.h"
#include "MultiProjectile.h"
#include "Yeezys.h"
#include "Supreme.h"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class App: public GlutApp
{
	// Maintain app state here
	float mx;
	float my;

public:
	// Constructor, to initialize state
	App(const char* label, int x, int y, int w, int h);

	// These are the events we want to handle
	void draw();
	void keyPress(unsigned char key);
	void keyUp(unsigned char key);
	void mouseDown(float x, float y);
	void mouseDrag(float x, float y);

	void specialKeyPress(int key);

	void specialKeyUp(int key);

	void idle();

	Army* army;
	Player* playerone;
	Player* playertwo;
	MultiProjectile* p1_projectiles;
	MultiProjectile* p2_projectiles;
	MultiProjectile* enemy_projectiles;
	Yeezys* yeezys;
	Supreme* supreme;
	TexRect* background;

	AnimatedRect* gameOver;

	bool game_over;
};

#endif
