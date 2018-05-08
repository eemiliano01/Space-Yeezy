#ifndef Screen_h
#define Screen_h

#include "TexRect.h"
#include "AnimatedRect.h"

class Screen
{
	bool win;
	bool lose;
	bool pause;
	bool gamestart;
	bool show;
	TexRect* titlemenu;
	TexRect* pausemenu;
	TexRect* gameovermenu;
	TexRect* winscreen;
	TexRect* gameover;
//	AnimatedRect* gameover;

public:
	Screen(const char* title, const char* pausem, const char* game, const char* winimage, const char* gameoverimage)
	{
		titlemenu = new TexRect(title,-1,1,2,2);
		pausemenu = new TexRect(pausem,-1,1,2,2);
		gameovermenu = new TexRect(game,-1,1,2,2);
		winscreen = new TexRect(winimage,-1,1,2,2);
		//gameover = new AnimatedRect(gameoverimage,7,1,-1.0,0.5,2,1.2);
		gameover = new TexRect(gameoverimage,-0.5,0.5,1,0.5);
		win = false;
		lose = false;
		pause = false;
		gamestart = true;
		show = true;
	}

	void draw()
	{
		if(win)
		{
			winscreen->draw();
		}
		else if(lose)
		{
			gameovermenu->draw();
			gameover->draw();
	//		gameover->advance();
		}
		else if(gamestart)
		{
			titlemenu->draw();
		}
		else if(pause)
		{
			pausemenu->draw();
		}
	}

	bool getwin()
	{
		return win;
	}

	bool getlose()
	{
		return lose;
	}

	bool getstart()
	{
		return gamestart;
	}

	bool getpause()
	{
		return pause;
	}

	bool getshow()
	{
		return show;
	}

	void setwin()
	{
		win = true;
		lose = false;
		pause = false;
		gamestart = false;
		show = true;
	}

	void setshowfalse()
	{
		show = false;
		gamestart = false;
		win = false;
		lose = false;
		pause = false;
	}

	void setshowtrue()
	{
		show = true;
	}	

	void setlose()
	{
		win = false;
		gamestart = false;
		pause = false;
		lose = true;
		show = true;
	}

	void setstart()
	{
		lose = false;
		win = false;
		pause = false;
		gamestart = true;
		show = true;
	}

	void togglepause()
	{
		win = false;
		lose = false;
		gamestart = false;
		if(pause == false)
		{
			pause = true;
			show = true;
		}
		else if(pause == true)
		{
			pause = false;
			show = false;
		}
	}

	void unpause()
	{
		pause = false;
		show = false;
	}

};

#endif
