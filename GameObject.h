#include "BulletHell.h"
#include "TextureManager.h"
#include <vector>

class GameObject {
protected:
    int init_xpos;              //initial position must be constant and saved
    int init_ypos;              //initial position must be constant and saved
    int final_xpos;             //final position change by time
    int final_ypos;             //final position change by time
    SDL_Texture *objectTex = nullptr;
    SDL_Rect sourceRec, desRec;
public:
    GameObject(const char* texturesheet,int x, int y, int scale);   //create GameObject with initial parameter
    virtual ~GameObject();      //https://www.geeksforgeeks.org/virtual-destructor/
    virtual void update();
    virtual void render();
    virtual void clean();
    SDL_Rect* getHitbox(){return &desRec;}
};

enum Type {STAY, UP, DOWN, LEFT, RIGHT};
class Bullet : public GameObject {
private:
    int direction = 0;
public:
    Bullet(const char* texturesheet,int x, int y, int scale): GameObject(texturesheet, x, y, scale){}
    ~Bullet(){}
    void update();
    void render();
    void clean();
    void setDirection(enum Type type);
    bool isOutScreen();
};

class Player : public GameObject {
private:
    int hitPoints;
    int framecount = 0;
public:
    Player(const char* texturesheet,int x, int y, int scale): GameObject(texturesheet, x, y, scale){}
    ~Player(){}
    void setHitPoints(int hp){hitPoints = hp;}
    int getHitPoints(){return hitPoints;}
    void shootBullet();
    bool checkHit(Bullet* enemyBullet);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void update();
    void render();
    bool shoot = false;
    std::vector<Bullet*> danmaku;
};

class Enemy : public GameObject {
private:
    int hitPoints;
    int framecount = 0;
public:
    Enemy(const char* texturesheet,int x, int y, int scale): GameObject(texturesheet, x, y, scale){}
    ~Enemy(){}
    void setHitPoints(int hp){hitPoints = hp;}
    int getHitPoints(){return hitPoints;}
    void shootBullet();
    bool checkHit(Bullet* playerBullet);
    void update();
    void render();
    std::vector<Bullet*> danmaku;
};
