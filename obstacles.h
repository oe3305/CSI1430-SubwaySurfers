#ifndef obstacles_h
#define obstacles_h

#include "window_manager.h"
#include "SDL_Plotter.h"

enum type {
	ICEBURG,
	BIG_ICEBURG,
	SNOWBALL
};
class Obstacle{
private:
	//Rectangle* r;
	double xVel;
	double x,y;
	int height;
	int width;
	PNGSprite obsSprite;
	string imageName;
	int type;
	int scale;
	int frame = 0;
	double frameTimer = 0;
	static double yVel;
	const string iceburg[3] = {"iceburg1","iceburg2","snowman"};
	const string snowball[4] = {"snowball0","snowball1","snowball2","snowball3"};

public:
	Obstacle(int lane, int t, double xVel = 0,int height = 48,int width = 48);

	static double& getYVel() {
		return yVel;
	}

	static void setYVel(double speed) {
		yVel = speed;
	}

	void update();

	bool done();

	bool withinBounds(point p);
	
	// Method to render the PNG sprite on top of the obstacle
	void renderSprite(SDL_Plotter& g);
	
	// Getter methods for position (useful for rendering)
	int getX() const;
	int getY() const;
	
	// Method to render both rectangle and sprite
	void draw(SDL_Plotter& g);
};

#endif /* obstacles_h */
