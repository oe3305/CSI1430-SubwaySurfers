#include "obsticles.h"

using namespace std;


enum playerState
{
    IDLE,
    MOVING_LEFT,
    MOVING_RIGHT
};

struct player
{
    double shiftMultiplier;
    int currLane = 1;
    int targetLane = 1;
    rectangle r;
    double progress = 0.0;
    playerState state;

    player(rectangle &r)
    {
        this->r = r;
        shiftMultiplier = 1.0;
    }

    void move(playerState newState)
    {
        if (state != IDLE)
            return;
        state = newState;
        progress = 0.0;

        if (state == MOVING_LEFT && currLane > 0)
        {
            targetLane = currLane - 1;
        }
        else if (state == MOVING_RIGHT && currLane < 2)
        {
            targetLane = currLane + 1;
        }
    }

    void changePos()
    {
        int currX = LANES_X[currLane];
        int targetX = LANES_X[targetLane];
        r.x = currX + (targetX - currX) * progress - 25;
    }

    void update()
    {
        if (state == IDLE)
            return;

        progress += .1 * shiftMultiplier;

        if (progress >= 1.0)
        {
            currLane = targetLane;
            state = IDLE;
            progress = 0.0;
        }
        changePos();
    }
};

int WinMain(int argc, char **argv)
{
    cout << "Starting program..." << endl;
    SDL_Plotter g(WINDOW_HEIGHT, WINDOW_WIDTH, true);
    cout << "SDL_Plotter initialized successfully!" << endl;
    bool running = true;
    char key;

    vector<rectangle> rectangles;
    vector<obstacle> obstacles;
    player p(rect);
    
    while (!g.getQuit() && running)
    {
        // INPUT
        if (g.kbhit())
        {
            key = g.getKey();
            if (toupper(key) == 'Q')
            {
                running = false;
                break;
            }
            if (key == LEFT_ARROW)
            {
                p.move(MOVING_LEFT);
            }
            if (key == RIGHT_ARROW)
            {
                p.move(MOVING_RIGHT);
            }
        }

        // UPDATE PLAYER
        p.update();
        
        // Update all obstacles
		/*
        for (auto& obs : obstacles) {
            obs.update();
        }
		*/
        
        // RENDERING
        g.clear();

        lane1.draw(g);
        lane2.draw(g);
        

        testSprite.render(g, 370, 500);
        
		/*
        for (auto& obs : obstacles) {
            obs.draw(g);
        }
		*/
        
        p.r.draw(g);

        g.update();
        // TIMING
        g.Sleep(MSPF);
    }

    cout << "test.cpp completed!" << endl;
    return 0;
}
