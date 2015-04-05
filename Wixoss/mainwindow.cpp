#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <card.h>
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    //ui->graphicsView->scene()->addItem();
    Card *c = new Card(1);
    printf("Created new card.\n");
}
