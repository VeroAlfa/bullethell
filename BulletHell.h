#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_Image.h>
#include "InputManager.h"

class BulletHell {
private:
    bool isRunning;
    SDL_Event event;
public:
    BulletHell();
    ~BulletHell();
    void init(const char *title,int x, int y, int w, int h);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool checkRunning() {return isRunning;}
    static SDL_Window *window;          //for create one and only window for entire project
    static SDL_Renderer *renderer;      //for create one and only renderer for entire project
    static InputManager inputManager;   //for create one and only input for entire project
};

