#include "card.h"
#include <stdio.h>
#include <QtSql>

const char* Card::DATABASE = "cards.db";

Card::Card(int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Card::DATABASE);
    if(!db.open())
        printf("Ded");
    QSqlQuery query(db);
    query.exec("SELECT Name, Image FROM Cards WHERE Id = 1;");
    query.first();
    name = query.value(0).toString();
    imageFile = "setimages/" + query.value(1).toString();
    isWhite = query.value(2).toInt() == 1;
    pixmap = QPixmap(imageFile);
    if (pixmap.isNull())
        printf("lol fucked\n");
//    pixmapItem = new QGraphicsPixmapItem(pixmap);
    printf("Hi from card %s.\n", name.toUtf8().data());
}

QGraphicsPixmapItem* Card::getPixmapItem() {
    QGraphicsPixmapItem* pi = new QGraphicsPixmapItem(pixmap);
    return pi;
}

Card::~Card()
{

}

