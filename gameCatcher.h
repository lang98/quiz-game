#ifndef GAMECATCHER_H
#define GAMECATCHER_H
#include "gameObject.h"

class gameCatcher : public gameObject
{
private:
    int xOfCatcher;
    int yOfCatcher;
public:
    gameCatcher();
    void init(); //overriding the function with the same name in its parent class gameObject
    void moveLeft();
    void moveRight();
    void moveDown();

    void moveLeft(char);
    void moveRight(char);
    void moveDown(char);
};

#endif // GAMECATCHER_H
