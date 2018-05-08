#ifndef Enemy_h
#define Enemy_h

#include "TexRect.h"
#include "AnimatedRect.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

class Enemy
{
	bool alive;
	bool fading;
	bool right;
	bool left;
	bool down;
	bool shot;
	int rows;
	int cols;
	int shootnum;
	int totalchance;
	float cornerX;
	float cornerY;
	float width;
	float height;
	float moverate;
	TexRect *enemy;
	AnimatedRect *enemyfade;

public:
	Enemy(const char* filename1, const char* filename2, int rows, int cols, float x, float y, float w, float h, int snum, int tchance)
	{
		enemy = new TexRect(filename1, x, y, w, h);
		enemyfade = new AnimatedRect(filename2, rows, cols, x, y, w, h);
		this->rows = rows;
		this->cols = cols;
		cornerX = x;
		cornerY = y;
		width = w;
		height = h;
		alive = true;
		fading = false;
		shot = false;
		shootnum = snum;
		totalchance = tchance;
		moverate = 0.005; //0.001
	}

	void setshotfalse()
	{
		shot = false;
	}

	bool getalive()
	{
		return alive;
	}

	float getcornerX()
	{
		return cornerX;
	}

	float getcornerY()
	{
		return cornerY;
	}

	float setcornerX(float x)
	{
		cornerX = x;
	}

	float setcornerY(float y)
	{
		cornerY = y;
	}

	float getWidth()
	{
		return width;
	}

	float getHeight()
	{
		return height;
	}

	void setdeath()
	{
		alive = false;
		fading = true;
	}

	void setmovement(bool l, bool r, bool d)
	{
		left = l;
		right = r;
		down = d;
	}
	
	void draw()
	{
		if(alive)
		{
			enemy->draw();
		}
		else if(fading)
		{
			enemyfade->draw();
			if(enemyfade->done())
			{
				fading = false;
			}
		}
		if(left)
		{
			cornerX -= moverate;
			enemy->moveLeft(moverate);
			enemyfade->moveLeft(moverate);
		}
		else if(right)
		{
			cornerX += moverate;
			enemy->moveRight(moverate);
			enemyfade->moveRight(moverate);
		}
		else if(down)
		{
			cornerY -= moverate;
			enemy->moveDown(moverate);
			enemyfade->moveDown(moverate);
		}
	}

	bool contains(float x, float y)
	{
		if(enemy->contains(x,y) && alive == true)
		{
			alive = false;
			fading = true;
			return true;
		}
	}

	bool shoot()
	{
		if(shot == false && alive == true)
		{
			srand(time(NULL));
			int num;
			num = rand() % totalchance + 1;
			if(num == shootnum)
			{
				shot = true;
			}
			return num == 5;
		}
		else
		{
			return false;
		}
	}
};

#endif
