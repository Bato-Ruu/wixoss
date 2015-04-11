#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <card.h>
#include <QDebug>
#include <QTime>
#include "databaseaccessor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    handScene = new QGraphicsScene(this);
    ui->hand->setScene(handScene);
    mainDeckScene = new QGraphicsScene(this);
    ui->mainDeck->setScene(mainDeckScene);
    lrigDeckScene = new QGraphicsScene(this);
    ui->lrigDeck->setScene(lrigDeckScene);
    enerZoneScene = new QGraphicsScene(this);
    ui->enerZone->setScene(enerZoneScene);
    lrigZoneScene = new QGraphicsScene(this);
    ui->lrigZone->setScene(lrigZoneScene);
    signi1ZoneScene = new QGraphicsScene(this);
    ui->signi1Zone->setScene(signi1ZoneScene);
    signi2ZoneScene = new QGraphicsScene(this);
    ui->signi2Zone->setScene(signi2ZoneScene);
    signi3ZoneScene = new QGraphicsScene(this);
    ui->signi3Zone->setScene(signi3ZoneScene);
    lrigTrashScene = new QGraphicsScene(this);
    ui->lrigTrash->setScene(lrigTrashScene);
    trashScene = new QGraphicsScene(this);
    ui->trash->setScene(trashScene);
    lifeClothScene = new QGraphicsScene(this);
    ui->lifeCloth->setScene(lifeClothScene);
    checkZoneScene = new QGraphicsScene(this);
    ui->checkZone->setScene(checkZoneScene);
    checkZoneScene = new QGraphicsScene(this);
    ui->checkZone->setScene(checkZoneScene);

    qsrand(QTime::currentTime().msec());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    Card c = DatabaseAccessor::getCardById(qrand() % 760 + 1);
    qDebug() << "Created new card.\n";
    handScene->addItem(c.getPixmapItem());
}
