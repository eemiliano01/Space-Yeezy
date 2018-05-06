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
	bool shooting;
	int rows;
	int cols;
	int count;
	float cornerX;
	float cornerY;
	float width;
	float height;
	float moverate;
	TexRect *player;
	AnimatedRect *playerfade;

public:
	Player(const char* filename1, const char* filename2, int rows, int cols, float x, float y, float w, float h)
	{
		player = new TexRect(filename1, x, y, w, h);
		playerfade = new AnimatedRect(filename2, rows, cols, x, y, w, h);
		this->rows = rows;
		this->cols = cols;
		count = 1;
		left = false;
		right = false;
		shooting = false;
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
			if(shooting == false)
			{
				shooting = true;
			}
			else if(shooting == true)
			{
				shooting = false;
			}
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

	bool getshooting()
	{
		return shooting;
	}
	
	~Player()
	{

	}
};

#endif
