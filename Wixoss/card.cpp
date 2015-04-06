#include "card.h"
#include <stdio.h>
#include <QtSql>
#include <QDir>

const char* Card::DATABASE = "cards.db";

Card::Card(int id)
{
    this->id = id;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir().toNativeSeparators(Card::DATABASE));
    if(!db.open())
        printf("Ded");
    QSqlQuery query(db);
    QString query_string = "SELECT Name, Image FROM Cards WHERE Id = " + QString::number(id) + ";";
    query.exec(query_string);
    query.first();
    name = query.value(0).toString();
    imageFile = "setimages/" + query.value(1).toString();
    isWhite = query.value(2).toInt() == 1;
    pixmap = QPixmap(QDir().toNativeSeparators(imageFile));
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

