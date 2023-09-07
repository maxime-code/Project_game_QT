#ifndef CPP_QT_TPMINIPROJET_MYSECONDSCENE_HPP
#define CPP_QT_TPMINIPROJET_MYSECONDSCENE_HPP

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

class MySecondScene : public QGraphicsScene {   // ceci est la classe du second niveau du jeu
Q_OBJECT
private :

    QGraphicsSimpleTextItem* info;
    QGraphicsSimpleTextItem* info3;         // On affiche le nom du personnage et le timer dans des QGraphicsSimpleTextItem
    QGraphicsSimpleTextItem* info2;

    QString* playerName;
    class player* personnage;

    QGraphicsPixmapItem* eau;
    QGraphicsPixmapItem* baleine;
    QGraphicsPixmapItem* bateau;
    QGraphicsPixmapItem* flag;                      // object graphique important de la scène
    QGraphicsPixmapItem* monster;
    QGraphicsPixmapItem* monster2;
    QGraphicsRectItem* water;

    QTimer* timer;                      // timer à 30 milliseconde
    QTimer* timer2;                     // timer à 1 seconde

    QVector<map_items_wall_left*> pileBlocsLeft;
    QVector<map_items_wall_right*> pileBlocsRight;
    QVector<map_items_sol*> pileBlocsSol;
    QVector<map_items_kill*> pileBlocsKill;

    int time;
    bool win=false;
    bool jumping=false;
    bool dead=false;
    bool collLeft=false;
    bool collSol=false;
    bool collRight=false;
    bool right = false;
    bool up = false;
    bool left = false;
    float x=0;              // les coordonnées du joueur
    float y=0;
    float xm=2;
public:
    explicit MySecondScene(QString* name,int time, QObject* parent = nullptr);
    ~MySecondScene() override;
    void pop_blocs();
    void addItemsBlocs();
    void keyPressEvent(QKeyEvent* event);                       // évenements du clavier
    //void drawBackground(QPainter* painter, const QRectF& rect);     //fond d'écran
protected:
    void keyReleaseEvent(QKeyEvent* event);

public slots :
    void update2();                 // fonctions qui s'exécute tout les x temps
    void update();
};






#endif //CPP_QT_TPMINIPROJET_MYSECONDSCENE_HPP
