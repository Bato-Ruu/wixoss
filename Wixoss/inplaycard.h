#ifndef INPLAYCARD_H
#define INPLAYCARD_H

#include "card.h"

class InPlayCard : public Card
{
public:
    InPlayCard();
    InPlayCard(Card c);
    InPlayCard(int id, QString name, QPixmap* pixmap, bool isWhite);
    ~InPlayCard();
    void fromCard(Card c);
    void up();
    void down();
    void faceUp();
    void faceDown();
    bool isUp();
    bool isFaceUp();
    void setRotated(bool rot);
    virtual QPixmap* getPixmap();
    QPixmap* getFace();
private:
    void setBackface();
    QPixmap* backface;
    bool _up;
    bool _faceUp;
    bool rotated;
};
#endif // INPLAYCARD_H
