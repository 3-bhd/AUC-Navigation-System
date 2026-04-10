#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include "graph.h"

class Level : public QGraphicsScene
{

public:
    char f;
    Graph g;
    QPointF lastPoint;
    QPointF mp;
    explicit Level(QObject *parent = nullptr, char floor = 'p', string path = "", int newWidth = 0, int newHeight = 0);
    ~Level();
};

#endif // LEVEL_H
