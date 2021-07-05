#include "GameObject.h"
//#include <iostream>
//using namespace std;

void Enemy::shootBullet(){
    danmaku.push_back(new Bullet("assets/traject.png", final_xpos, final_ypos, 1));   //append new object
    danmaku[danmaku.size()-1]->setDirection(DOWN);
}

bool Enemy::checkHit(Bullet* playerBullet){
    if (SDL_HasIntersection(playerBullet->getHitbox(),&desRec)){
        //cout << "Enemy is Hit" << endl;
        hitPoints -= 1;
        return true;
    } else {
        return false;
    }
}

void Enemy::update(){
    if (hitPoints > 0){
        //count frame
        framecount++;

        //player transition
        desRec.x = final_xpos - (desRec.w/2);
        desRec.y = 639 - final_ypos - (desRec.h/2);

        //shoot bullet every 1/3 sec
        if (framecount % 20 == 0){
            framecount = 0;
            //cout << danmaku.size() << endl;     //for memory leak debug
            shootBullet();
        }

        //update bullet and delete outscreen bullet
        for (unsigned int j = 0; j < danmaku.size(); j++){

            if (danmaku[j]->isOutScreen()){
                //cout << "clear danmaku" << endl;    //for memory leak debug
                delete danmaku[j];
                danmaku.erase(danmaku.begin() + j);
                danmaku.shrink_to_fit();
            }
            else {
                danmaku[j]->update();
            }
        }
    }
}

void Enemy::render(){
    if (hitPoints > 0){
        for (unsigned int j = 0; j < danmaku.size(); j++){
            danmaku[j]->render();

        TextureManager::renderTex(objectTex, sourceRec, desRec);
        }
    }
}

