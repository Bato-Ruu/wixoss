#include "card.h"
#include <QDebug>
#include <QtSql>
#include <QDir>

const char* Card::DATABASE = "cards.db";

Card::Card(int id)
{
    this->id = id;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir().toNativeSeparators(Card::DATABASE));
    if(!db.open())
        qDebug() << "Ded\n";
    QSqlQuery query(db);
    QString query_string = "SELECT Name, Image FROM Cards WHERE Id = " + QString::number(id) + ";";
    query.exec(query_string);
    query.first();
    name = query.value(0).toString();
    imageFile = "setimages/" + query.value(1).toString();
    isWhite = query.value(2).toInt() == 1;
    pixmap = QPixmap(QDir().toNativeSeparators(imageFile));
    if (pixmap.isNull())
        qDebug() << "lol fucked\n";
//    pixmapItem = new QGraphicsPixmapItem(pixmap);
    qDebug() << "Hi from card " << name << "\n";
}

QGraphicsPixmapItem* Card::getPixmapItem() {
    QGraphicsPixmapItem* pi = new QGraphicsPixmapItem(pixmap);
    return pi;
}

Card::~Card()
{

}

