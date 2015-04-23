#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
class Card
{
public:
    static const QString WHITE;
    static const QString BLACK;
    Card();
    Card(int id, QString name, QString imageFile, bool isWhite);
    ~Card();
    virtual QPixmap* getPixmap();
    int getId();
    QString getName();
    bool isWhite();
protected:
    QPixmap* face;
    int id;
    QString imageFile;
    QString name;
    bool _isWhite;
};

#endif // CARD_H
