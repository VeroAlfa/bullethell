#include "GameObject.h"

void Bullet::update(){
    //stay still
    if (direction == 0){
        final_xpos += 0;
        final_ypos += 0;
    }
    //up
    else if (direction == 1){
        final_xpos += 0;
        final_ypos += 8;
    }
    //down
    else if (direction == 2){
        final_xpos += 0;
        final_ypos -= 8;
    }
    //left
    else if (direction == 3){
        final_xpos -= 8;
        final_ypos += 0;
    }
    //right
    else if (direction == 4){
        final_xpos += 8;
        final_ypos += 0;
    }
    //object transition
    desRec.x = final_xpos - (desRec.w/2);
    desRec.y = 639 - final_ypos - (desRec.h/2);
}

void Bullet::setDirection(enum Type type){
    if (type == STAY){
        direction = 0;
    }
    else if (type == UP){
        direction = 1;
    }
    else if (type == DOWN){
        direction = 2;
    }
    else if (type == LEFT){
        direction = 3;
    }
    else if (type == RIGHT){
        direction = 4;
    }
}

bool Bullet::isOutScreen(){
    if (final_xpos < 640 && final_xpos >= 0 && final_ypos < 640 && final_ypos >= 0){
        return false;
    }
    else {
        return true;
    }
}

void Bullet::render(){
    if (isOutScreen()){
        clean();
    }
    else {
        TextureManager::renderTex(objectTex, sourceRec, desRec);
    }
}

void Bullet::clean(){
    TextureManager::destroyTex(objectTex);
}
