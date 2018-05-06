#include "App.h"

using namespace std;
//comment
static App* singleton;

void app_timer(int value)
{
	if(singleton->game_over)
	{
		//game is over
	}
	else
	{
		for(int i = 0; i < singleton->projectiles->getsize(); i++)
		{
			if(singleton->army->contains(singleton->projectiles->projectileX(i),singleton->projectiles->projectileY(i)))
			{
				singleton->projectiles->setnotmoving(i);
			}
		}
		singleton->redraw();
		glutTimerFunc(16, app_timer, value);
	}    
}

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h)
{
	// Initialize state variables
    
	singleton = this;
	mx = 0.0;
	my = 0.0;
    
	background = new TexRect("images/space_square.png", -1, 1, 2, 2);
	army = new Army("images/thanos_face.png","images/thanos_face_fade.png", 3, 2, -0.9, 0.9, .14, .20, 3, 8);
	playerone = new Player("images/Kanye.png", " ", 3, 2, 0.5, -0.8, .15, .20);
	projectiles = new MultiProjectile("images/money.png", 0.0, 0.0, 0.0477, 0.114);

	game_over = false;

	app_timer(1);

}

void App::specialKeyPress(int key)
{
	if(!game_over)
	{
		if(key == 101)
		{
			if(projectiles->poslastprojectile() >= 0 || projectiles->poslastprojectile() == -10)
			{
				projectiles->addProjectile(true,playerone->getcornerX()+0.01, playerone->getcornerY()-0.01, 0.1);
			}
		}
		playerone->keydown(key);
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
	projectiles->draw();
	playerone->draw();
	army->draw();

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

