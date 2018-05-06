#ifndef Projectile_h
#define Projectile_h

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
		up = up;
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
		if(input)
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

	void draw()
	{
		if(moving)
		{
			projectile->draw();
			if(up)
			{
				cornerY += moverate;
				projectile->moveUp(moverate);
			}
			else if(down)
			{
				cornerY -= moverate;
				projectile->moveDown(moverate);
			}
		}
	}

};

#endif
