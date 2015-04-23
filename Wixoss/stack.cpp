#include "stack.h"

Stack::Stack()
{

}

Stack::~Stack()
{

}

Stack::Stack(QString name) {
    setName(name);
    std::vector<InPlayCard>* stack = new std::vector<InPlayCard>();
    setVector(stack);
}

std::vector<InPlayCard>* Stack::getVector()
{
    return stack;
}

void Stack::setVector(std::vector<InPlayCard>* stack) {
    this->stack = stack;
}

void Stack::setName(QString name) {
    this->name = name;
}

int Stack::getX()
{
    return x;
}

int Stack::getY()
{
    return y;
}

int Stack::getWidth()
{
    return width;
}

int Stack::getHeight()
{
    return height;
}

void Stack::setX(int x)
{
    this->x = x;
}

void Stack::setY(int y)
{
    this->y = y;
}

void Stack::setWidth(int width)
{
    this->width = width;
}

void Stack::setHeight(int height)
{
    this->height = height;
}

QString Stack::getName() {
    return name;
}
