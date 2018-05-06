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
	const char* filename;

public:
	MultiProjectile(const char* filename, float x, float y, float w, float h)
	{
		this->filename = filename;
		width = w;
		height = h;
	}

	void addProjectile(bool upinput, float x, float y, float speed)
	{
		//cout << "size of projectiles " << multiprojectile.size() << endl;
		if(multiprojectile.empty())
		{
			projectile = new Projectile(filename,x,y,width,height,speed,upinput,true);
			multiprojectile.push_back(projectile);
		}
		else if(multiprojectile.at(multiprojectile.size() - 1)->getcornerY() >= 1)
		{
			projectile = new Projectile(filename,x,y,width,height,speed,upinput,true);
			multiprojectile.push_back(projectile);
		}
	}

	int getsize()
	{
		return multiprojectile.size();
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
			if(multiprojectile.front()->getcornerY() - height >= 0.99 || multiprojectile.front()->getcornerY() <= -0.8)
			{
				multiprojectile.pop_front();
			}
		}
	}

};

#endif
