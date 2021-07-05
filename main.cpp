#include "BulletHell.h"

BulletHell *game = nullptr;

int main(int argc, char **argv)
{
    const int fps = 60;                 //limiting frame rate
    const int frameDelay = 1000/fps;    //limiting frame rate
    Uint32 frameStart;                  //limiting frame rate
    int frameTime;                      //limiting frame rate

    game = new BulletHell();

    game->init("Bullet Hell Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640);

    while (game->checkRunning()){                   //Game loop
        frameStart = SDL_GetTicks();                //limiting frame rate

        game->handleEvents();                       //input handling
        game->update();                             //change object attribute
        game->render();                             //display

        frameTime = SDL_GetTicks() - frameStart;    //limiting frame rate
        if (frameDelay > frameTime){                //limiting frame rate
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();

    return 0;
}
