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
    pa = new PlayArea();
    QGraphicsScene* s = new QGraphicsScene(this);
    pa->setScene(s);
    ui->playAreaCanvas->setSceneRect(0, 0, 1280, 720);
    s->setSceneRect(0, 0, 1280, 720);
    ui->playAreaCanvas->setScene(s);
    pa->init();
    //ui->playAreaCanvas->showFullScreen();
    qsrand(QTime::currentTime().msec());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   pa->repaintAll();
}
