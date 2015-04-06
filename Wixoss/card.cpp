#include "card.h"
//#include <iostream>
#include <QDebug>
#include <QtSql>
#include <QDir>
#include <QTextStream>
using namespace std;

const QString Card::DATABASE = "cards.db";

Card::Card(int id)
{
    QTextStream cout(stdout);
    this->id = id;

    QString databasePath = QDir().toNativeSeparators(QDir().currentPath() + "/debug/" + Card::DATABASE);
        cout << databasePath << endl;
    // Makes a new database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);
    // Checks if database can't be opened
    if(!db.open())
        cout << "Database could not be found" << endl;

    // Query database

    //db.setDatabaseName(QDir::toNativeSeparators(Card::DATABASE));

    QSqlQuery query(db);

    // Gets the card name and image from the database cards
    QString query_string;// + QString::number(id) + ";";
    query.exec("SELECT Name, Image FROM Cards WHERE Id = " + QString::number(id) +  ";");
    cout << query.executedQuery() << endl;
    query.first();  // Checks and sets the query to the first row

    // Initializing the values of the card
    name = query.value(0).toString();
    imageFile = QDir().currentPath() + "/debug/setimages/" + query.value(1).toString();
    isWhite = query.value(2).toInt() == 1;
    pixmap = QPixmap(QDir().toNativeSeparators(imageFile));

    cout << QDir().toNativeSeparators(imageFile) << endl;
    /*** Error Checking ***/
    // Checks if the imageFile exists

    if (pixmap.isNull())
        cout << "Image could not be found" << endl;
//    pixmapItem = new QGraphicsPixmapItem(pixmap);

    cout << "Hi from card " << name.toUtf8().data() << "." << endl;
    db.close();
}

QGraphicsPixmapItem* Card::getPixmapItem() {
    QGraphicsPixmapItem* pi = new QGraphicsPixmapItem(pixmap);
    return pi;
}

Card::~Card()
{

}

