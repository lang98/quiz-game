#include <fstream>
#include <string>
#include <iostream>
#include <windows.h> //clrscr, sleep
#include <stdlib.h>  //atoi
#include <sstream>
#include <conio.h> //getch

#include "ending.h"
#include "Globals.h"

using namespace std;

ending::ending()
{
    outputXPosition = windowWidth()/2-10;
}

//get user information, (correct, incorrect, percent. etc) from parameter and store
//in private variables for later use
void ending::getPara(const float para[], const string &name, char category)
{
    //score, percentage[0,1], correct, incorrect, missed,
    for(int i=0; i<5; i++){
        paraData[i] = para[i];
    }
    playerName = name;
    switch(category){
        case 'm': categoryName = "Math"; break;
        case 'p': categoryName = "Physics"; break;
        case 'c': categoryName = "Chemistry"; break;
        case 'b': categoryName = "Biology"; break;
    }
}

//find the value of score and insert new record in the correct position to form
//descending order
void ending::writeToRecord()
{
    fstream fileRecord;
    string line;
    string stemp;
    bool fileEmpty = false;
    ostringstream convert;
    int score = paraData[0];
    int insertPosi;

    fileTemp.clear(); //used for second round, clean the vector content
    scoreStorage.clear();

    //store original text in a vector
    fileRecord.open("HighScores.txt");
    if(fileRecord.is_open()){
        while(getline(fileRecord, line)){
            fileTemp.push_back(line);
        }
        fileRecord.close();
    }else{
        gotoXY(20, 8); cout << "Unable to open file";
    }

    //check if the film is empty
    if(fileTemp.size()==0){
        fileEmpty = true;
    }

    if(!fileEmpty){
        //store original score in a list
        for(int i=0; i<fileTemp.size(); i++){
            if(i % 8 == 2){
                int itemp = atoi(fileTemp[i].c_str());//convert to int from c_str
                scoreStorage.push_back(itemp);//store in the vector
            }
        }

        //check the scores and return the position of the new record where
        //it should be stored, based on the score value
        for(int i=0; i<scoreStorage.size(); i++){
            if(score > scoreStorage[i]){//if the new score is bigger than previous ones
                insertPosi = i;//assign this index to the position that the new record will be in
                break;
            }else{
                insertPosi = i+1;
            }
        }
        insertPosi *= 8; //to insert in the vector of all entries since there are 8 entries
                         //for each player info

        //insert the new record in the correct position
        //insert from the back
        fileTemp.emplace(fileTemp.begin()+insertPosi, "");
        for(int i=4; i>=0; i--){//convert from int to string
            convert << paraData[i];//write to an ostringstream
            stemp = convert.str();//the str value of ostrstream is stored in stemp
            convert.str("");//erase buffer
            fileTemp.emplace(fileTemp.begin()+insertPosi, stemp);//insert the temp
        }
        //insert name and subject
        fileTemp.emplace(fileTemp.begin()+insertPosi, categoryName);
        fileTemp.emplace(fileTemp.begin()+insertPosi, playerName);

        //write everything in the vector back to file
        fileRecord.open("HighScores.txt");
        if(fileRecord.is_open()){
            //write old record to the file
            for(int i=0; i<fileTemp.size(); i++){
                fileRecord << fileTemp[i] <<endl;
            }

            fileRecord.close();
        }
    }else{
        //write new record to the file directly
        fileRecord.open("HighScores.txt");
        fileRecord << playerName <<endl;
        fileRecord << categoryName <<endl;
        for(int i=0; i<5; i++){
            fileRecord << paraData[i] <<endl;
        }
        fileRecord<<endl;
        fileRecord.close();
    }
    gotoXY(0, 0);
    cout<<"You acheived "<<score<<" points"<<endl;
    cout<<"File has been successfully updated"<<endl;
    Sleep(1000);
}

//returns if another game
bool ending::getIfAgain()
{
    char ctemp;
    do{
        system("cls");
        gotoXY(outputXPosition - 5, 5);
        cout<<"Would you like another game?"<<endl;
        gotoXY(outputXPosition - 5, 7);
        cout<<"1. Go to menu";
        gotoXY(outputXPosition - 5, 8);
        cout<<"2. Quit";

        ctemp = _getch();
        switch(ctemp)
        {
            case '1': return false;  break;
            case '2': return true;   break;
        }
    }while(ctemp != '1' || ctemp != '2');
}
