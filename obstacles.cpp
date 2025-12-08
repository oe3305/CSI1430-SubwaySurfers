#include "obstacles.h"

double Obstacle::yVel = 0;

Obstacle::Obstacle(int lane, int t, double xVel,int height,int width) {
	this->xVel = xVel;
	this->height = height;
	this->width = width;
	this->type = t;
	
	x = Window::getLaneX(lane);
	y = -height/2;
	
	// Load the obstacle PNG sprite
	if(t == ICEBURG) {
		imageName = iceburg[rand()%3];
		scale = 3;
	}
	else if(t == BIG_ICEBURG) {
		imageName = "bigiceburg1";
		scale = 3;
	}
	else if(t == SNOWBALL) {
		imageName = snowball[0];
		scale = 2;
	}

	if (!obsSprite.loadPNG("sprites/"+imageName+".png",scale)) {
		cout << "Warning: Could not load sprites/"<<imageName<<".png" << endl;
	}
}


void Obstacle::update()
{
	y += yVel*Window::DELTA_TIME;
	if(xVel!=0) {
		x += xVel*Window::DELTA_TIME;
		if(x-width/2<=0) xVel*=-1;
		if(x+width/2>=Window::WIDTH) xVel*=-1;
	}

	if(type==SNOWBALL) {
		frameTimer -= Window::DELTA_TIME;
		if(frameTimer <= 0) {
			if(xVel>0) frame = (++frame)%4;
			else frame = (--frame+4)%4;
			frameTimer = 0.2;
		}
		imageName = snowball[frame];
		if (!obsSprite.loadPNG("sprites/"+imageName+".png",scale)) {
			cout << "Warning: Could not load sprites/"<<imageName<<".png" << endl;
		}
	}
}

bool Obstacle::done() {
	return y-height/2 > Window::HEIGHT;
}

bool Obstacle::withinBounds(point p) {
	if(p.y < y-width/2) return false;
	if(p.y > y+width/2) return false;
	if(p.x < x-width/2) return false;
	if(p.x > x+width/2) return false;
	return true;
}

// Method to render the PNG sprite on top of the obstacle
void Obstacle::renderSprite(SDL_Plotter& g) {
	// Calculate centered position for the sprite
	int spriteX = static_cast<int>(x) - obsSprite.getWidth() / 2;
	int spriteY = static_cast<int>(y) - obsSprite.getHeight() / 2;
	
	// Render the PNG sprite
	obsSprite.render(g, spriteX, spriteY);
}

// Getter methods for position (useful for rendering)
int Obstacle::getX() const { return static_cast<int>(x); }
int Obstacle::getY() const { return static_cast<int>(y); }

// Method to render both rectangle and sprite
void Obstacle::draw(SDL_Plotter& g) {
	
	// Draw the PNG sprite on top
	renderSprite(g);
}
