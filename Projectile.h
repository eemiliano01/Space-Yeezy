#ifndef Projectile_h
#define Projectile_h

#include "TexRect.h"
#include "Player.h"

using namespace std;

class Projectile
{
	bool up;
	bool down;
	bool moving;
	float cornerX;
	float cornerY;
	float width;
	float height;
	float moverate;
	TexRect* projectile;

public:
	Projectile(const char* filename, float x, float y, float w, float h, float speed, bool up, bool moving)
	{
		projectile = new TexRect(filename, x, y, w, h);
		this->up = up;
		down = !up;
		cornerX = x;
		cornerY = y;
		width = w;
		height = h;
		this->moving = moving;
		moverate = speed;
	}

	void setDirection(bool upinput)
	{
		if(upinput)
		{
			up = true;
			down = false;
		}
		else
		{
			up = false;
			down = true;
		}
	}

	bool shotplayer(Player* player)
	{
		float x1 = player->getcornerX();
		float x2 = x1 + player->getwidth();
		float y1 = player->getcornerY() - 0.5;
		float y2 = y1 + player->getheight();
		if(projectile->contains(x1,y1) || projectile->contains(x1,y2) || projectile->contains(x2,y2) || projectile->contains(x2,y1))
		{
			return true;
		}
	}

	void setnotmoving()
	{
		moving = false;
		cornerY = 2;
	}

	void setSpeed(float speed)
	{
		moverate = speed;
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

	void draw()
	{
		if(moving)
		{
			if(up)
			{
				projectile->draw();
				cornerY += moverate;
				projectile->moveUp(moverate);
			}
			else if(down)
			{
				projectile->draw();
				cornerY -= moverate;
				projectile->moveDown(moverate);
			}
		}
	}

};

#endif
