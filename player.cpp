#include "player.h"

Player::Player(int width, int height)
{
	lane = 1;
	x = Window::getLaneX(lane);
	targetX = Window::getLaneX(lane);
	y = Window::GROUND_LEVEL;

	this -> width = width;
	this -> height = height;

	if(!playerSprite.loadPNG("sprites/penguin.png",2)) {
		cout << "Error: could not load that jawn";
	}
}

void Player::reset() {
	lane = 1;
	x = Window::getLaneX(lane);
	targetX = Window::getLaneX(lane);
	y = Window::GROUND_LEVEL;
}

void Player::move(action act)
{
	if(targetX==x) {
		if(act == MOVE_LEFT && lane > 0) lane--;
		else if(act == MOVE_RIGHT && lane < 2) lane++;
		targetX = Window::getLaneX(lane);
		xVel = targetXVel;
	}
}

void Player::update()
{
	if(x != targetX) {
		if(x<targetX) x+=xVel*Window::DELTA_TIME;
		else x-=xVel*Window::DELTA_TIME;
		if(fabs(x-targetX) < xVel*Window::DELTA_TIME) x = targetX;
		if(xVel>deaccel) xVel-=deaccel;
	}
}

void Player::corners(point* corners) {
	corners[0] = point(x-width/2,y-width/2);
	corners[1] = point(x-width/2,y+width/2);
	corners[2] = point(x+width/2,y-width/2);
	corners[3] = point(x+width/2,y+width/2);
}

void Player::renderSprite(SDL_Plotter& g) {
	// Calculate centered position for the sprite
	int spriteX = static_cast<int>(x) - playerSprite.getWidth() / 2;
	int spriteY = static_cast<int>(y) - playerSprite.getHeight() / 2;
	
	// Render the PNG sprite
	playerSprite.render(g, spriteX, spriteY);
}

// Getter methods for position (useful for rendering)
int Player::getX() const { return static_cast<int>(x); }
int Player::getY() const { return static_cast<int>(y); }

// Method to render both rectangle and sprite
void Player::draw(SDL_Plotter& g) {
	
	// Draw the PNG sprite on top
	renderSprite(g);
}
