#include "gameCatcher.h"
#include "gameObject.h"
#include "Globals.h"

gameCatcher::gameCatcher()
{
    xOfCatcher = getX('H');
    yOfCatcher = getY('H');
}

void gameCatcher::init()
{
    xOfCatcher = getX('H');
    yOfCatcher = getY('H');
}

void gameCatcher::moveRight()
{
    if(xOfCatcher < 24){
        coor[xOfCatcher][yOfCatcher] = ' ';
        coor[xOfCatcher + 1][yOfCatcher] = 'H';
        xOfCatcher++;
    }
}

void gameCatcher::moveLeft()
{
    if(xOfCatcher > 1){
        coor[xOfCatcher][yOfCatcher] = ' ';
        coor[xOfCatcher - 1][yOfCatcher] = 'H';
        xOfCatcher--;
    }
}

void gameCatcher::moveDown()
{
    moveLetters();
}

//2 spaces per movement
void gameCatcher::moveRight(char doubleSpeed)
{
    if(xOfCatcher < 23){
        coor[xOfCatcher][yOfCatcher] = ' ';
        coor[xOfCatcher + 2][yOfCatcher] = 'H';
        xOfCatcher += 2;
    }
}

//2 spaces per movement
void gameCatcher::moveLeft(char doubleSpeed)
{
    if(xOfCatcher > 1){
        coor[xOfCatcher][yOfCatcher] = ' ';
        coor[xOfCatcher - 2][yOfCatcher] = 'H';
        xOfCatcher -= 2;
    }
}

//2 spaces per movement
void gameCatcher::moveDown(char doubleSpeed)
{
    if(getY('A') < 26 && getY('B') < 26){ //make sure the position of letter by checking 2 letters
        moveLetters();
        moveLetters();
    }else{
        moveLetters();
    }
}

