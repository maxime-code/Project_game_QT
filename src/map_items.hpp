#ifndef PLANE_H
#define PLANE_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QPixmap>
#include <QBrush>


class map_items_sol : public QGraphicsPixmapItem {
public:

    map_items_sol(int x, int y, int w=100, int h=100) : QGraphicsPixmapItem(QPixmap("../resources/2.png").scaled(w,h)) {
        this->setPos(x, y);
    }
}; // bloc de type sol

class map_items_wall_left : public QGraphicsPixmapItem {
public:

    map_items_wall_left(int x, int y, int w, int h) : QGraphicsPixmapItem(QPixmap("../resources/rouge.png").scaled(w,h)) {
        this->setPos(x, y);
    }
}; // bloc de type gauche

class map_items_wall_right : public QGraphicsPixmapItem {
public:

    map_items_wall_right(int x, int y, int w=10, int h=50) : QGraphicsPixmapItem(QPixmap("../resources/6.png").scaled(w,h)) {
        this->setPos(x, y);
    }
}; // bloc de type droit

class map_items_kill : public QGraphicsPixmapItem {
public:

    map_items_kill(int x, int y, int w, int h) : QGraphicsPixmapItem(QPixmap("../resources/boul.png").scaled(w,h)) {
        this->setPos(x, y);
    }
}; // bloc qui élimine le joueur

class player : public QGraphicsPixmapItem{
private:
public:
    player(int x, int y, int w, int h) : QGraphicsPixmapItem(QPixmap("../resources/singe.png").scaled(w,h)){
        this->setPos(x, y);
    }
}; // class joueur

#endif // PLANE_H
