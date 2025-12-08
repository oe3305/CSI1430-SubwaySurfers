#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> 
#include <cmath> 
#include "SDL_Plotter.h"

using namespace std;

#ifndef window_manager_h
#define window_manager_h

enum action {
	MOVE_LEFT,
	MOVE_RIGHT,
	RESTART,
	NONE,
	START
};

class Window {
private:
	static const int FPS = 60;
	SDL_Plotter g;
	bool running = true;

public:
	static const int WIDTH = 600;
	static const int HEIGHT = 800;
	static const int GROUND_LEVEL = HEIGHT*95/100;
	static constexpr int LANES_X[3] = {WIDTH/6,WIDTH/2,WIDTH*5/6};
	static constexpr double DELTA_TIME = 1.0/FPS;

	// description: Constructor for the Window manager.
	// return: none
	// precondition: 'g' is an initialized SDL_Plotter object passed by reference.
	// postcondition: The internal plotter reference is set, and the game window state is initialized.
	Window(SDL_Plotter &g);

	// description: Manages the progression of a single game frame, typically involves updating game logic and events.
	// return: void
	// precondition: Called repeatedly in the main game loop.
	// postcondition: The internal state of the window manager advances one frame (e.g., processes closing events).
	void NextFrame();

	// description: Clears the screen and draws all managed graphical elements (e.g., rectangles, sprites) to the buffer, then updates the display.
	// return: void
	// precondition: 'g' is an initialized SDL_Plotter.
	// postcondition: The contents of the back buffer are swapped to the screen, displaying the current game state.
	void Render();

	// description: Checks if the game window is currently open and running.
	// return: bool (true if running, false if the user has requested to close the window)
	// precondition: none
	// postcondition: The current running state of the window is returned.
	bool IsRunning();

	// description: Polls the SDL_Plotter for user input (keyboard presses) and translates it into a defined 'action' enum.
	// return: action (MOVE_LEFT, MOVE_RIGHT, RESTART, START, or NONE)
	// precondition: 'g' is actively polling for input events.
	// postcondition: The most relevant user action for the current frame is identified and returned.
	action GetAction();

	// description: Static utility function to retrieve the center X coordinate for a specific lane index.
	// return: int (x coordinate of the lane center)
	// precondition: 'lane' is a valid index (0, 1, or 2).
	// postcondition: The predefined X position for the requested lane is returned.
	static int getLaneX(int lane) {return LANES_X[lane];}

	// description: Retrieves a reference to the internal SDL_Plotter object.
	// return: SDL_Plotter& (reference to the plotter)
	// precondition: The Window object is initialized.
	// postcondition: Provides access to the underlying graphics context for drawing operations.
	SDL_Plotter& getPlotter() {return g;}
};

#endif /* window_manager_h */
