#ifndef player_h
#define player_h

#include "window_manager.h"
#include "SDL_Plotter.h"

const double deaccel =70;
const double targetXVel = 1300;
class Player
{
private:
	double x,y;
	int lane;
	int width, height;
	double targetX;
	//Rectangle* r;
	double xVel;
	PNGSprite playerSprite;

public:
    Player(int width, int height)
    {
		lane = 1;
		x = Window::getLaneX(lane);
		targetX = Window::getLaneX(lane);
		y = Window::GROUND_LEVEL;

		this -> width = width;
		this -> height = height;

		//r = new Rectangle(static_cast<int>(x),y, height, width, color(0,255,0));

		if(!playerSprite.loadPNG("sprites/penguin.png",2)) {
			cout << "Error: could not load that jawn";
		}
    }

	void reset() {
		lane = 1;
		x = Window::getLaneX(lane);
		targetX = Window::getLaneX(lane);
		y = Window::GROUND_LEVEL;

		//r->setX(static_cast<int>(x));
	}

    void move(action act)
    {
		if(targetX==x) {
			if(act == MOVE_LEFT && lane > 0) lane--;
			else if(act == MOVE_RIGHT && lane < 2) lane++;
			targetX = Window::getLaneX(lane);
			xVel = targetXVel;
		}
		//cout << "A: Player @ " << x << " moving to " << targetX << " in lane " << lane << endl;
    }

    void update()
    {
		if(x != targetX) {
			if(x<targetX) x+=xVel*Window::DELTA_TIME;
			else x-=xVel*Window::DELTA_TIME;
			if(fabs(x-targetX) < xVel*Window::DELTA_TIME) x = targetX;
			//r->setX(static_cast<int>(x));
			if(xVel>deaccel) xVel-=deaccel;
		}
    }

	void corners(point* corners) {
		corners[0] = point(x-width/2,y-width/2);
		corners[1] = point(x-width/2,y+width/2);
		corners[2] = point(x+width/2,y-width/2);
		corners[3] = point(x+width/2,y+width/2);
	}

	void renderSprite(SDL_Plotter& g) {
		// Calculate centered position for the sprite
		int spriteX = static_cast<int>(x) - playerSprite.getWidth() / 2;
		int spriteY = static_cast<int>(y) - playerSprite.getHeight() / 2;
		
		// Render the PNG sprite
		playerSprite.render(g, spriteX, spriteY);
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

#endif /* player_h */
