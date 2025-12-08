#include "window_manager.h"
#include "obstacles.h"
#include "player.h"
using namespace std;

vector<Obstacle*> obstacles;
int score;
double velocityMultiplier;
double obstacleDelay;

void displayScore() {
	cout << "\033c";
	cout << setfill('*') << setw(14) << "" << endl;
	cout << setfill(' ');
	cout << "* Score: "<< setw(3) << score << " *" << endl;
	cout << setfill('*') << setw(14) << "" << endl;
}

void addScore() {
	score++;
	velocityMultiplier = 1+log2(score)/4;
	obstacleDelay = 1.2*pow(0.95,score)+0.3;
	displayScore();
}

int lane = rand()%3;
void addObstacle() {
	int type = rand()%10;
	lane = (lane+1+rand()%2)%3;
	int yVel = 100*velocityMultiplier;
	int xVel = 0;
	switch(type) {
		case 7: //Tall
			obstacles.push_back(new Obstacle(lane, yVel, 0, 80));
			break;
		case 8: //Bouncing
			xVel = rand()%50+100;
			if(rand()%2==0) xVel*=-1;
			obstacles.push_back(new Obstacle(lane, yVel, xVel, 20, 20));
			break;
		case 9: // Double
			obstacles.push_back(new Obstacle((lane+1)%3, yVel));
		default:// Default Obstacle
			obstacles.push_back(new Obstacle(lane, yVel));
	}
	//cout << "New Obstacle: " << obstacles.size() << endl;
}

void removeObstacle(Obstacle* o) {
	auto it = remove(obstacles.begin(), obstacles.end(), o);
	if (it != obstacles.end()) {
		delete o; 
		obstacles.erase(it, obstacles.end());
	}
	addScore();
	//cout << "Removed Obstacle: " << obstacles.size() << endl;
}

bool colliding(Player player, Obstacle* ob) {
	point corners[4];
	player.corners(corners);
	for(point p : corners) {
		if(ob->withinBounds(p)) return true;
	}
	return false;
}

int WinMain(int argc, char **argv)
{
	//Initialize Window and Player
    //cout << "Starting program." << endl;
	SDL_Plotter g(Window::HEIGHT,Window::WIDTH,true);
    Window w(g);
	Player p(30,30);
	w.Render();
	bool alive;
	double obstacleTimer;
	action a;

	while(w.IsRunning()) {
		//Setup
		score = 0;
		alive = true;
		velocityMultiplier = 1.0;
		obstacleDelay = 1.5;
		obstacleTimer = obstacleDelay;
		displayScore();
		while(w.IsRunning() && alive) {
			//Obstacle Spawning
			obstacleTimer-=Window::DELTA_TIME;
			if(obstacleTimer <= 0) {
				addObstacle();
				obstacleTimer = obstacleDelay;
			}

			//Player Movement
			a = w.GetAction();
			if(a==MOVE_LEFT || a==MOVE_RIGHT) p.move(a);
			p.update();

			//Obstacle Movement and Collision Check
			for(Obstacle* o : obstacles) {
				o->update();
				if(colliding(p,o)) alive=false;
				if(o->done()) removeObstacle(o);
			}

			//Rendering
			w.Render();
			w.NextFrame();
		}
		if(w.IsRunning()) cout << "Press R to Restart" << endl;
		for(Obstacle* o : obstacles) {
			o->removeRect();
		}
		obstacles.clear();
		w.Render();
		do {
			a = w.GetAction();
			w.NextFrame();
		} while(a!=RESTART && w.IsRunning());
		p.reset();
	}

	return 0;
}
