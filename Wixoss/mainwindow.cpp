#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <card.h>
#include <QDebug>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    qsrand(QTime::currentTime().msec());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    Card c = Card(qrand() % 760 + 1);
    qDebug() << "Created new card.\n";
    scene->addItem(c.getPixmapItem());
}
