#include "App.h"

using namespace std;
//comment
static App* game;

void app_timer(int value)
{
	srand(time(NULL));
	int num = rand() % 3 + 1;
	if(game->screens->getshow())
	{
		if(game->screens->getlose())
		{
	        game->redraw();
	        glutTimerFunc(100, app_timer, value);
		}
		else
		{
			game->redraw();
			glutTimerFunc(16, app_timer, value);
		}
	}
	else if(game->game_start)
	{
		//check for player projectiles hitting enemy
		for(int i = 0; i < game->p1_projectiles->getsize(); i++)
		{
			if(game->army->containsprojectile(game->p1_projectiles->getprojectile(i)))
			{
				game->p1_projectiles->setnotmoving(i);
			}
		}
		//check for enemy projectiles hitting player
		for(int i = 0; i < game->enemy_projectiles->getsize(); i++)
		{
			if(game->playerone->shot(game->enemy_projectiles->getprojectile(i)->shotplayer(game->playerone)))
			{
				game->playercount--;
				if(game->playercount == 0)
				{
					game->screens->setlose();
				}
			}
		}

		if(game->twoplayer)
		{
			//check for player 2 projectiles hitting enemy
			for(int i = 0; i < game->p2_projectiles->getsize(); i++)
			{
				if(game->army->containsprojectile(game->p2_projectiles->getprojectile(i)))
				{
					game->p2_projectiles->setnotmoving(i);
				}
			}
			//check for enemy projectiles hitting player 2
			for(int i = 0; i < game->enemy_projectiles->getsize(); i++)
			{
				if(game->playertwo->shot(game->enemy_projectiles->getprojectile(i)->shotplayer(game->playertwo)))
				{
					game->playercount--;
					if(game->playercount == 0)
					{
						game->screens->setlose();
					}
				}
			}
			game->yeezys->pickedup(game->playertwo->pickedup(game->yeezys));
			game->supreme->pickedup(game->playertwo->pickedup(game->supreme));
		}

		if(num == 2)
		{
			game->enemy_projectiles->addRandomProjectile(false,0.05);
		}

		//check for num alive
		if(game->army->getalive() == 0)
		{
			game->screens->setwin();
		}
		for(int i = game->army->getnum() - 1; i >= 0; i--)
		{
			if(game->army->getenemy(i)->getcornerY() <= -0.65 && game->army->getenemy(i)->getalive())
			{
				game->screens->setlose();
			}
		}
		game->yeezys->pickedup(game->playerone->pickedup(game->yeezys));
		game->supreme->pickedup(game->playerone->pickedup(game->supreme));

		game->redraw();
		glutTimerFunc(16, app_timer, value);
	}
}

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h)
{
	// Initialize state variables
    
	game = this;
	mx = 0.0;
	my = 0.0;
    
	screens = new Screen("images/title_screen.png","images/pause_screen.png","images/game_over.png","images/win_screen.png","images/game_over_animate.png");
	background = new TexRect("images/space_square.png", -1, 1, 2, 2);
	army = new Army("images/thanos_face.png","images/thanos_face_fade.png", 3, 2, -0.9, 0.95, .14, .20, 4, 10);
	playerone = new Player("images/Kanye.png", " ", 3, 2, -0.7, -0.8, .15, .2);
	playertwo = new Player("images/donald_trump.png", " ", 3, 2, 0.5, -0.8, .15, .2);
	p1_projectiles = new MultiProjectile("images/money.png", 0.0, 0.0, 0.0477, 0.114);
	p2_projectiles = new MultiProjectile("images/money.png", 0.0, 0.0, 0.0477, 0.114);
	enemy_projectiles = new MultiProjectile("images/thanos_gauntlet.png", 0.0, 0.0, 0.484, 0.640);
	yeezys = new Yeezys("images/yeezys.png", 0.16, 0.09675);
	supreme = new Supreme("images/supreme_powerup.png", 0.165, 0.145);
	game_start = false;
	twoplayer = false;
	app_timer(1);

}

void App::specialKeyPress(int key)
{
	if(screens->getshow() == false)
	{
		if(key == 101)
		{
			if(p2_projectiles->getsize() <= playertwo->getcount())
			{
				p2_projectiles->addProjectile(true, playertwo->getcornerX() + 0.01, playertwo->getcornerY() - 0.01, /*speed*/ 0.02+playertwo->getboost());
			}
		}
		else
		{
			playertwo->keydown(key);
		}
	}
}

void App::specialKeyUp(int key)
{
	playertwo->keyup(key);
}

void App::draw()
{

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 1.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(screens->getshow())
	{
		screens->draw();
	}
	else
	{
		background->draw();
		p1_projectiles->draw();
		p2_projectiles->draw();
		enemy_projectiles->draw();
		playerone->draw();
		if(twoplayer)
		{
			playertwo->draw();
		}
		army->draw();
		yeezys->draw();
		supreme->draw();
	}
	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

void App::mouseDown(float x, float y)
{
	// Update app state
	mx = x;
	my = y;
}

void App::mouseDrag(float x, float y)
{
	// Update app state
	mx = x;
	my = y;
}

void App::idle()
{

}

void App::keyPress(unsigned char key)
{
	if (key == 'q')
	{
		if(screens->getshow())
		{
			// Exit the app when Esc key is pressed
			delete playerone;
			delete army;
			delete background;
			delete this;
			exit(0);
		}
	}
	else if(key == 'w')
	{
		if(p1_projectiles->getsize() <= playerone->getcount())
		{
			p1_projectiles->addProjectile(true, playerone->getcornerX() + 0.01, playerone->getcornerY() - 0.01, /*speed*/ 0.02+playerone->getboost());
		}
	}
	else if(key == 'p')
	{
		screens->togglepause();
		app_timer(1);
	}
	else if(key == 'r')
	{
		if(screens->getshow())
		{
			screens = new Screen("images/title_screen.png","images/pause_screen.png","images/game_over.png","images/win_screen.png","images/game_over_animate.png");
			army = new Army("images/thanos_face.png","images/thanos_face_fade.png", 3, 2, -0.9, 0.95, .14, .20, 4, 10);
			playerone = new Player("images/Kanye.png", " ", 3, 2, -0.7, -0.8, .15, .2);
			playertwo = new Player("images/donald_trump.png", " ", 3, 2, 0.5, -0.8, .15, .2);
			enemy_projectiles = new MultiProjectile("images/thanos_gauntlet.png", 0.0, 0.0, 0.484, 0.640);
			game_start = false;
			twoplayer = false;
			app_timer(1);
		}
	}
	else if(key == '1')
	{
		playercount = 1;
		twoplayer = false;
		game_start = true;
		screens->setshowfalse();
	}
	else if(key == '2')
	{
		playercount = 2;
		twoplayer = true;
		game_start = true;
		screens->setshowfalse();
	}
	else
	{
		playerone->keydownchar(key);
	}
}

void App::keyUp(unsigned char key)
{
	playerone->keyupchar(key);
}

