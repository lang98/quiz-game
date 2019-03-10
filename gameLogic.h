#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>
#include <string>

#include "gameObject.h"

using namespace std;

class gameLogic : gameObject
{
private:
    vector <string> question;
    vector <string> choice;
    vector <char> answer;

protected:
    int questionCounter;

    char chosen;
    char correctAns;
    bool ifEnded;

    int score;
    int numOfCorrectAns;
    int numOfMissedAns;
    int numOfIncorrectAns;
    int numOfQuestions;
    float percentage;

public:
    gameLogic();
    void init();
    char getCaught();
    void displayResult();

    bool ifAnswered();
    bool getIfEnded();

    void readQues(char);
    void displayQues();

    void calculatePara();
    void displayPara();
    void returnPara(float*);
};

#endif // GAMELOGIC_H
