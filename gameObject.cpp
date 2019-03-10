#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "gameObject.h"
#include "Globals.h"

using namespace std;

gameObject::gameObject()
{
    for(int x = 0; x < 26; x++){
        for(int y = 0; y < 29; y++){
            if(y == 0 || y == 28)//draw horizontal border
                coor[x][y] = '-';
            else if(x == 0 || x == 25)//draw vertical border
                coor[x][y] = '|';
            else
                coor[x][y] = ' ';//draw space for every other element
        }
    }
    //letters to be at the top
    coor[05][1] = 'A';
    coor[10][1] = 'B';
    coor[15][1] = 'C';
    coor[20][1] = 'D';
    coor[13][27] = 'H'; //Catcher
}

void gameObject::init()
{
    for(int x = 0; x < 26; x++){
        for(int y = 0; y < 29; y++){
            if(y == 0 || y == 28)
                coor[x][y] = '-';
            else if(x == 0 || x == 25)
                coor[x][y] = '|';
            else
                coor[x][y] = ' ';
        }
    }
    coor[05][1] = 'A';
    coor[10][1] = 'B';
    coor[15][1] = 'C';
    coor[20][1] = 'D';
    coor[13][27] = 'H'; //Catcher
}

void gameObject::moveLetters()
{
    yofA = getY('A');
    yofB = getY('B');
    yofC = getY('C');
    yofD = getY('D');

    if(yofA != 27){//if letters are not at bottom

        coor[05][yofA] = ' ';//change to an empty space
        yofA++;
        coor[10][yofB] = ' ';
        yofB++;
        coor[15][yofC] = ' ';
        yofC++;
        coor[20][yofD] = ' ';
        yofD++;

        //move ABCD downward
        if(yofA < 27){
            coor[05][yofA] = 'A';
            coor[10][yofB] = 'B';
            coor[15][yofC] = 'C';
            coor[20][yofD] = 'D';
        }else if(yofA == 27){ //at the bottom of field
            //move the letters so that the catcher will not be covered by letters
            //eg. when catcher catches 'A', the catcher will still be on the filed,
            //but 'A' disappears.
            if(getX('H') == 05){
                coor[10][yofB] = 'B';
                coor[15][yofC] = 'C';
                coor[20][yofD] = 'D';
            }else if(getX('H') == 10){
                coor[05][yofA] = 'A';
                coor[15][yofC] = 'C';
                coor[20][yofD] = 'D';
            }else if(getX('H') == 15){
                coor[05][yofA] = 'A';
                coor[10][yofB] = 'B';
                coor[20][yofD] = 'D';
            }else if(getX('H') == 20){
                coor[05][yofA] = 'A';
                coor[10][yofB] = 'B';
                coor[15][yofC] = 'C';
            }else{
            	coor[05][yofA] = 'A';
	            coor[10][yofB] = 'B';
	            coor[15][yofC] = 'C';
	            coor[20][yofD] = 'D';
			}
        }

        //gotoXY(0,0);
        //gameObject::drawBoard();
    }
}

int gameObject::getX(int obj)
{
    for(int x = 0; x < 26; x++){
        for(int y = 0; y < 29; y++){
            if(coor[x][y] == obj){
                return x;
            }
        }
    }
}

int gameObject::getY(int obj)
{
    for(int x = 0; x < 26; x++){
        for(int y = 0; y < 29; y++){
            if(coor[x][y] == obj){
                return y;
            }
        }
    }
}

void gameObject::drawBoard()
{
    gotoXY(0, 0);
    for(int y = 0; y < 29; y++){
        for(int x = 0; x < 26; x++){
            cout<<(char)coor[x][y];
        }
        cout<<endl;
    }
}
