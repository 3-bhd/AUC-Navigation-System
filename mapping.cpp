#include "mapping.h"
#include <QInputDialog>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QMessageBox>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QStyleFactory>

Mapping::Mapping(QWidget* parent):QGraphicsView(parent)
{

    plaza = new Level(this, 'p', "C:\\Users\\Muhammad Yasser\\Downloads\\Webp.net-resizeimage (1).png", 1120, 840);
    plaza->g.loadNodes("E:\\New folder (6)\\TaheyFeHuss\\PlazaNodes.txt");
    plaza->g.loadEdges("E:\\New folder (6)\\TaheyFeHuss\\EdgeNodes.txt");
    m_draw = false;
    setMouseTracking(true);
    currentFloor = plaza;
    this->setScene(currentFloor);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setSceneRect(0, 0, 1120, 840);
    this->setMinimumSize(1120, 840);
    this->setInteractive(true);
    // Inside your class constructor or a method
    QPushButton *button = new QPushButton("Find Path");
    button->setStyle(QStyleFactory::create("Fusion"));
    QGraphicsProxyWidget *proxy = this->scene()->addWidget(button);
    connect(button, &QPushButton::clicked, this, &Mapping::onButtonClicked);
    // Position the button at the top left corner of the view
    proxy->setPos(this->mapToScene(45, 166));
}

void Mapping:: keyPressEvent(QKeyEvent* event)
{

    if(event->key() == Qt::Key_Space)
    {
        QString text = QInputDialog::getText(nullptr, "Enter Node", "Node:", QLineEdit::Normal, "Default text");

        nodes.append(text);
        currentFloor->g.addvertex(text.toStdString(), currentFloor->mp);
        m_draw = true;
        if (m_draw)
        {
            QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(currentFloor->mp.x()-2.5, currentFloor->mp.y()-2.5, 10, 10);
            ellipse->setPen(QPen(Qt::black, 3));
            QGraphicsTextItem *t = currentFloor->addText(text);
            t->setPos(ellipse->boundingRect().center() - t->boundingRect().center());
            currentFloor->addItem(ellipse);
        }
    }
    if(event->key() == Qt::Key_E)
    {
        QString text2 = "";
        QString text3= "";

        do
                {
                    text2 = QInputDialog::getText(nullptr, "Enter First Node", "Edge:", QLineEdit::Normal, "Default text");
                    text3 = QInputDialog::getText(nullptr, "Enter Second Node", "Edge:", QLineEdit::Normal, "Default text");
                    string t2 = text2.toStdString();
                    string t3 = text3.toStdString();
                    bool exist = currentFloor->g.addedge(t2, t3, 10);
                    if(exist)
                    {
                        QPointF p1 = currentFloor->g.getPos(t2);
                        QPointF p2 = currentFloor->g.getPos(t3);
                        QLineF l(p1, p2);
                        QGraphicsLineItem *line = new QGraphicsLineItem(l);
                        currentFloor->addItem(line);
                    }
                    if(!exist)
                        qDebug() << "Stop adding Edges";
                }while(text2 != "n" && text3 != "n");
    }
    if(event->key() == Qt::Key_S)
    {
        currentFloor->g.saveNodes("E:\\New folder (6)\\TaheyFeHuss\\PlazaNodes.txt");
        currentFloor->g.saveEdges("E:\\New folder (6)\\TaheyFeHuss\\EdgeNodes.txt");
    }
    if(event->key() == Qt::Key_P)
    {
        printOnScreen();
    }
    if(event->key() == Qt::Key_D)
    {
        QString text = QInputDialog::getText(nullptr, "Enter Node", "Node:", QLineEdit::Normal, "Default text");
        currentFloor->g.deleteNode(text.toStdString());
    }
    if(event->key() == Qt::Key_M)
    {
        clearPath();
        QString s1 = QInputDialog::getText(nullptr, "Node 1", "Where are u?", QLineEdit::Normal, "Default text");
        QString d1 = QInputDialog::getText(nullptr, "Node 2", "Where do you wanna go?", QLineEdit::Normal, "Default text");
        string s = s1.toStdString();
        string d = d1.toStdString();
        if(currentFloor->g.work.find(s) != currentFloor->g.work.end() && currentFloor->g.work.find(d) != currentFloor->g.work.end())
            printShortestPath(s, d);
    }

}

void Mapping::mouseMoveEvent(QMouseEvent* event)
{
    QPointF temp = mapToScene(event->pos());
    currentFloor->mp = temp;
//    qDebug() << temp;
}
void Mapping::mousePressEvent(QMouseEvent* event) {
    if(event->modifiers() & Qt::ControlModifier) {
        // Ctrl is pressed: switch to drag mode
        setDragMode(QGraphicsView::ScrollHandDrag);
    }
    QGraphicsView::mousePressEvent(event);
}

void Mapping::wheelEvent(QWheelEvent* event) {
    if(event->modifiers() & Qt::ControlModifier) {
        // Ctrl is pressed: zoom
        if(event->angleDelta().y() > 0) {
            // Zoom in
            scale(1.1, 1.1);
        } else {
            // Zoom out
            scale(0.9, 0.9);
        }
        event->accept();
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void Mapping::mouseReleaseEvent(QMouseEvent* event) {
    // Switch back to no drag mode
    setDragMode(QGraphicsView::NoDrag);
    QGraphicsView::mouseReleaseEvent(event);
}

void Mapping::printOnScreen()
{
    Graph::vmap::iterator it = currentFloor->g.work.begin();
    while(it != currentFloor->g.work.end())
    {
        QPointF p(it->second->pos);
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(p.x()-2.5, p.y()-2.5, 10, 10);
        ellipse->setPen(QPen(Qt::black, 0));

        QGraphicsTextItem *t = currentFloor->addText(QString::fromStdString(it->second->name));
        t->setTextWidth(3);
        t->setPos(ellipse->boundingRect().center() - t->boundingRect().center());
        currentFloor->addItem(ellipse);
        vector<Graph::vertex::ve> v = it->second->adj;
        for(auto i : v)
        {
            QLineF l(i.second->pos, it->second->pos);
            QGraphicsLineItem *line = new QGraphicsLineItem(l);
            currentFloor->addItem(line);
        }
        it++;
    }
}
void Mapping:: printShortestPath(string s, string d)
{
    vector<string> v = currentFloor->g.AStar(s, d);
    Graph::vertex* ves = currentFloor->g.getVertex(v[0]);


    for(int i = 1; i < v.size(); i++)
    {

        Graph::vertex* ved = currentFloor->g.getVertex(v[i]);
        QLineF l(ves->pos, ved->pos);
        QGraphicsLineItem *line = new QGraphicsLineItem(l);
        pa.push_back(line);
        line->setPen(QPen(Qt::black, 3,Qt::DotLine));
        currentFloor->addItem(line);
        ves = ved;
    }

}
void Mapping::clearPath()
{
    for(auto &line: pa)
    {
        currentFloor->removeItem(line);
    }
    pa.clear();
}
void Mapping::onButtonClicked() {

        clearPath();
        QString s1 = QInputDialog::getText(nullptr, "Enter Node", "Node:", QLineEdit::Normal, "Default text");
        QString d1 = QInputDialog::getText(nullptr, "Enter Node", "Node:", QLineEdit::Normal, "Default text");
        string s = s1.toStdString();
        string d = d1.toStdString();
        if(currentFloor->g.work.find(s) != currentFloor->g.work.end() && currentFloor->g.work.find(d) != currentFloor->g.work.end())
            printShortestPath(s, d);
}
Mapping::~Mapping()
{

}
