#ifndef MultiProjectile_h
#define MultiProjectile_h

#include "Projectile.h"
#include <deque>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class MultiProjectile
{
	deque<Projectile*> multiprojectile;
	Projectile* projectile;
	float width;
	float height;
	const char* filename;
	bool alternate;

public:
	MultiProjectile(const char* filename, float x, float y, float w, float h)
	{
		this->filename = filename;
		width = w;
		height = h;
		alternate = false;
	}

	void addRandomProjectile(bool upinput, float speed)
	{
		if(multiprojectile.size() == 0)
		{
			int num = rand() % 12;
			float posneg;
			if(alternate)
			{
				posneg = -1;
				alternate = false;
			}
			else
			{
				posneg = 1;
				if(num >= 9)
				{
					num -= 4;
				}
				alternate = true;
			}
			float x = (float)(num)/10;
			x *= posneg;
			float y = 1.5;
			projectile = new Projectile(filename,x,y,width,height,speed,upinput,true);
			multiprojectile.push_back(projectile);
		}
	}	

	void addProjectile(bool upinput, float x, float y, float speed)
	{
		projectile = new Projectile(filename,x,y,width,height,speed,upinput,true);
		multiprojectile.push_back(projectile);
	}

	float projectileX(int a)
	{
		return multiprojectile.at(a)->getcornerX();
	}

	float projectileY(int a)
	{
		return multiprojectile.at(a)->getcornerY();
	}

	Projectile* getprojectile(int a)
	{
		return multiprojectile.at(a);
	}

	float poslastprojectile()
	{
		if(multiprojectile.size() != 0)
		{
			return multiprojectile.back()->getcornerY();
		}
		return -10;
	}

	int getsize()
	{
		return multiprojectile.size();
	}

	void setnotmoving(int a)
	{
		multiprojectile.at(a)->setnotmoving();
	}

	void draw()
	{
		for(int i = 0; i < multiprojectile.size(); i++)
		{
			multiprojectile.at(i)->draw();
		}
		for(int i = 0; i < multiprojectile.size(); i++)
		{
			//cout << multiprojectile.front()->getcornerY() << endl;
			if(multiprojectile.front()->getcornerY() - height >= 0.99 || multiprojectile.front()->getcornerY() <= -0.99)
			{
				multiprojectile.pop_front();
			}
		}
	}

};

#endif
