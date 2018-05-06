#ifndef MultiProjectile_h
#define MultiProjectile_h

#include "Projectile.h"
#include <deque>
#include <iostream>

using namespace std;

class MultiProjectile
{
	deque<Projectile*> multiprojectile;
	Projectile* projectile;
	float width;
	float height;

public:
	MultiProjectiles(const char* filename, float x, float y, float w, float h);
	{
		projectile = new Projectile(filename,x,y,w,h,false,false);
		width = w;
		height = h;
	}

	void addProjectile(bool upinput, float speed);
	{
		projectile->setDirection(upinput);
		projectile->setSpeed(speed);
		multiprojectile.push_back(projectile);
	}

	void draw()
	{
		for(int i = 0; i < multiprojectile.size(); i++)
		{
			multiprojectile.at(i)->draw();
		}
		for(int i = 0; i < multiprojectile.size(); i++)
		{
			if(multiprojectile.front()->getcornerY() >= 0.99 || multiprojectile.front()->getcornerY() <= -0.99)
			{
				multiprojectile.pop_front();
			}
		}
	}

};

#endif
