#ifndef Player_h
#define Player_h

#include "TexRect.h"
#include "AnimatedRect.h"
#include "Yeezys.h"
#include "Supreme.h"
#include <deque>

class Player
{
	bool alive;
	bool fading;
	bool left;
	bool right;
	int rows;
	int cols;
	int projectile_count;
	float cornerX;
	float cornerY;
	float width;
	float height;
	float moverate;
	float boost;
	TexRect *player;
	AnimatedRect *playerfade;

public:
	Player(const char* filename1, const char* filename2, int rows, int cols, float x, float y, float w, float h)
	{
		player = new TexRect(filename1, x, y, w, h);
		playerfade = new AnimatedRect(filename2, rows, cols, x, y, w, h);
		this->rows = rows;
		this->cols = cols;
		projectile_count = 0;
		left = false;
		right = false;
		cornerX = x;
		cornerY = y;
		width = w;
		height = h;
		alive = true;
		fading = false;
		moverate = 0.02;
		boost = 0.0;
	}

	int getcount()
	{
		return projectile_count;
	}

	float getboost()
	{
		return boost;
	}

	float getcornerX()
	{
		return cornerX;
	}

	float getcornerY()
	{
		return cornerY;
	}

	float getwidth()
	{
		return width;
	}

	float getheight()
	{
		return height;
	}

	bool pickedup(Yeezys* yeezy)
	{
		float x1, x2, y1, y2;
		x1 = yeezy->getcornerX();
		x2 = x1+yeezy->getwidth();
		y1 = yeezy->getcornerY();
		y2 = y1+yeezy->getheight();
		if(player->contains(x1,y1) || player->contains(x1,y2) || player->contains(x2,y2) || player->contains(x1,y2))
		{
			moverate += 0.02;
			return true;
		}
		return false;
	}

	bool pickedup(Supreme* supreme)
	{
		float x1, x2, y1, y2;
		x1 = supreme->getcornerX();
		x2 = x1+supreme->getwidth();
		y1 = supreme->getcornerY();
		y2 = y1+supreme->getheight();
		if(player->contains(x1,y1) || player->contains(x1,y2) || player->contains(x2,y2) || player->contains(x1,y2))
		{
			boost += 0.02;
			projectile_count++;
			return true;
		}
		return false;
	}

	void keydown(int key)
	{
		if(key == 100)
		{
			left = true;
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

	void keydownchar(unsigned char key)
	{
		if(key == 'a')
		{
			left = true;
		}
		else if(key == 'd')
		{
			right = true;
		}
	}

	void keyupchar(unsigned char key)
	{
		if(key == 'a')
		{
			left = false;
		}
		else if(key == 'd')
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

	bool shot(bool input)
	{
		if(input)
		{
			cornerX = 2;
			player->moveLeft(2);
			alive = false;
			fading = true;
			return true;
		}
		else
		{
			return false;
		}
	}
	
	~Player()
	{

	}
};

#endif
