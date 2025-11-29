#include <iostream>
#include <vector>
#include "SDL_Plotter.h"

using namespace std;

const int WINDOW_WIDTH = 750;
const int WINDOW_HEIGHT = 1000;
const int GROUND_LEVEL = 950;

struct rectangle
{
    int x, y, length, width;
    color col;

    rectangle() : x(0), y(0), length(0), width(0), col(color(0, 0, 0)) {}
    rectangle(int x, int y, int length, int width, color col)
    {
        this->x = x;
        this->y = y;
        this->length = length;
        this->width = width;
        this->col = col;
    }

    void draw(SDL_Plotter &g)
    {
        for (int i = 0; i < length; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                int pixelX = x + j;
                int pixelY = y + i;

                g.plotPixel(pixelX, pixelY, col);
            }
        }
    }
};

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

    void move(playerState newState) {
        if(state != IDLE) return;
        state = newState;
        progress = 0.0;
        
        if(state == MOVING_LEFT && currLane > 0) {
            targetLane = currLane - 1;
        }
        else if(state == MOVING_RIGHT && currLane < 2) {
            targetLane = currLane + 1;
        }
    }

    int getLaneX(int lane) {
        if(lane == 0) return 122;
        if(lane == 1) return 370;
        if(lane == 2) return 622;
        return 370;
    }

    void changePos() {
        int currX = getLaneX(currLane);
        int targetX = getLaneX(targetLane);
        r.x = currX + (targetX - currX) * progress - 25;
    }


    void update()
    {
        if(state == IDLE) return;

        progress += .1 * shiftMultiplier;

        if(progress >= 1.0) {
            currLane = targetLane;
            state = IDLE;
            progress = 0.0;
        }
        changePos();
    }
};

int main(int argc, char **argv)
{
    SDL_Plotter g(WINDOW_HEIGHT, WINDOW_WIDTH, true);
    bool running = true;
    char key;

    vector<rectangle> rectangles;
    rectangle lane1(245, 0, 1000, 5, color(0, 0, 255));
    rectangle lane2(495, 0, 1000, 5, color(0, 0, 255));
    rectangle rect(350, 900, 50, 50, color(72, 168, 50));
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

        // UPDATE
        p.update();
        // RENDERING
        g.clear();

        lane1.draw(g);
        lane2.draw(g);
        p.r.draw(g);

        g.update();

        // TIMING
        g.Sleep(16);
    }

    cout << "test2.cpp completed!" << endl;
    return 0;
}
