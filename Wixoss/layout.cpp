#include "layout.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>

Layout::Layout()
{

}

Layout::Layout(QString filename) {
    setLayout(filename);
}

Layout::~Layout()
{

}

int* Layout::getHandPos() {
    return handPos;
}

int* Layout::getMainDeckPos() {
    return mainDeckPos;
}

int* Layout::getLrigDeckPos() {
    return lrigDeckPos;
}

int* Layout::getEnerZonePos() {
    return enerZonePos;
}

int* Layout::getLrigZonePos() {
    return lrigZonePos;
}

int* Layout::getSigniZone1Pos() {
    return signiZone1Pos;
}

int* Layout::getSigniZone2Pos() {
    return signiZone2Pos;
}

int* Layout::getSigniZone3Pos() {
    return signiZone3Pos;
}

int* Layout::getLrigTrashPos() {
    return lrigTrashPos;
}

int* Layout::getTrashPos() {
    return trashPos;
}

int* Layout::getLifeClothPos() {
    return lifeClothPos;
}

int* Layout::getCheckZonePos() {
    return checkZonePos;
}

void Layout::setLayout(QString filename) {
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader xml(file.readAll());
    int* cur;
    int i = 0;
    bool valid = false;
    bool setValue = false;
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            QString key = xml.name().toString();
            if (key == "title") {
                xml.readNext();
                QString title = xml.text().toString();
                valid = true;
                if (title == "LifeCloth") {
                    cur = lifeClothPos;
                } else if (title == "Hand") {
                    cur = handPos;
                } else if (title == "SigniZone1") {
                    cur = signiZone1Pos;
                } else if (title == "CheckZone") {
                    cur = checkZonePos;
                } else if (title == "SigniZone2") {
                    cur = signiZone2Pos;
                } else if (title == "SigniZone3") {
                    cur = signiZone3Pos;
                } else if (title == "MainDeck") {
                    cur = mainDeckPos;
                } else if (title == "Trash") {
                    cur = trashPos;
                } else if (title == "LrigZone") {
                    cur = lrigZonePos;
                } else if (title == "LrigDeck") {
                    cur = lrigDeckPos;
                } else if (title == "LrigTrash") {
                    cur = lrigTrashPos;
                } else if (title == "EnerZone") {
                    cur = enerZonePos;
                } else {
                    valid = false;
                }
                continue;
            }
            if (key == "x") {
                i = 0;
                setValue = true;
            } else if (key == "y") {
                i = 1;
                setValue = true;
            } else if (key == "width") {
                i = 2;
                setValue = true;
            } else if (key == "height") {
                i = 3;
                setValue = true;
            } else {
                setValue = false;
            }
            if (setValue) {
                xml.readNext();
                if (valid) {
                    cur[i] = xml.text().toInt();
                }
            }
        }
    }
    if (xml.hasError()) {
        qDebug() << "Error while parsing Layout xml.";
    }
    qDebug() << "FInished parsing layout";
}
