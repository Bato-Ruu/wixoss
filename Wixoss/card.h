#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <QSql>
#include <QPixmap>

class Card
{
public:
    Card(int id);
    ~Card();
    static const QString DATABASE;
    QPixmap pixmap;
    QGraphicsPixmapItem* getPixmapItem();
private:
    int id;
    QString imageFile;
    bool isWhite;
    QString name;
};

#endif // CARD_H
