#ifndef Army_h
#define Army_h

#include "Enemy.h"
#include <vector>
#include <iostream>

using namespace std;

class Army
{
	vector<Enemy*> enemies;
	Enemy* troop;
	bool right;
	bool left;
	bool down;
	float top_left_X;
	float top_right_X;
	float top_Y;
	int rows;
	int cols;
	int num_enemies;
	int num_alive;

public:
	Army(const char* filename1, const char* filename2, int anirows, int anicols, float x, float y, float w, float h, int rows, int cols)
	{
		troop = new Enemy(filename1,filename2,anirows,anicols,x,y,w,h);
		top_left_X = x;
		top_right_X = top_left_X + cols * w;
		top_Y = y;
		this->rows = rows;
		this->cols = cols;
		num_enemies = rows * cols;
		right = true;
		down = false;
		int j = 1;
		Enemy* temp;
		float setX = x;
		float setY = y;
		for(int i = 1; i <= num_enemies; i++)
		{
			temp = new Enemy(filename1,filename2,anirows,anicols,setX,setY,w,h);
			if(i % cols == 0)
			{
				setX = x;
				setY -= h;
			}
			else
			{
				setX += w + 0.01;
			}
			enemies.push_back(temp);
		}
	}

	~Army()
	{
		for(int i = 0; i < num_enemies; i++)
		{
			delete[] enemies[i];
		}
	}

	void draw()
	{
		for(int i = 0; i < num_enemies; i++)
		{
			enemies.at(i)->draw();
		}
		if(top_Y - (troop->getHeight()/2) >= enemies.at(0)->getcornerY())
		{
			top_Y -= (troop->getHeight()/2);
			down = false;
			if(enemies.at(0)->getcornerX() <= -0.99)
			{
				right = true;
				left = false;
			}
			else
			{
				right = false;
				left = true;
			}
		}
		else if(enemies.at(cols-1)->getcornerX() + troop->getWidth() >= 0.99)
		{
			right = false;
			left = false;
			down = true;
		}
		else if(enemies.at(0)->getcornerX() <= -0.99)
		{
			right = false;
			left = false;
			down = true;
		}
		for(int i = 0; i < num_enemies; i++)
		{
			enemies.at(i)->setmovement(left,right,down);
			enemies.at(i)->move();
		}
		top_left_X = enemies.at(0)->getcornerX();
	}

};

#endif
