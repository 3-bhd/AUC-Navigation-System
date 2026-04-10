#include "level.h"
#include <QPixmap>

Level::Level(QObject *parent, char floor, string path, int newWidth, int newHeight)
    : QGraphicsScene{parent}
{
    f = floor;
    QPixmap pix(QString::fromStdString(path));
    pix = pix.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setBackgroundBrush(QBrush(pix));

}
Level::~Level()
{

}
