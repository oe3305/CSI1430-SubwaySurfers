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
    Player(int width, int height); 

	void reset();

    void move(action act);

    void update();

	void corners(point* corners);

	void renderSprite(SDL_Plotter& g);
	
	// Getter methods for position (useful for rendering)
	int getX() const;
	int getY() const;
	
	// Method to render both rectangle and sprite
	void draw(SDL_Plotter& g);
};

#endif /* player_h */
