#ifndef ENDING_H
#define ENDING_H

#include <string>
#include <vector>

using namespace std;

class ending
{
private:
    int outputXPosition;
    float paraData[5];
    string playerName;
    string categoryName;
    vector<string> fileTemp;
    vector<int> scoreStorage;

    //bool ifAgain;

public:
    ending();
    void getPara(const float*, const string&, char);
    void writeToRecord();

    bool getIfAgain();

};

#endif // ENDING_H
