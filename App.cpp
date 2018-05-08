#include "App.h"

using namespace std;
//comment
static App* game;

void app_timer(int value)
{
	srand(time(NULL));
	int num = rand() % 5 + 1;
	if(game->game_over)
	{
		cout << "game over" << endl;
	}
	else
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
				game->game_over = true;
			}
		}
		if(num == 3)
		{
			game->enemy_projectiles->addRandomProjectile(false,0.04);
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
    
	background = new TexRect("images/space_square.png", -1, 1, 2, 2);
	army = new Army("images/thanos_face.png","images/thanos_face_fade.png", 3, 2, -0.9, 0.95, .14, .20, 4, 8);
	playerone = new Player("images/Kanye.png", " ", 3, 2, 0.5, -0.8, .15, .20);
	p1_projectiles = new MultiProjectile("images/money.png", 0.0, 0.0, 0.0477, 0.114);
	p2_projectiles = new MultiProjectile("images/money.png", 0.0, 0.0, 0.0477, 0.114);
	enemy_projectiles = new MultiProjectile("images/thanos_gauntlet.png", 0.0, 0.0, 0.484, 0.640);
	yeezys = new Yeezys("images/yeezys.png", 0.16, 0.09675);
	supreme = new Supreme("images/supreme_powerup.png", 0.165, 0.145);

	game_over = false;

	app_timer(1);

}

void App::specialKeyPress(int key)
{
	if(!game_over)
	{
		if(key == 101)
		{
			if(p1_projectiles->getsize() <= playerone->getcount())
			{
				p1_projectiles->addProjectile(true, playerone->getcornerX() + 0.01, playerone->getcornerY() - 0.01, /*speed*/ 0.02+playerone->getboost());
			}
		}
		else
		{
			playerone->keydown(key);
		}
	}
}

void App::specialKeyUp(int key)
{
	playerone->keyup(key);
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

	background->draw();
	p1_projectiles->draw();
	p2_projectiles->draw();
	enemy_projectiles->draw();
	playerone->draw();
	army->draw();
	yeezys->draw();
	supreme->draw();

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
	if (key == 27)
	{
		// Exit the app when Esc key is pressed
		delete playerone;
		delete army;
		delete background;
		delete this;
		exit(0);
	}
	if(key == 'a')
	{
		//player 2 moves left
	}
	if(key == 'd')
	{
		//player 2 moves right
	}
	if(key == 'w')
	{
		//player 2 shoots
	}
	if (key == ' ')
	{
		game_over = false;
	}
}

void App::keyUp(unsigned char key)
{
	if(key == 'a')
	{
		//player 2 stops
	}
	if(key == 'd')
	{
		//player 2 stops
	}
	if(key == 'w')
	{
		//player 2 stops shooting
	}
}

