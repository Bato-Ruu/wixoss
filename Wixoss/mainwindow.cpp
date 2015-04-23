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
    ui->playAreaCanvas->setSceneRect(ui->centralWidget->rect());
    s->setSceneRect(0, 0, 1280, 720);
    ui->playAreaCanvas->setScene(s);
    pa->init();
    ui->playAreaCanvas->showFullScreen();
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
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "widget" << ui->centralWidget->rect();
    qDebug() << "canvas" << ui->playAreaCanvas->rect();
    pa->repaint("LrigTrash");
}
void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   pa->repaint("Hand");
}
