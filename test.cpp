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

    int getLaneX(int lane)
    {
        if (lane == 0)
            return 122;
        if (lane == 1)
            return 370;
        if (lane == 2)
            return 622;
        return 370;
    }

    void changePos()
    {
        int currX = getLaneX(currLane);
        int targetX = getLaneX(targetLane);
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

struct obstacle
{
public:
    rectangle r;
    int lane;
    int speed;
    bool onScreen;

    obstacle(int lane, int speed = 3)
    {
        this->lane = lane;
        this->speed = speed;
        this->onScreen = true;
        
        
        int xPos = getLaneX(lane) - 20;
        r = rectangle(xPos, -60, 40, 60, color(255, 0, 0));
    }

    void draw(SDL_Plotter &g)
    {
        if (onScreen)
        {
            r.draw(g);
        }
    }

    void update()
    {
        if (!onScreen)
            return;

        r.y += speed;

        if (r.y > WINDOW_HEIGHT)
        {
            onScreen = false;
        }
    }
    
    int getLaneX(int lane) {
        if(lane == 0) return 122;   // Left lane
        if(lane == 1) return 370;   // Center lane
        if(lane == 2) return 622;   // Right lane
        return 370;                 // Default to center
    }
};

int main(int argc, char **argv)
{
    cout << "Starting program..." << endl;
    SDL_Plotter g(WINDOW_HEIGHT, WINDOW_WIDTH, true);
    cout << "SDL_Plotter initialized successfully!" << endl;
    bool running = true;
    char key;

    vector<rectangle> rectangles;
    vector<obstacle> obstacles;
    rectangle lane1(245, 0, 1000, 5, color(0, 0, 255));
    rectangle lane2(495, 0, 1000, 5, color(0, 0, 255));
    rectangle rect(350, 900, 50, 50, color(72, 168, 50));
    player p(rect);
    
    // PNG SPRITE TEST
    PNGSprite testSprite;
    
    // Load your PNG file (change the path below to your desired PNG)
    if (!testSprite.loadPNG("iBePoppinBottles.png")) {
        cout << "Error: PNG file not found! Make sure the file exists." << endl;
        return -1; // Exit if PNG fails to load
    } else {
        cout << "Successfully loaded PNG file!" << endl;
    }

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

           
            if (key == '1')
            {
                // Spawn obstacle in left lane
                obstacles.push_back(obstacle(0, 3));
            }
            if (key == '2')
            {
                // Spawn obstacle in center lane
                obstacles.push_back(obstacle(1, 3));
            }
            if (key == '3')
            {
                // Spawn obstacle in right lane
                obstacles.push_back(obstacle(2, 3));
            }
        }

        // UPDATE
        p.update();
        
        // Update all obstacles
        for (auto& obs : obstacles) {
            obs.update();
        }
        
        // RENDERING
        g.clear();

        lane1.draw(g);
        lane2.draw(g);
        

        testSprite.render(g, 370, 500);
        
        for (auto& obs : obstacles) {
            obs.draw(g);
        }
        
        p.r.draw(g);

        g.update();
        // TIMING
        g.Sleep(16);
    }

    cout << "test.cpp completed!" << endl;
    return 0;
}
