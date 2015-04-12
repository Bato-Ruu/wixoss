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
