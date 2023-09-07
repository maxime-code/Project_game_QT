#ifndef CPP_QT_TPMINIPROJET_MYTHIRDSCENE_HPP
#define CPP_QT_TPMINIPROJET_MYTHIRDSCENE_HPP


#include <QGraphicsScene>
#include <QTimer>
#include <QRectF>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QVector>
#include <QRectF>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QGraphicsItem>
#include <QMainWindow>
#include <QGraphicsSimpleTextItem>

#include "map_items.hpp"

class MyThirdScene : public QGraphicsScene {

Q_OBJECT

private :
    QGraphicsSimpleTextItem* info;
    QGraphicsSimpleTextItem* info3;

    class player* personnage;
    QString* playerName;

    QTimer* timer2;
    QTimer* timer;
    QPixmap background;

    QGraphicsPixmapItem* flag;
    QGraphicsPixmapItem* monster;
    QGraphicsRectItem* water;

    QVector<map_items_wall_left*> pileBlocsLeft;
    QVector<map_items_wall_right*> pileBlocsRight;
    QVector<map_items_sol*> pileBlocsSol;
    QVector<map_items_kill*> pileBlocsKill;

    int n=0;
    int time;
    bool win=false;
    bool jumping=false;
    bool dead=false;
    bool collLeft=false;
    bool collSol=false;
    bool collRight=false;
    bool right = false;
    bool left = false;
    float x=0;
    float y=0;
public:
    explicit MyThirdScene(QString* name, int time, QObject* parent = nullptr);
    ~MyThirdScene() override;

    void pop_blocs();
    void addItemsBlocs();

    void keyPressEvent(QKeyEvent* event);
    void drawBackground(QPainter* painter, const QRectF& rect);
protected:

    void keyReleaseEvent(QKeyEvent* event);

public slots :
    void update2();
    void update();
};

#endif //CPP_QT_TPMINIPROJET_MYTHIRDSCENE_HPP
