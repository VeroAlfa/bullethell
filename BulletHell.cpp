#include "BulletHell.h"
#include "GameObject.h"
//#include <iostream>
//using namespace std;

Player* marisa;
Enemy* remilia;

SDL_Window* BulletHell::window = nullptr;
SDL_Renderer* BulletHell::renderer = nullptr;
InputManager BulletHell::inputManager;

BulletHell::BulletHell(){}
BulletHell::~BulletHell(){}

void BulletHell::init(const char *title,int x, int y, int w, int h){
    if (SDL_Init(SDL_INIT_VIDEO) == 0){
        //cout << "Game Initialized!..." << endl;

        window = SDL_CreateWindow(title, x, y, w, h, 0);                        //create window
        if (window){
            //cout << "Window Created!..." << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);    //create renderer
        if (renderer){
            SDL_SetRenderDrawColor(renderer,255, 255, 120, 255);
            //cout << "Renderer Created!..." << endl;
        }

        if(TTF_Init() == 0) {
            //cout << "TTF Initialized!..." << endl;
        }

        isRunning = true;

        //initialize GameObject here
        marisa = new Player("assets/alterisa.png", 320, 120, 3);
        remilia = new Enemy("assets/remilia.png", 320, 480, 1);
        marisa->setHitPoints(10);
        remilia->setHitPoints(100);
    }
    else{
        isRunning = false;
    }
}
void BulletHell::handleEvents(){
    // SDL_PollEvent(&event) - Returns 1 if there is a pending event or 0 if there are none available
    // keep loop until there is no pending event left
    while (SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            inputManager.pressKey(event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            inputManager.releaseKey(event.button.button);
            break;
        case SDL_KEYDOWN:
            inputManager.pressKey(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            inputManager.releaseKey(event.key.keysym.sym);
            break;
        default:
            break;
        };
    }

    if (inputManager.isKeyPressed(SDLK_w)){
        marisa->moveUp();
    }
    else if (inputManager.isKeyPressed(SDLK_a)){
        marisa->moveLeft();
    }
    else if (inputManager.isKeyPressed(SDLK_s)){
        marisa->moveDown();
    }
    else if (inputManager.isKeyPressed(SDLK_d)){
        marisa->moveRight();
    }
    else if (inputManager.isKeyPressed(SDLK_j)){
        marisa->shoot = true;
    }
    else if (!inputManager.isKeyPressed(SDLK_j)){
        marisa->shoot = false;
    }
}
void BulletHell::update(){
    marisa->update();
    remilia->update();

    if (marisa->getHitPoints() > 0){
        for (unsigned int j = 0; j < remilia->danmaku.size(); j++){
            if(marisa->checkHit(remilia->danmaku[j])){
                delete remilia->danmaku[j];
                remilia->danmaku.erase(remilia->danmaku.begin() + j);
                remilia->danmaku.shrink_to_fit();
            }
        }
    }
    if (remilia->getHitPoints() > 0){
        for (unsigned int j = 0; j < marisa->danmaku.size(); j++){
            if(remilia->checkHit(marisa->danmaku[j])){
                delete marisa->danmaku[j];
                marisa->danmaku.erase(marisa->danmaku.begin() + j);
                marisa->danmaku.shrink_to_fit();
            }
        }
    }
}
void BulletHell::render(){
    //clear canvas for new image
    SDL_RenderClear(renderer);

    //this is where we add stuff to render
    marisa->render();
    remilia->render();

    //update screen
    SDL_RenderPresent(renderer);

    //add stuff after render

}
void BulletHell::clean(){
    //clean all object
    marisa->clean();
    remilia->clean();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = nullptr;
    renderer = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    //cout << "Game Cleaned!..." << endl;
}

