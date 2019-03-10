#include <iostream>
#include <conio.h> //getch
#include <windows.h> //clrscr
#include <fstream>
#include <string>
#include <stdlib.h> //rand
#include <time.h> //rand
#include <iomanip> //setprecision

#include "menu.h"
#include "Globals.h"

using namespace std;

menu::menu()
{
    difficulty = '1'; //default level of Difficulty

    srand(time(NULL));
}

void menu::displayMenu()
{
    bool exit = false;
    do{
        system("cls");
        ifEnded = false;
        system("cls");
        gotoXY(0,5);
        cout<<"____ ____ ___    ____ ____    _  _ ____ _  _ _   _    ___  ____ _ _  _ ___ ____ "<<endl
            <<"| __ |___  |     |__| [__     |\\/| |__| |\\ |  \\_/     |__] |  | | |\\ |  |  [__  "<<endl
            <<"|__] |___  |     |  | ___]    |  | |  | | \\|   |      |    |__| | | \\|  |  ___] "<<endl;
        menu::outputXPosition = windowWidth()/2-10;
        gotoXY(outputXPosition, 15);
        cout<<"1. Play";
        gotoXY(outputXPosition, 16);
        cout<<"2. View high scores";
        gotoXY(outputXPosition, 17);
        cout<<"3. Help";
        gotoXY(outputXPosition, 18);
        cout<<"4. Level of difficulty"<<endl;
        gotoXY(outputXPosition, 19);
        cout<<"5. Quit"<<endl;
        choice = _getch();
        system("cls");
        //get user's input
        switch(choice)
        {
            case '1': menu::displayCategory(); exit = true; break;
            case '2': menu::displayRecord(); exit = true; break;
            case '3': menu::displayHelp(); exit = true; break;
            case '4': menu::displayLevel(); exit = true; break;
            case '5': menu::endGame(); exit = true; break;
        }
    }while(exit == false);
}

void menu::displayCategory()
{
    bool exit = false;
    char ctemp;
    menu::outputXPosition = windowWidth()/2-10;
    do{
        system("cls");
        gotoXY(outputXPosition, 12);
        cout<<"Choose your Catogory";

        gotoXY(outputXPosition, 15);
        cout<<"1. Math";
        gotoXY(outputXPosition, 16);
        cout<<"2. Physics";
        gotoXY(outputXPosition, 17);
        cout<<"3. Chemistry";
        gotoXY(outputXPosition, 18);
        cout<<"4. Biology"<<endl;
        //get user's input
        ctemp = _getch();
        switch(ctemp){
            case '1': category = 'm'; exit = true; break;
            case '2': category = 'p'; exit = true; break;
            case '3': category = 'c'; exit = true; break;
            case '4': category = 'b'; exit = true; break;
        }
        system("cls");
    }while(exit == false);
}

void menu::displayHelp()
{
    fstream fileHelp;
    string line;
    bool exit = false;

    fileHelp.open("Help.txt");

    cout<<"*** Help ***"<<endl<<endl;

    if(fileHelp.is_open())
    {
        while(getline(fileHelp,line))
        {
            cout<<line<<endl;
        }
        fileHelp.close();
    }else{
        cout<<"Unable to open this file.";
    }

    do{
        cout<<"Press 0 to go back to main menu"<<endl;
        char backToMenu;
        backToMenu = _getch();
        if (backToMenu == '0'){
            displayMenu();
            exit = true;
        }
    }while(exit == false);
}

