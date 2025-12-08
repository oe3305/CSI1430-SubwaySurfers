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
	// description: Constructor for the Player class. Initializes player dimensions and state.
	// return: none
	// precondition: width and height are positive integers representing the desired player size.
	// postcondition: A Player object is initialized with starting position, lane, velocity, and a sprite loaded using the provided dimensions.
    Player(int width, int height); 

	// description: Resets the player's position, lane, and velocity to their initial default values.
	// return: void
	// precondition: The Player object exists.
	// postcondition: The player is centered in the starting lane with zero horizontal velocity.
	void reset();

	// description: Adjusts the player's target horizontal position based on the specified action (e.g., move left/right).
	// return: void
	// precondition: 'act' is a valid action from the action enum (e.g., LEFT, RIGHT, NONE).
	// postcondition: The 'targetX' value is updated to reflect the desired new lane position, clamped within screen bounds.
    void move(action act);

	// description: Updates the player's current horizontal position ('x') based on current velocity ('xVel') and applies deceleration to move towards the 'targetX'.
	// return: void
	// precondition: The game loop calls this function periodically to advance game state.
	// postcondition: 'x' and 'xVel' are updated based on physics calculations. 'xVel' moves closer to zero as 'x' approaches 'targetX'.
    void update();

	// description: Calculates and fills an array with the current coordinates of the player's four corners.
	// return: void
	// precondition: 'corners' is a pointer to an array of at least 4 point structures. The player's current 'x' and 'y' positions are valid.
	// postcondition: The 'corners' array contains the top-left, top-right, bottom-right, and bottom-left points of the player sprite's bounding box.
	void corners(point* corners);

	// description: Renders the player's PNG sprite onto the provided graphics plotter object at its current 'x' and 'y' position.
	// return: void
	// precondition: 'g' is an initialized and open SDL_Plotter object. The playerSprite has been loaded correctly.
	// postcondition: The player sprite is drawn on the screen buffer.
	void renderSprite(SDL_Plotter& g);
	
	// description: Retrieves the current integer x-coordinate of the player's top-left corner.
	// return: int (x position)
	// precondition: The Player object exists.
	// postcondition: The exact current x-coordinate is returned.
	int getX() const;

	// description: Retrieves the current integer y-coordinate of the player's top-left corner.
	// return: int (y position)
	// precondition: The Player object exists.
	// postcondition: The exact current y-coordinate is returned.
	int getY() const;
	
	// description: A composite draw function that can render both a basic debug rectangle and the main PNG sprite (though the rectangle part is commented out in this definition).
	// return: void
	// precondition: 'g' is an initialized and open SDL_Plotter object.
	// postcondition: The player's visual representation (sprite) is drawn on the screen buffer.
	void draw(SDL_Plotter& g);
};

#endif /* player_h */
