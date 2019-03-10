/*
Filename 	: QinRyaGetAsMuch
Program	    : This program is an educational game designed to help students consolidate their knowledge
              by playing multiple choice game. User can control the movement of a catcher to catch letters
              abcd, via keyboard keys. Their scores and percentage and other information will be stored in
              the record for viewing. User can also define the level of difficulty and what subject they
              are interested in practicing.
Outline     : This game is made entirely by object oriented programming, which includes a few classes, as
              included in the header file area. Each class has a certain task, and finally the main.cpp can
              combine those methods of different classes to make the final game work. The game field array
              is set global for easier usage, and functions windowheight and windowwidth and gotoxy are also
              set global since they are needed in every class and they are just as basic and useful as "cout".
Programmer 	: Ryan Qin
Class	    : ICS4UO1
Due Date	: June. 17, 2016
*/

#include <iostream>
#include <conio.h> //kbhit
#include <time.h> //clock
//#include <windows.h> //cls
#include <stdlib.h>
#include <string>
#include <iomanip> //setprecision

#include "Globals.h"
#include "menu.h"
#include "gameObject.h"
#include "gameCatcher.h"
#include "gameLogic.h"
#include "ending.h"
//#include "kbController.h"

using namespace std;

int main()
{
    //variables
    char category; //used to identify which category is chosen
    bool ifOver  = false; //ending of the entire game: true
    bool ifEnded = false; //ending one round of the game: true
    bool ifAnswered; //if the player has chosen the answer: true
                     //returns true once the letters are at the bottom
    int letterCaught;
    int controller;

    clock_t begin_time = clock();
    float diff; //to calculate the time difference, falling speed
    float fallingSpeed;
    string playerName;
    float animationTime;
    float paraData[5] = {0, 0, 0, 0, 0};
                    //score, percentage[0,1], correct, incorrect, missed,

    //Initialize all objects
    menu objMenu;
    gameObject objGame;
    gameCatcher objCatcher;
    gameLogic objLogic;
    ending objEnd;

    //Animation
    animationTime = (float)objMenu.animation(5) / 1000.0;//convert ms to s
    objMenu.displayAniResult(animationTime);

    //************************************************************
    //game begin
    //************************************************************
    while(!ifOver){// if the entire game continues
        objLogic.init();
        objMenu.displayMenu();
        category = objMenu.getCategory();
        ifEnded = objMenu.checkIfEnded();
        if(ifEnded == true) return 0; //selected by user, to quit the game

        playerName = objMenu.getName();
        fallingSpeed = objMenu.getFallingSpeed();

        objLogic.readQues(category);//read question based on subject/category
        objLogic.displayQues();

        //game begin
        while(!ifEnded){ // if this round continues
            ifAnswered = objLogic.ifAnswered(); //check if catches the letter, false
            objGame.drawBoard();
            objLogic.displayPara();
            if(ifAnswered){ // if catch letters
                objLogic.displayResult(); //right or wrong
                objLogic.calculatePara(); //score, percent, correct, incorrect....
                system("cls");
                objLogic.displayQues(); //display the next question

                objGame.init(); //initialize the board so that letters are at top
                objCatcher.init(); //initialize position of the catcher
                ifEnded = objLogic.getIfEnded(); //check if run out of questions
            }
            if(kbhit()){ //if detect keyboard pressed
                controller = _getch(); //get what key is pressed
				objCatcher.executeKeyPressed((char)controller);

				/*
                switch(kbController)
                {
                    case LEFT:  objCatcher.moveLeft();      break;
                    case 'a':   objCatcher.moveLeft('d');   break; //overload, faster movement
                    case RIGHT: objCatcher.moveRight();     break;
                    case 'd':   objCatcher.moveRight('d');  break; //same as above
                    case DOWN:  objCatcher.moveDown();      break;
                    case 's':   objCatcher.moveDown('d');   break; //same as above
                }
				*/
            }else{
                //no key is pressed
                //wait until reaching the time required for letters to change position
                diff = float(clock() - begin_time) / CLOCKS_PER_SEC; //difference between current time and begin time
                if(diff >= fallingSpeed){
                    objGame.moveLetters(); //if the difference reaches the time required, letters will move down
                    begin_time = clock(); //redefine begin time for the next round
                }
            }
        }
        objLogic.returnPara(paraData); //pass by reference to change values
                                       //of the score, percent, correct. etc

        //end
        objEnd.getPara(paraData, playerName, category);
        objEnd.writeToRecord();

        ifOver = objEnd.getIfAgain();//check if user wants to quit or continue another game
    }

    //thank you for player my program
    objMenu.endGame();

    return 0;
}
