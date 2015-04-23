#ifndef STACK_H
#define STACK_H
#include <vector>
#include <QString>
//#include "card.h"
#include "inplaycard.h"


class Stack
{
private:
    std::vector<InPlayCard>* stack;
    QString name;
    int x, y, width, height;
public:
    Stack();
    ~Stack();
    Stack(QString name);
    std::vector<InPlayCard>* getVector();
    void setVector(std::vector<InPlayCard>* stack);
    void setName(QString name);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);
    QString getName();
    int getXoffset();
    int getYoffset();
};

#endif // STACK_H
