#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H
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

class MyScene : public QGraphicsScene {  // ceci est la classe du premier niveau du jeu
    Q_OBJECT
private :
    QGraphicsSimpleTextItem* info;
    QGraphicsSimpleTextItem* info3;         // On affiche le nom du personnage et le timer dans des QGraphicsSimpleTextItem
    QGraphicsSimpleTextItem* info2;

    QString* playerName;

    QTimer* timer2;             // timer à 1 seconde
    QTimer* timer;              // timer à 30 millisecondes

    QPixmap background;         // fond d'écran

    class player* personnage;
    QGraphicsPixmapItem* flag;          // object graphique important de la scène
    QGraphicsPixmapItem* monster;

    QVector<map_items_wall_left*> pileBlocsLeft;
    QVector<map_items_wall_right*> pileBlocsRight;      // piles contenant tous les blocs de la scène
    QVector<map_items_sol*> pileBlocsSol;
    QVector<map_items_kill*> pileBlocsKill;

    int time=0;             // on commence à t=0
    bool win=false;
    bool jumping=false;
    bool dead;
    bool collLeft=false;
    bool collSol=false;
    bool collRight=false;
    bool right = false;        // savoir si le joueur se déplace
    bool left = false;
    float x=0;              // les coordonnées du joueur
    float y=0;
    float xm=2;
public:
    MyScene(QString* name, QObject* parent = nullptr);
    virtual ~MyScene();

    void pop_blocs();
    void addItemsBlocs();           // fonctions pour créer et placer les blocs sur la map
    void pop_pyramide();
    void pop_jump();

    void keyPressEvent(QKeyEvent* event);                       // évenements du clavier
    void drawBackground(QPainter* painter, const QRectF& rect);
protected:
    void keyReleaseEvent(QKeyEvent* event);

public slots :
    void update2();         // fonctions qui s'exécute tout les x temps
    void update();
};

#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
