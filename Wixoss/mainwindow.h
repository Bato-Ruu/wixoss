#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_drawButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* handScene;
    QGraphicsScene* mainDeckScene;
    QGraphicsScene* lrigDeckScene;
    QGraphicsScene* enerZoneScene;
    QGraphicsScene* lrigZoneScene;
    QGraphicsScene* signi1ZoneScene;
    QGraphicsScene* signi2ZoneScene;
    QGraphicsScene* signi3ZoneScene;
    QGraphicsScene* lrigTrashScene;
    QGraphicsScene* trashScene;
    QGraphicsScene* lifeClothScene;
    QGraphicsScene* checkZoneScene;

};

#endif // MAINWINDOW_H
