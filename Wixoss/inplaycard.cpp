#include "inplaycard.h"
#include <QPixmap>

InPlayCard::InPlayCard()
{

}

InPlayCard::~InPlayCard()
{

}

InPlayCard::InPlayCard(int id, QString name, QPixmap* pixmap, bool isWhite)
{
    this->id = id;
    this->_isWhite = isWhite;
    this->face = pixmap;
    this->name = name;
    this->_up = true;
    this->_faceUp = true;
    setBackface();
}

InPlayCard::InPlayCard(Card c) {
    this->id = c.getId();
    this->_isWhite = c.isWhite();
    this->face = c.getPixmap();
    this->name = c.getName();
    this->_up = true;
    this->_faceUp = true;
    setBackface();
}

void InPlayCard::setBackface() {
    QString filename;
    if (isWhite()) {
        filename = Card::WHITE;
    } else {
        filename = Card::BLACK;
    }
    backface = new QPixmap(filename);
}
void InPlayCard::up() {
    this->_up = true;
}

void InPlayCard::down() {
    this->_up = false;
}

void InPlayCard::faceUp() {
    this->_faceUp = true;
}

void InPlayCard::faceDown() {
    this->_faceUp = false;
}

bool InPlayCard::isUp() {
    return _up;
}

bool InPlayCard::isFaceUp() {
    return _faceUp;
}

QPixmap* InPlayCard::getPixmap()
{
    QPixmap* ret;
    if (!isFaceUp()) {
        ret = backface;
    } else {
    ret = face;
    }
    if (!rotated) {
        return ret;
    }
    QMatrix rm;
    rm.rotate(180);
    ret = new QPixmap(ret->transformed(rm));
    return ret;
}

QPixmap* InPlayCard::getFace() {
    return face;
}

void InPlayCard::setRotated(bool rot) {
    rotated = rot;
}
