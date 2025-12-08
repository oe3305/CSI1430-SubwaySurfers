/*
 * SDL_Plotter.h
 *
 * Version 3.1
 * Add: color and point constructors
 * 12/14/2022
 *
 * Version 3.0
 * 5/31/2022
 *
 * Version 2.4
 * 4/4/2022
 *
 * Version 2.3
 *  6/28/2021
 *
 * Version 2.2
 *  4/26/2019
 *
 *  Dr. Booth
 */

#ifndef SDL_PLOTTER_H_
#define SDL_PLOTTER_H_


//Windows Library
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>

#include <string.h>
#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <queue>
#include <vector>
using namespace std;

const char UP_ARROW    = 1;
const char DOWN_ARROW  = 2;
const char LEFT_ARROW  = 3;
const char RIGHT_ARROW = 4;
const int RED_SHIFT    = 65536;
const int GREEN_SHIFT  = 256;
const int BLUE_SHIFT   = 1;
const int ALPHA_SHIFT  = 16777216;
const int WHITE        = 255;
const int MAX_THREAD   = 100;


//Point
struct point{
	int x,y;
	point(){
		x = y = 0;
	}

	point(int x, int y){
		this->x = x;
		this->y = y;
	}
};

//Color
struct color{
	unsigned int R,G,B;
	color(){
		R = G = B = 0;
	}

	color(int r, int g, int b){
		R = r;
		G = g;
		B = b;
	}
};

//Threaded Sound Function
struct param{
	bool play;
	bool running;
	bool pause;
	SDL_Thread*  threadID;
	SDL_cond *cond;
	SDL_mutex *mut;
	string name;

	param(){
		play = false;
		running = false;
		pause = false;
	    cond = nullptr;
	    mut  = nullptr;
	    threadID = nullptr;
	    name="";
	}
};


class SDL_Plotter{
private:
	SDL_Texture  *texture;
	SDL_Renderer *renderer;
	SDL_Window   *window;
    Uint32       *pixels;
    const Uint8  *currentKeyStates;
    SDL_Event    event;
    int          row, col;
    bool         quit;

    //Keyboard Stuff
    queue<char> key_queue;

    //Mouse Stuff
    queue<point> click_queue;

    //Sound Stuff
    bool SOUND;
    int soundCount;
    map<string, param> soundMap;

    char getKeyPress(SDL_Event & event);

public:
    SDL_Plotter(int r=480, int c=640, bool WITH_SOUND = true);
    ~SDL_Plotter();
    void update();

    bool getQuit();
    void setQuit(bool flag);

    bool kbhit();
    bool mouseClick();
    char getKey();
    point getMouseClick();

    void plotPixel(int x, int y, int r, int g, int b);
    void plotPixel(point p, int r, int g, int b);
    void plotPixel(int x, int y, color=color{});
    void plotPixel(point p, color=color{});

    void clear();
    int getRow();
    int getCol();

    void initSound(string sound);
    void playSound(string sound);
    void quitSound(string sound);

    void Sleep(int ms);

    bool getMouseDown(int& x, int& y);
    bool getMouseUp(int& x, int& y);
    bool getMouseMotion(int& x, int& y);
    void getMouseLocation(int& x, int& y);

    Uint32 getColor(int x, int y);

	void hideWindow();
	void showWindow();
	void destroyWindow();

};

// PNG Sprite Loading Class (requires SDL2_image)
class PNGSprite {
private:
    int width, height;
    std::vector<std::vector<color>> pixels;  // Store as SDL_Plotter colors
    
public:
    PNGSprite() : width(0), height(0) {}
    
    bool loadPNG(const std::string& filename) {
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface) {
            std::cout << "Failed to load PNG: " << IMG_GetError() << std::endl;
            return false;
        }
        
        width = surface->w;
        height = surface->h;
        pixels.resize(height, std::vector<color>(width));
        
        // Lock surface for pixel access
        if (SDL_MUSTLOCK(surface)) {
            SDL_LockSurface(surface);
        }
        
        // Convert SDL surface to SDL_Plotter colors
        Uint32* pixelData = (Uint32*)surface->pixels;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Uint32 pixel = pixelData[y * (surface->pitch / 4) + x];
                Uint8 r, g, b, a;
                SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
                
                // Store pixel (transparent pixels as black for now)
                if (a > 128) {
                    pixels[y][x] = color(r, g, b);
                } else {
                    pixels[y][x] = color(0, 0, 0);
                }
            }
        }
        
        if (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
        
        SDL_FreeSurface(surface);
        return true;
    }
    
    void render(SDL_Plotter& g, int x, int y, bool skipTransparent = true) {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                int drawX = x + col;
                int drawY = y + row;
                
                if (drawX >= 0 && drawX < g.getCol() && drawY >= 0 && drawY < g.getRow()) {
                    color& pixel = pixels[row][col];
                    
                    // Skip black pixels if treating as transparent
                    if (skipTransparent && pixel.R == 0 && pixel.G == 0 && pixel.B == 0) {
                        continue;
                    }
                    
                    g.plotPixel(drawX, drawY, pixel);
                }
            }
        }
    }
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif // SDL_PLOTTER_H_
