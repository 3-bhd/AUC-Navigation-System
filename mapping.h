#ifndef MAPPING_H
#define MAPPING_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPaintEvent>
#include "level.h"
#include <QWheelEvent>

class Mapping : public QGraphicsView
{
    Q_OBJECT
    Level* plaza;
    Level* level1;
    Level* level2;
    Level* currentFloor;
    bool m_draw;
    QVector<QString> nodes;
    vector<QGraphicsLineItem*> pa;
public:
    Mapping(QWidget* parent = nullptr);
    void printShortestPath(string s, string d);
    void printsp(string s, string d);
    void clearPath();
    ~Mapping();
public slots:
    void keyPressEvent(QKeyEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void printOnScreen();
    void onButtonClicked();

};

#endif // MAPPING_H
