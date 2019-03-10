#ifndef MENU_H
#define MENU_H

#include <string>

using namespace std;

class menu
{
private:
    int outputXPosition;
    char choice;
    char category;
    char difficulty;
    float fallingSpeed;
    int ifEnded;
    string playerName;

public:
    menu();
    void displayMenu();
    void displayHelp();
    void displayRecord();
    void displayCategory();
    void displayLevel();
    string getName();

    char getCategory();
    float getFallingSpeed();
    bool checkIfEnded();

    int animation(int);
    void displayAniResult(float);

    void endGame();

};

#endif // MENU_H
