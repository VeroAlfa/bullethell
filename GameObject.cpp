#include "GameObject.h"

GameObject::GameObject(const char* texturesheet,int x, int y, int scale)
{
    SDL_Surface* tmpSurface = IMG_Load(texturesheet);                   //load image to surface
    objectTex = TextureManager::loadTexture(tmpSurface);                //load object texture from file name

    sourceRec.x = 0;                    //default at corner
    sourceRec.y = 0;                    //default at corner
    TextureManager::getPixels(objectTex, &sourceRec.w, &sourceRec.h);   //get resolution of file and pass to sourceRec

    desRec.h = sourceRec.h / scale;     //set desRec height
    desRec.w = sourceRec.w / scale;     //set desRec width

    init_xpos = final_xpos = x;         //set initial pos of desRec
    init_ypos = final_ypos = y;         //set initial pos of desRec
}

GameObject::~GameObject(){
    clean();
}

void GameObject::update(){
    //object transition
    desRec.x = final_xpos - (desRec.w/2);
    desRec.y = 639 - final_ypos - (desRec.h/2);
}

void GameObject::render(){
    TextureManager::renderTex(objectTex, sourceRec, desRec);
}

void GameObject::clean(){
    TextureManager::destroyTex(objectTex);
}

