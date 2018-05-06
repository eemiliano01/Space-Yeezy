#ifndef Player_h
#define Player_h

#include "TexRect.h"
#include "AnimatedRect.h"
#include "Projectile.h"
#include <deque>

class Player
{
	bool alive;
	bool fading;
	bool left;
	bool right;
	bool shoot;
	int rows;
	int cols;
	int count;
	float cornerX;
	float cornerY;
	float width;
	float height;
	float moverate;
	Projectile *projectile;
	deque<Projectile*> projectiles;
	TexRect *player;
	AnimatedRect *playerfade;

public:
	Player(const char* filename1, const char* filename2, int rows, int cols, float x, float y, float w, float h)
	{
		projectile = new Projectile("images/money.png", cornerX, cornerY, 0.0477, 0.114, true, false);
		player = new TexRect(filename1, x, y, w, h);
		playerfade = new AnimatedRect(filename2, rows, cols, x, y, w, h);
		this->rows = rows;
		this->cols = cols;
		count = 1;
		left = false;
		right = false;
		shoot = false;
		cornerX = x;
		cornerY = y;
		width = w;
		height = h;
		alive = true;
		fading = false;
		moverate = 0.05;
	}

	float getcornerX()
	{
		return cornerX;
	}

	float getcornerY()
	{
		return cornerY;
	}

	void keydown(int key)
	{
		if(key == 100)
		{
			left = true;
		}
		else if(key == 101)
		{
			projectile = new Projectile("images/money.png", cornerX+0.045, cornerY-0.04, 0.0477, 0.114, true, true);
			projectiles.push_back(projectile);
		}
		else if(key == 102)
		{
			right = true;
		}
	}

	void keyup(int key)
	{
		if(key == 100)
		{
			left = false;
		}
		else if(key == 102)
		{
			right = false;
		}
	}

	void draw()
	{
		if(alive)
		{
			for(int i = 0; i < projectiles.size(); i++)
			{
				projectiles.at(i)->draw();
			}
			for(int i = 0; i < projectiles.size(); i++)
			{
				if(projectiles.at(0)->getcornerY() >= 0.99)
				{
					projectiles.pop_front();
				}
			}
			if(left && cornerX >= -0.99)
			{
				cornerX -= moverate;
				player->moveLeft(moverate);
				playerfade->moveLeft(moverate);
			}
			else if(right && cornerX + width <= 0.99)
			{
				cornerX += moverate;
				player->moveRight(moverate);
				playerfade->moveRight(moverate);
			}
			player->draw();
		}
		else if(fading)
		{
			playerfade->draw();
			if(playerfade->done())
			{
				fading = false;
			}
		}
	}

	void contains(float x, float y)
	{
		if(player->contains(x,y))
		{
			alive = false;
			fading = true;
		}
	}

	~Player()
	{

	}
};

#endif
