#include "mainwindow.h"
#include <QApplication>
#include "databaseaccessor.h"

int main(int argc, char *argv[])
{
    QSqlDatabase db = DatabaseAccessor::db;
    db.setDatabaseName(DatabaseAccessor::DATABASE);
    // Checks if database can't be opened
    if(!DatabaseAccessor::db.open())
        qDebug() << "Database could not be found" << endl
                 << "Database path: " << DatabaseAccessor::DATABASE << endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
