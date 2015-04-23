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
    scene->addRect(0, 0, 1280, 720, p, b);
    scene->addLine(320, 0, 320, 720, p);
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
        repaint(pstack);
        InPlayCard c2(testCard);
        c2.faceDown();
        c2.setRotated(true);
        zone = getOpponentStack(ostack);
        zone->getVector()->push_back(c2);
        repaint(ostack);
    }
}

QGraphicsScene* PlayArea::getScene() {
    return scene;
}

void PlayArea::setScene(QGraphicsScene* scene) {
    this->scene = scene;
}

void PlayArea::repaint(QString stack) {
    QGraphicsView* canvas = scene->views().at(0);
    canvas->resetTransform();
    scaleX = canvas->width() / 1280.f;
    scaleY = canvas->height() / 720.f;
    qreal offsetX = (1280.f - scaleX * 1280.f) / 2;
    qreal offsetY = (720.f - scaleY * 720.f) / 2;
    qreal cscale = std::min(scaleX, scaleY);
    qDebug() << offsetX << offsetY;
    canvas->scale(cscale, cscale);
    canvas->translate(offsetX, offsetY);
    Stack* p = getPlayerStack(stack);
    Stack* o = getOpponentStack(stack);
    QGraphicsPixmapItem* pi;
    std::vector<InPlayCard>* c = p->getVector();
    std::vector<InPlayCard>* co = o->getVector();
    for (InPlayCard &i : *c) {
        qDebug() << "Repainting card";
        qDebug() << p->getWidth() << "," << p->getHeight();
        qDebug() << p->getX() << "," << p->getY();
        int x = (int) (i.getPixmap()->width() * scale);
        int y = (int) (i.getPixmap()->height() * scale);
        pi = new QGraphicsPixmapItem(i.getPixmap()->scaled(x, y, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        pi->setPos(p->getX() - p->getWidth() / 2, p->getY() - p->getHeight() / 2);
        scene->addItem(pi);
    }

    for (InPlayCard &i : *co) {
        qDebug() << "Repainting card";
        qDebug() << o->getWidth() << "," << o->getHeight();
        qDebug() << o->getX() << "," << o->getY();
        //min = std::min(o->getWidth(), o->getHeight());
        int x = (int) (i.getPixmap()->width() * scale);
        int y = (int) (i.getPixmap()->height() * scale);
        qDebug() << minHeight << scale;
        pi = new QGraphicsPixmapItem(i.getPixmap()->scaled(x, y, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        pi->setPos(o->getX() - o->getWidth() / 2, o->getY() - o->getHeight() / 2);
        //pi->setFlag(QGraphicsItem::ItemIsMovable);
        scene->addItem(pi);
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
