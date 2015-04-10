#include <QDebug>
#include <QtSql>
#include <QDir>
#include "card.h"

Card::Card(int id, QString name, QString imageFile, bool isWhite)
{
    qDebug() << "----- Card Constructor -----" << endl;
    this->id = id;
    this->name = name;
    this->isWhite = isWhite;

    this->pixmap = QPixmap(QDir::toNativeSeparators(imageFile));

    // Checks if the imageFile exists
    if (this->pixmap.isNull())
        qDebug() << "Image could not be found" << endl
                 << "Image File Directory: " << QDir::toNativeSeparators(imageFile) << endl;
    qDebug() << "----- End of Card Constructor -----" << endl;
}

QGraphicsPixmapItem* Card::getPixmapItem() {
    QGraphicsPixmapItem* pi = new QGraphicsPixmapItem(pixmap);
    return pi;
}

Card::~Card()
{

}

