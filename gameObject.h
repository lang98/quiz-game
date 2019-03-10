#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class gameObject
{
private:
    float fallingSpeed;

protected:
    int yofA;
    int yofB;
    int yofC;
    int yofD;

public:
    gameObject();
    virtual void init(); //to be overriden

    void moveLetters();

    int getX(int);
    int getY(int);

    void drawBoard();
};

#endif // GAMEOBJECT_H
