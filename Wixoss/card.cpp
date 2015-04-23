#include <QDebug>
#include <QtSql>
#include <QDir>
#include "card.h"


const QString Card::WHITE = QString("setimages/general/white.jpg");
const QString Card::BLACK = QString("setimages/general/black.jpg");


Card::Card()
{

}

Card::Card(int id, QString name, QString imageFile, bool isWhite)
{
    qDebug() << "----- Card Constructor -----" << endl;
    this->id = id;
    this->name = name;
    this->_isWhite = isWhite;

    this->face = new QPixmap(QDir::toNativeSeparators(imageFile));

    // Checks if the imageFile exists
    if (this->face->isNull())
        qDebug() << "Image could not be found" << endl
                 << "Image File Directory: " << QDir::toNativeSeparators(imageFile) << endl;
    qDebug() << "----- End of Card Constructor -----" << endl;
}

QPixmap* Card::getPixmap() {
    return face;
}

int Card::getId()
{
    return id;
}

QString Card::getName()
{
    return name;
}

bool Card::isWhite()
{
    return _isWhite;
}

Card::~Card()
{

}
