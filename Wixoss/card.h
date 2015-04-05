#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <sqlite3.h>

class Card : public QGraphicsPixmapItem
{
public:
    Card(int id);
    ~Card();
    static const char* DATABASE;

private:
    sqlite3* conn;
    int id;
    char* imageFile;
    bool isWhite;
    int print_data(void* priv, char** a, char** b);
};

#endif // CARD_H