void menu::displayRecord()
{
    ifstream fileRecord;
    string line;
    bool exit = false;
    int lenOfEntry;
    int counter = 0;
    fileRecord.open("HighScores.txt", ios::out);

    cout<<"*** High scores ***"<<endl<<endl;
    cout<<"|   Name           |  Category   |  Points   |Percentage | Correct   | Incorrect | Missed    |"<<endl;
    cout<<"============================================================================================="<<endl;

    if(fileRecord.is_open())
    {


        while(getline(fileRecord, line)){
            if(line != ""){
                cout<<"|   "<<line;
                //set length of each entry for formatting purpose
                switch(counter % 7){
                    case 0: lenOfEntry = 15; break;
                    case 1: lenOfEntry = 10; break;
                    case 2: lenOfEntry = 8; break;
                    case 3: lenOfEntry = 7; cout<<'%'; break;
                    case 4: lenOfEntry = 8; break;
                    case 5: lenOfEntry = 8; break;
                    case 6: lenOfEntry = 8; break;
                }
                counter++;
                //output a certain number of spaces to format
                for(int i=0; i<(lenOfEntry-line.size()); i++){
                    cout<<" ";
                }
            }else
                cout<<"|"<<endl;
        }
        fileRecord.close();
        cout<<endl<<endl;
    }else{
        cout<<"Unable to open this file.";
    }

    do{
        //get user's input
        cout<<"Press 0 to go back to main menu"<<endl;
        char backToMenu;
        backToMenu = _getch();
        if (backToMenu == '0'){
            displayMenu();
            exit = true;
        }
    }while(exit == false);
}

void menu::displayLevel()
{
    bool exit = false;
    menu::outputXPosition = windowWidth()/2-10;
    do{
        gotoXY(outputXPosition, 12);
        cout<<"Choose your Level of difficulty";

        gotoXY(outputXPosition, 15);
        cout<<"1. Easy";
        gotoXY(outputXPosition, 16);
        cout<<"2. Medium";
        gotoXY(outputXPosition, 17);
        cout<<"3. Hard";
        gotoXY(outputXPosition, 18);
        cout<<"4. Expert"<<endl;

        difficulty = _getch();
        if(difficulty == '1' || difficulty == '2' || difficulty == '3' || difficulty == '4'){
            exit = true;
        }
    }while(exit == false);

    exit = false; //redefine it for the next error message
    do{
        //get user's input
        cout<<"Press 0 to go back to main menu"<<endl;
        char backToMenu;
        backToMenu = _getch();
        if (backToMenu == '0'){
            displayMenu();
            exit == true;
            break;
        }
    }while(exit == false);
}

float menu::getFallingSpeed()
{
    switch(difficulty){
        case '1' : fallingSpeed = 1.3; break;
        case '2' : fallingSpeed = 1.0; break;
        case '3' : fallingSpeed = 0.7; break;
        case '4' : fallingSpeed = 0.4; break;
    }
    return fallingSpeed;
    //return the speed chosen by user previously
}

string menu::getName()
{
    system("cls");
    gotoXY(outputXPosition, 12);
    cout<<"Enter your name and press enter: ";
    getline(cin, playerName);
    Sleep(500); system("cls");
    return playerName;
}

char menu::getCategory()
{
    return category;
}

void menu::endGame()
{
    system("cls");
    gotoXY(outputXPosition - 5, 5);
    cout<<"Thank you for playing this game !!"<<endl<<endl<<endl<<endl;
    ifEnded = true;
}

bool menu::checkIfEnded(){
    return ifEnded;
}

//recursion to create annimation of loading the game
int menu::animation(int barPosi)
{
    int randomTime;
    gotoXY(windowWidth() / 2 - 10, windowHeight() / 2 - 2);
    cout<<"Loading . . .";
    gotoXY(barPosi, windowHeight() / 2);
    cout<<"|";
    if(barPosi < windowWidth() - 5){
        if(rand() % 10 == 0){
            randomTime = rand() % 400;
            Sleep(randomTime);
        }else{
            randomTime = rand() % 10;
            Sleep(randomTime);
        }
        return randomTime + animation(barPosi+1); //return the total time after termination (ms)
    }
}

void menu::displayAniResult(float total)
{
    gotoXY(windowWidth() / 2 - 13, windowHeight() / 2 - 2);
    cout<<"Loading has taken "<<setprecision(3)<<total<<" s";
    Sleep(1500);
}
