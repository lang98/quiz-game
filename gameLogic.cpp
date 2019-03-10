#include <iostream>
#include <windows.h> //clrscr
#include <fstream>
#include <time.h> //rand
#include <stdlib.h> //rand
#include <iomanip> //setprecision

#include "gameLogic.h"
#include "Globals.h"
#include "gameObject.h"

using namespace std;

gameLogic::gameLogic()
{
    score = 0;
    numOfQuestions = 0;
    numOfCorrectAns = 0;
    numOfMissedAns = 0;
    numOfIncorrectAns = 0;
    percentage = 0;

    questionCounter = 1;
    ifEnded = false;

    srand(time(NULL));
}

void gameLogic::init()
{
    score = 0;
    numOfQuestions = 0;
    numOfCorrectAns = 0;
    numOfMissedAns = 0;
    numOfIncorrectAns = 0;
    percentage = 0;

    questionCounter = 1;
    ifEnded = false;

    question.clear();
    choice.clear();
    answer.clear();
}

//if 'H' stays where the letter is located, that means 'H' catches that letter
//this function return which letter is caught
char gameLogic::getCaught()
{
    if(coor[05][27] == 'H')
        return 'a';
    else if(coor[10][27] == 'H')
        return 'b';
    else if(coor[15][27] == 'H')
        return 'c';
    else if(coor[20][27] == 'H')
        return 'd';
    else
        return 'm'; //missed
}

//display correct or not
void gameLogic::displayResult()
{
    chosen = getCaught();
    gotoXY(40, 10);
    cout<<"************";
    gotoXY(40, 11);
    if(chosen == correctAns){
        cout<<"* Correct *";
    }else if(chosen == 'm'){
        cout<<"* Missed *";
    }else{
        cout<<"* Incorrect *";
    }
    gotoXY(40, 12);
    cout<<"************";
    Sleep(1000);
}

//returns true if the player has made the choice
bool gameLogic::ifAnswered()
{
    if(getY('A') == 27 || getY('B') == 27) //if at least a letter is at bottom
        return true;
    else
        return false;
}

//read questions and choices from file
void gameLogic::readQues(char category)
{
    ifstream fileQues;
    string line;
    string strTemp;
    string strArrTemp[4];
    int randomSwap1, randomSwap2;

    //open corresponding file according to user's choice
    switch(category){
        case 'm':
            fileQues.open("quesMath.txt", ios::out); break;
        case 'p':
            fileQues.open("quesPhy.txt", ios::out); break;
        case 'c':
            fileQues.open("quesChem.txt", ios::out); break;
        case 'b':
            fileQues.open("quesBio.txt", ios::out); break;
        case 'r':
            int randNum = rand() % 4; //random
            switch(randNum){
                case 0: fileQues.open("quesMath.txt", ios::out); break;
                case 1: fileQues.open("quesPhy.txt", ios::out); break;
                case 2: fileQues.open("quesChem.txt", ios::out); break;
                case 3: fileQues.open("quesBio.txt", ios::out); break;
            }
    }

    if(fileQues.is_open())
    {
        int counter = 0;
        while(getline(fileQues,line))
        {
            if(line != ""){
                if(counter % 5 == 0){//seperated by lines, first line of every five lines
                    question.push_back(line); //store in questions
                }else{
                    choice.push_back(line); //store in choices
                }
                counter++;
            }
        }
        fileQues.close();
    }else{
        gotoXY(30, 0);
        cout<<"Unable to open this file.";
    }

    //mix up the vector choice
    for(int i=0; i<question.size(); i++){
        //copy the 4 choices of the same question to strArrTemp
        int index = 0;
        for(int j=0; j<4; j++){
            strArrTemp[j] = choice[i*4 + index];
            index++;
        }
        //erase the 4 choices of the same question from the vector
        choice.erase(choice.begin()+i*4, choice.begin()+i*4+4);
        //swap twice to mix up
        for(int a=0; a<2; a++){
            randomSwap1 = rand() % 4;
            randomSwap2 = rand() % 4;
            strTemp = strArrTemp[randomSwap1];
            strArrTemp[randomSwap1] = strArrTemp[randomSwap2];
            strArrTemp[randomSwap2] = strTemp;
        }
        //append back to vector choice at the original position
        for(int a=0; a<4; a++){
            choice.emplace(choice.begin()+i*4, strArrTemp[a]);
            //insert a strig for each iterating process, 4 in total
        }
    }

    //get correct answer and store in vector answer
    for(int i=0; i<question.size(); i++){
        for(int j=0; j<4; j++){
            strTemp = choice[i*4+j];
            //if ended by "**"
            if(strTemp.back() == '*' && strTemp.at(strTemp.size()-2) == '*'){
                switch(j){//append abcd in front of each choice
                    case 0: answer.push_back('a'); break;
                    case 1: answer.push_back('b'); break;
                    case 2: answer.push_back('c'); break;
                    case 3: answer.push_back('d'); break;
                }
                choice[i*4+j].erase(strTemp.size()-2, 2);//erase "**"
            }
        }
    }
}

