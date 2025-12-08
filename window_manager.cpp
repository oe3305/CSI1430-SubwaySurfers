#include "window_manager.h"
using namespace std;

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
		if (key == ' ') return START;
	}
	return NONE;
}
