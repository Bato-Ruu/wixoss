#ifndef DATABASEACCESSOR_H
#define DATABASEACCESSOR_H
#include <QString>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QDir>
#include "card.h"

class DatabaseAccessor
{
public:
    static const QString DATABASE;
    static QSqlDatabase db;
    static Card getCardById(int id);
private:
    DatabaseAccessor();
    ~DatabaseAccessor();
};

#endif // DATABASEACCESSOR_H
