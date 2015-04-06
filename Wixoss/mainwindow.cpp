#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <card.h>
#include <stdio.h>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    Card c = Card(rand() % 760 + 1);
    printf("Created new card.\n");
    scene->addItem(c.getPixmapItem());
}
