#ifndef Supreme_h
#define Supreme_h

#include "TexRect.h"
#include "Player.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Supreme
{
	bool drawn;
	bool falling;
	float cornerX;
	float cornerY;
	float width;
	float height;
	float fallrate;
	TexRect* supreme;

public:
	Supreme(const char* filename, float w, float h)
	{
		supreme = new TexRect(filename, 0.0, 1.5, w, h);
		drawn = false;
		falling = true;
		cornerX = 0.0;
		cornerY = 1.5;
		width = w;
		height = h;
		fallrate = 0.03;
	}

	void pickedup(bool picked)
	{
		if(picked)
		{
			falling = true;
			drawn = false;
			cornerY = 1.5;
			supreme->setY(1.5);
		}
	}

	float getwidth()
	{
		return width;
	}

	void setwidth(float w)
	{
		width = w;
	}

	float getheight()
	{
		return height;
	}

	void setheight(float h)
	{
		height = h;
	}

	float getcornerX()
	{
		return cornerX;
	}

	float getcornerY()
	{
		return cornerY;
	}

	void setcornerX(float x)
	{
		cornerX = x;
	}

	void setcornerY(float y)
	{
		cornerY = y;
	}

	void draw()
	{
		if(drawn == false)
		{
			srand(time(NULL));
			int num;
			num = rand() % 15 + 1;
			if(num == 7)
			{
				//cout << "spawning supreme" << endl;
				drawn = true;
				int pos;
				pos = rand() % 7 + 1;
				num = rand() % 2 + 1;
				float posneg;
				if(num == 2)
				{
					posneg = 1;
				}
				else
				{
					posneg = -1;
				}
				float posX = (float)(pos)/10;
				posX *= posneg;
				cornerX = posX;
				supreme->setX(posX);
				supreme->draw();
				if(falling)
				{
					cornerY -= fallrate;
					supreme->moveDown(fallrate);
					if(cornerY <= -0.8)
					{
						falling = false;
					}
				}
			}
		}
		else if(drawn == true)
		{
			supreme->draw();
			if(falling)
			{
				cornerY -= fallrate;
				supreme->moveDown(fallrate);
				if(cornerY <= -0.8)
				{
					falling = false;
				}
			}
		}
	}
};

#endif