void gameLogic::displayQues()
{
    int lineCounter = 4;
    int lineCounter2 = 0;
    int selectQues;
	//srand(time(NULL));

    if(!question.empty()){
        selectQues = rand() % question.size(); //randomly choose a question
        correctAns = answer[selectQues]; //get the correct answer
        gotoXY(27, lineCounter2);
        cout<<questionCounter<<". ";

        //************************************************************
        //output algorithm: to display a question in multiple lines
        while(question[selectQues].size() > (windowWidth()-33)){
            gotoXY(30, lineCounter2);
            cout<<question[selectQues].substr(0, windowWidth()-33);
            question[selectQues].erase(0, windowWidth()-33);
            lineCounter2++;
        }
        gotoXY(30, lineCounter2);
        cout<<question[selectQues].substr(0, windowWidth()-33);
        //************************************************************

        question.erase(question.begin()+selectQues); //erase from question vector
        answer.erase(answer.begin()+selectQues); //erase from answer vector

        //output answers in abcd order
        while(lineCounter <= 7){
            gotoXY(30, lineCounter);
            switch(lineCounter){
                case 4: cout<<"a. "; break;
                case 5: cout<<"b. "; break;
                case 6: cout<<"c. "; break;
                case 7: cout<<"d. "; break;
            }
            cout<<choice[selectQues*4];
            choice.erase(choice.begin()+selectQues*4); //erase each answer already displayed
            lineCounter++; //next line
        }
        questionCounter++;
    }else{
        ifEnded = true;
    }
}

//returns true if question has run out
bool gameLogic::getIfEnded()
{
    if(ifEnded) return true;
    else return false;
}

//process the player's info/parameter
void gameLogic::calculatePara()
{
    chosen = getCaught();
    if(chosen == correctAns){
        score += 10; //10 scores per correct question
        numOfCorrectAns++;
    }else if(chosen == 'm'){ //missed
        numOfMissedAns++;
    }else if(chosen != correctAns){ //incorrect
        numOfIncorrectAns++;
    }
    numOfQuestions++;
    //percentage of correct answers
    if(numOfQuestions != 0)
        percentage = (float)numOfCorrectAns / (float)numOfQuestions * 100.0;
    else //make sure the denomenator is not 0
        percentage = 0;
}

//display info at the right bottom of screen
void gameLogic::displayPara()
{
    //score
    gotoXY(windowWidth()-20, windowHeight()-1);
    cout<<"Score: "<<score;
    //question missed
    gotoXY(windowWidth()-20, windowHeight()-2);
    cout<<"Missed: "<<numOfMissedAns;
    //number of incorrect answers
    gotoXY(windowWidth()-20, windowHeight()-3);
    cout<<"Incorrect: "<<numOfIncorrectAns;
    gotoXY(windowWidth()-20, windowHeight()-4);
    cout<<"Correct: "<<numOfCorrectAns;
    gotoXY(windowWidth()-20, windowHeight()-5);
    cout<<"Percentage: "<<setprecision(3)<<percentage <<'%';
}

//pass by reference to change the parameter, in the form of an array
void gameLogic::returnPara(float paraData[])
{
    paraData[0] = 1.0*score;
    paraData[1] = 1.0*percentage;
    paraData[2] = 1.0*numOfCorrectAns;
    paraData[3] = 1.0*numOfIncorrectAns;
    paraData[4] = 1.0*numOfMissedAns;
}
