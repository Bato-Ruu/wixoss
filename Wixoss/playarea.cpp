#include "playarea.h"
#include "databaseaccessor.h"
#include <QXmlStreamReader>
#include <QGraphicsView>
#include "inplaycard.h"
class InPlayCard;

PlayArea::PlayArea()
{

}

PlayArea::~PlayArea()
{

}

const QString PlayArea::stackNames[] = {"SigniZone1", "CheckZone", "SigniZone2", "SigniZone3",
                        "MainDeck", "Trash", "LrigZone", "LrigDeck", "LrigTrash", "EnerZone", "LifeCloth", "Hand"};


void PlayArea::init() {
    setLayout(QString("res/layout.xml"));
    QPen p(QColor(255, 255, 255, 255));
    QBrush b(QColor(0, 120, 80, 155));
    field = new QGraphicsRectItem(0, 0, 1280, 720);
    scene->addItem(field);
    field->setBrush(b);
    field->setPen(p);
    QGraphicsLineItem* line = new QGraphicsLineItem(320, 0, 320, 720, field);
    line->setPen(p);
    Card testCard = DatabaseAccessor::getCardById(1);
    scale = (((float) getPlayerStack("LrigZone")->getHeight()) / ((float) testCard.getPixmap()->height()));
    qDebug() << getPlayerStack("LrigZone")->getHeight() << scale << testCard.getPixmap()->height();
    QString pstack;
    QString ostack;
    for (int i = 0; i < 12; i++) {
        pstack = PlayArea::stackNames[i];
        ostack = PlayArea::stackNames[11 - i];
        testCard = DatabaseAccessor::getCardById((qrand() % 760) + 1);
        InPlayCard c(testCard);
        Stack* zone = getPlayerStack(pstack);
        zone->getVector()->push_back(c);
        repaint(zone);
        InPlayCard c2(testCard);
        c2.faceDown();
        c2.setRotated(true);
        zone = getOpponentStack(ostack);
        zone->getVector()->push_back(c2);
        repaint(zone);
    }
}

QGraphicsScene* PlayArea::getScene() {
    return scene;
}

void PlayArea::setScene(QGraphicsScene* scene) {
    this->scene = scene;
}

void PlayArea::repaint(Stack* stack) {
    QGraphicsPixmapItem* pi;
    std::vector<InPlayCard>* c = stack->getVector();
    for (InPlayCard &i : *c) {
        //qDebug() << "Repainting card";
        //qDebug() << stack->getWidth() << "," << stack->getHeight();
        //qDebug() << stack->getX() << "," << stack->getY();
        int x = (int) (i.getPixmap()->width() * scale);
        int y = (int) (i.getPixmap()->height() * scale);
        pi = new QGraphicsPixmapItem(i.getPixmap()->scaled(x, y, Qt::KeepAspectRatio, Qt::SmoothTransformation), field);
        pi->setPos(stack->getX() - stack->getWidth() / 2, stack->getY() - stack->getHeight() / 2);
        //scene->addItem(pi);
    }
}

void PlayArea::setLayout(QString filename) {
    int width = 960;
    int height = 720;
    int off = 320;
    minHeight = std::numeric_limits<qreal>::max();
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader xml(file.readAll());
    Stack* curP;
    Stack* curO;
    QString key;
    int tmp;
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            key = xml.name().toString();
            if (key == "title") {
                xml.readNext();
                QString title = xml.text().toString();
                //qDebug() << title;
                curP = new Stack(title);
                curO = new Stack(title);
                playerStacks[title] = curP;
                opponentStacks[title] = curO;
                continue;
            }
            if (key == "x") {
                xml.readNext();
                tmp = xml.text().toInt();
                curP->setX(tmp);
                curO->setX(width - tmp + 2 * off);
                //qDebug() << "x " << cur->getX();
            } else if (key == "y") {
                xml.readNext();
                tmp = xml.text().toInt();
                curP->setY(tmp);
                curO->setY(height - tmp);
                //qDebug() << "y " << cur->getY();
            } else if (key == "width") {
                xml.readNext();
                curP->setWidth(xml.text().toInt());
                curO->setWidth(xml.text().toInt());
                //qDebug() << "width " << cur->getWidth();
            } else if (key == "height") {
                xml.readNext();
                curP->setHeight(xml.text().toInt());
                curO->setHeight(xml.text().toInt());
                minHeight = std::min(minHeight, (qreal) xml.text().toDouble());
                //qDebug() << "height " << cur->getHeight();
            }
        }
    }
    if (xml.hasError()) {
        qDebug() << "Error while parsing Layout xml.";
    }
    qDebug() << "FInished parsing layout";
}

Stack* PlayArea::getPlayerStack(QString stack)
{
    return playerStacks[stack];
}

Stack* PlayArea::getOpponentStack(QString stack)
{
    return opponentStacks[stack];
}

void PlayArea::repaintAll()
{
    QGraphicsView* canvas = scene->views().at(0);
    canvas->resetTransform();
    scaleX = canvas->width() / 1280.f;
    scaleY = canvas->height() / 720.f;
    qreal cscale = std::min(scaleX, scaleY);
    canvas->scale(cscale, cscale);
    qreal offsetX = (1280.f - 1280.f * cscale) / 2;
    qreal offsetY = (720.f - 720.f * cscale) / 2;
    if (offsetX > offsetY) {
        offsetY = 0;
    } else {
        offsetX = 0;
    }
    qDebug() << "scale" << cscale << "offsets" << offsetX << offsetY;
    field->setX(offsetX);
    field->setY(offsetY);
    Stack* zone;
    QString pstack, ostack;
    for (int i = 0; i < 12; i++) {
        pstack = PlayArea::stackNames[i];
        ostack = PlayArea::stackNames[11 - i];
        zone = getPlayerStack(pstack);
        repaint(zone);
        zone = getOpponentStack(ostack);
        repaint(zone);
    }
}
