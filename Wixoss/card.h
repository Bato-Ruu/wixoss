#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Card
{
public:
    Card(int id, QString name, QString imageFile, bool isWhite);
    ~Card();
    QPixmap pixmap;
    QGraphicsPixmapItem* getPixmapItem();
private:
    int id;
    QString imageFile;
    QString name;
    bool isWhite;
};

#endif // CARD_H
