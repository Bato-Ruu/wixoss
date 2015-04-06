#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <card.h>
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //scene = new QGraphicsScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    Card c = Card(1);
    printf("Created new card.\n");
    ui->graphicsView->scene()->addItem(c.getPixmapItem());
}
