#ifndef obstacles_h
#define obstacles_h

#include "window_manager.h"
#include "SDL_Plotter.h"

class Obstacle{
private:
	Rectangle* r;
	double xVel;
	double yVel;
	double x,y;
	int height;
	int width;
	PNGSprite obsSprite;

public:
	Obstacle(int lane, double yVel = 100, double xVel = 0,int height = 40,int width = 60)
	{
		this->yVel = yVel;
		this->xVel = xVel;
		this->height = height;
		this->width = width;
		
		x = Window::getLaneX(lane);
		y = -height/2;
		r = new Rectangle(static_cast<int>(x),static_cast<int>(y), height, width, color(255, 0, 0));
		
		// Load the obstacle PNG sprite
		if (!obsSprite.loadPNG("iBePoppinBottles.png")) {
			cout << "Warning: Could not load obstacle.png" << endl;
		}
	}

	void update()
	{
		y += yVel*Window::DELTA_TIME;
		r->setY(static_cast<int>(y));
		if(xVel!=0) {
			x += xVel*Window::DELTA_TIME;
			if(x-width/2<=0) xVel*=-1;
			if(x+width/2>=Window::WIDTH) xVel*=-1;
			r->setX(static_cast<int>(x));
		}

		if(done()) removeRect();
	}

	bool done() {
		return r->getY()-r->getHeight()/2 > Window::HEIGHT;
	}

	bool withinBounds(point p) {
		if(p.y < y-width/2) return false;
		if(p.y > y+width/2) return false;
		if(p.x < x-width/2) return false;
		if(p.x > x+width/2) return false;
		return true;
	}

	void removeRect() {
		Window::removeRectangle(r);
	}
	
	// Method to render the PNG sprite on top of the obstacle
	void renderSprite(SDL_Plotter& g) {
		// Calculate centered position for the sprite
		int spriteX = static_cast<int>(x) - obsSprite.getWidth() / 2;
		int spriteY = static_cast<int>(y) - obsSprite.getHeight() / 2;
		
		// Render the PNG sprite
		obsSprite.render(g, spriteX, spriteY);
	}
	
	// Getter methods for position (useful for rendering)
	int getX() const { return static_cast<int>(x); }
	int getY() const { return static_cast<int>(y); }
	
	// Method to render both rectangle and sprite
	void draw(SDL_Plotter& g) {
		
		// Draw the PNG sprite on top
		renderSprite(g);
	}
};

#endif /* obstacles_h */
