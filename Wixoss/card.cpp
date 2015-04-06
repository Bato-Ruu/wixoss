#include <QDebug>
#include <QtSql>
#include <QDir>
#include "card.h"

const QString Card::DATABASE = "cards.db";

Card::Card(int id)
{
    qDebug() << "----- Card Constructor -----" << endl;
    this->id = id;

    QString databasePath = QDir::toNativeSeparators(Card::DATABASE);
    //QDir().toNativeSeparators(QDir().currentPath() + "/" + Card::DATABASE);

    // Makes a new database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);

    // Checks if database can't be opened
    if(!db.open())
        qDebug() << "Database could not be found" << endl
                 << "Database path: " << databasePath << endl;


    // Query database

    QSqlQuery query(db);

    // Gets the card name and image from the database cards
    QString query_string = QString("SELECT Name, Image FROM Cards WHERE Id = %1;").arg(QString::number(id));
    query.exec(query_string);

    //qDebug() << "Executed Query: " << query.executedQuery() << endl;

    query.first();  // Checks and sets the query to the first row

    // Initializing the values of the card
    name = query.value(0).toString();
    imageFile = QDir().currentPath() + "/setimages/" + query.value(1).toString();
    isWhite = query.value(2).toInt() == 1;
    pixmap = QPixmap(QDir().toNativeSeparators(imageFile));

    // Checks if the imageFile exists
    if (pixmap.isNull())
        qDebug() << "Image could not be found" << endl
                 << "Image File Directory: " << QDir().toNativeSeparators(imageFile) << endl;
        //pixmapItem = new QGraphicsPixmapItem(pixmap);

    //qDebug() << "Hi from card " << name.toUtf8().data() << "." << endl;
    db.close();
    qDebug() << "----- End of Card Constructor -----" << endl;
}

QGraphicsPixmapItem* Card::getPixmapItem() {
    QGraphicsPixmapItem* pi = new QGraphicsPixmapItem(pixmap);
    return pi;
}

Card::~Card()
{

}

