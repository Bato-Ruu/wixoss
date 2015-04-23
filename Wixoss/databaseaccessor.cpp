#include "databaseaccessor.h"
#include <QSqlQuery>
DatabaseAccessor::DatabaseAccessor()
{

}

DatabaseAccessor::~DatabaseAccessor()
{

}

const QString DatabaseAccessor::DATABASE = QDir::toNativeSeparators("cards.db");
QSqlDatabase DatabaseAccessor::db = QSqlDatabase::addDatabase("QSQLITE");

Card DatabaseAccessor::getCardById(int id) {
    if (id == 0) {
        Card c(0, "Blank", "", false);
        return c;
    }
    QSqlQuery query(DatabaseAccessor::db);

    // Gets the card name and image from the database cards
    QString query_string = QString("SELECT Name, Image FROM Cards WHERE Id = %1;").arg(QString::number(id));
    query.exec(query_string);

    //qDebug() << "Executed Query: " << query.executedQuery() << endl;

    query.first();  // Checks and sets the query to the first row

    // Initializing the values of the card
    QString name = query.value(0).toString();
    QString imageFile = QDir::currentPath() + "/setimages/" + query.value(1).toString();
    bool isWhite = query.value(2).toInt() == 1;
    Card c(id, name, imageFile, isWhite);
    query_string = QString("SELECT e.Effect from Cards c, Effects e, CardsToEffects ce WHERE c.Id = ce.Card AND ce.Effect = e.Id AND c.Id = %1;").arg(QString::number(id));
    query.exec(query_string);
    while(query.next()) {
        qDebug() << query.value(0).toString() << endl;
    }
    //qDebug() << "Hi from card " << name.toUtf8().data() << "." << endl;
    return c;
}
