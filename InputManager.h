#include <unordered_map>

class InputManager{
private:
    std::unordered_map<unsigned int, bool> keyMap;
public:
    InputManager(){}
    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);
    bool isKeyPressed(unsigned int keyID);
};
