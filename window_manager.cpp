#include "window_manager.h"
using namespace std;

Rectangle::Rectangle() : x(0), y(0), height(0), width(0), col(color(0, 0, 0)) {}
Rectangle::Rectangle(int x, int y, int height, int width, color col) {
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	this->col = col;
	Window::addRectangle(this);
	//cout << "New Rectangle" << endl;
}

void Rectangle::draw(SDL_Plotter &g)
{
	//cout << "Drawing " << width << "x" << height << " Rectangle @ (" << x << "," << y << ")" << endl;
	for (int i = x-width/2; i <= x+width/2; ++i)
	{
		for (int j = y-height/2; j <= y+height/2; ++j)
		{
			g.plotPixel(i, j, col);
		}
	}
	 for (int i = x-width/2 + SHADOW_OFFSET; i <= x+width/2 + SHADOW_THICKNESS; ++i)
	{
		for (int j = y+height/2+1; j <= y+height/2+1+SHADOW_THICKNESS; ++j)
		{
			g.plotPixel(i, j, color(0,0,0));
		}
	}
	 for (int i = x+width/2 + 1; i <= x+width/2 + 1+ SHADOW_THICKNESS; ++i)
	{
		for (int j = y-height/2+SHADOW_OFFSET; j <= y+height/2+SHADOW_THICKNESS; ++j)
		{
			g.plotPixel(i, j, color(0,0,0));
		}
	}
}

vector<Rectangle*> Window::rectangles;

Window::Window(SDL_Plotter &g) {
	this->g.destroyWindow();
	this->g = g;
	this->g.showWindow();
	//cout << "Window Sucessfully Opened" << endl;
}

void Window::NextFrame() {
	g.update();
	g.Sleep(static_cast<int>(1000*DELTA_TIME));
}

void Window::Render() {
	g.clear();

	//cout << rectangles.size() << endl;
	
	for(auto* i : rectangles) {
		(*i).draw(g);
	}

	//cout << "Rendered" << endl;

}

bool Window::IsRunning(){
	return running && !g.getQuit();
}

action Window::GetAction() {
	if (g.kbhit())
	{
		char key = toupper(g.getKey());
		if (key == 'Q') running=false;
		if (key == LEFT_ARROW) return MOVE_LEFT;
		if (key == RIGHT_ARROW) return MOVE_RIGHT;
		if (key == 'R') return RESTART;
	}
	return NONE;
}
void Window::removeRectangle(Rectangle* r_to_remove) {
	auto it = std::remove(rectangles.begin(), rectangles.end(), r_to_remove);
	if (it != rectangles.end()) {
		delete r_to_remove; 
		rectangles.erase(it, rectangles.end());
	}
}

void Window::reset() {
	for(Rectangle* r : rectangles) {
		removeRectangle(r);
	}
}
