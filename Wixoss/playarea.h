#ifndef PLAYAREA_H
#define PLAYAREA_H
#include <vector>
#include "card.h"
#include "stack.h"
#include <QGraphicsScene>

class PlayArea
{
public:
    PlayArea();
    ~PlayArea();
    void init();
    QGraphicsScene* getScene();
    void setScene(QGraphicsScene* s);
    void repaint(Stack* stack);
    void setLayout(QString filename);
    Stack* getPlayerStack(QString stack);
    Stack* getOpponentStack(QString stack);
    static const QString stackNames[];
    void repaintAll();
private:
    qreal scaleX;
    qreal scaleY;
    qreal scale;
    qreal minHeight;
    std::map<QString, Stack*> playerStacks;
    std::map<QString, Stack*> opponentStacks;
    QGraphicsScene* scene;
    QGraphicsRectItem* field;

};
#endif // PLAYAREA_H
