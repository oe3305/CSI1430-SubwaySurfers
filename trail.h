#ifndef obstacles_h
#define obstacles_h

#include "window_manager.h"

class Trail{
private:
	Rectangle* r;
	int x,y;
	double timer = 2;


public:
	Trail(int x, int y)
	{
		this->x = x;
		this->y = y;
		r = new Rectangle(x,y, 20, 20, color(145, 212, 248),TRAIL);
	}

	void update()
	{
		timer -= Window::DELTA_TIME;

		if(timer<=0) removeRect();
	}

	void removeRect() {
		Window::removeRectangle(r);
	}
};

#endif /* obstacles_h */
