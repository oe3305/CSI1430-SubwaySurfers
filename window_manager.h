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

class Rectangle {
private:
    int x, y, height, width;
    color col;
	const int SHADOW_THICKNESS = 2;
	const int SHADOW_OFFSET = 5;

public:
    Rectangle();
    Rectangle(int x, int y, int height, int width, color col);

    void draw(SDL_Plotter &g);

	void setY(int y) {this->y = y;}
	void setX(int x) {this->x = x;}

	int getY()const {return y;}
	int getX()const {return x;}
	int getHeight()const {return height;}
};

class Window {
private:
	static const int FPS = 60;
	SDL_Plotter g;
	bool running = true;
	static vector<Rectangle*> rectangles;

public:
	static const int WIDTH = 600;
	static const int HEIGHT = 800;
	static const int GROUND_LEVEL = HEIGHT*95/100;
	static constexpr int LANES_X[3] = {WIDTH/6,WIDTH/2,WIDTH*5/6};
	static constexpr double DELTA_TIME = 1.0/FPS;

	Window(SDL_Plotter &g);

	void NextFrame();
	void Render();
	bool IsRunning();
	action GetAction();
	static int getLaneX(int lane) {return LANES_X[lane];}
	static void addRectangle(Rectangle* r){rectangles.push_back(r);}
	static void removeRectangle(Rectangle*);
	static void reset();
	SDL_Plotter& getPlotter() {return g;}
};

#endif /* window_manager_h */
