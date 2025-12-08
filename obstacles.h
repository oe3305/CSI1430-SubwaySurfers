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
	// description: Constructor for the Obstacle class. Initializes a new obstacle in a specific lane with a given type and dimensions.
	// return: none
	// precondition: 'lane' is a valid game lane index. 't' is a valid enum type (ICEBURG, BIG_ICEBURG, SNOWBALL). Dimensions are positive.
	// postcondition: An Obstacle object is created with correct starting position, velocity, and a sprite loaded corresponding to its type.
	Obstacle(int lane, int t, double xVel = 0,int height = 48,int width = 48);

	// description: Provides a reference to the static vertical velocity variable ('yVel').
	// return: A reference to a double (static yVel).
	// precondition: The Obstacle class has been defined.
	// postcondition: Allows external functions to modify the shared global vertical speed of all obstacles.
	static double& getYVel() {
		return yVel;
	}

	// description: Sets the static vertical velocity variable ('yVel') to a new speed.
	// return: void
	// precondition: The Obstacle class has been defined. 'speed' is the desired new vertical speed.
	// postcondition: All obstacles will now move vertically at the specified speed during their next update cycle.
	static void setYVel(double speed) {
		yVel = speed;
	}

	// description: Updates the obstacle's position based on its 'xVel' and the static 'yVel'. Also handles animation frame timing.
	// return: void
	// precondition: This function is called frequently within the main game loop.
	// postcondition: The 'x' and 'y' coordinates of the obstacle are advanced, and the 'frame' count might increment for animation.
	void update();

	// description: Checks if the obstacle has moved completely off the bottom of the game screen.
	// return: bool (true if done/off-screen, false otherwise)
	// precondition: Game window dimensions are accessible/known.
	// postcondition: A boolean status is returned indicating if this specific obstacle should be despawned.
	bool done();

	// description: Checks if a given point 'p' falls within the bounding box of this obstacle. Used for collision detection.
	// return: bool (true if the point is within bounds, false otherwise)
	// precondition: 'p' is a valid point structure (with x, y coordinates).
	// postcondition: A boolean status is returned indicating a collision or proximity.
	bool withinBounds(point p);
	
	// description: Renders the obstacle's PNG sprite onto the provided graphics plotter object at its current 'x' and 'y' position.
	// return: void
	// precondition: 'g' is an initialized and open SDL_Plotter object. The obsSprite has been loaded correctly.
	// postcondition: The obstacle sprite is drawn on the screen buffer.
	void renderSprite(SDL_Plotter& g);
	
	// description: Retrieves the current integer x-coordinate of the obstacle's top-left corner.
	// return: int (x position)
	// precondition: The Obstacle object exists.
	// postcondition: The exact current x-coordinate is returned.
	int getX() const;

	// description: Retrieves the current integer y-coordinate of the obstacle's top-left corner.
	// return: int (y position)
	// precondition: The Obstacle object exists.
	// postcondition: The exact current y-coordinate is returned.
	int getY() const;
	
	// description: A composite draw function that renders the PNG sprite for the obstacle.
	// return: void
	// precondition: 'g' is an initialized and open SDL_Plotter object.
	// postcondition: The obstacle's visual representation is drawn on the screen buffer.
	void draw(SDL_Plotter& g);
};

#endif /* obstacles_h */
