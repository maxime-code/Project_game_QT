#include "MyScene.h"
#include "MenuWindows.h"

#include <QDebug>
#include <iostream>
#include <QGraphicsView>
#include <string>
#include <QApplication>

using namespace std;


MyScene::MyScene(QString* name, QObject* parent) : QGraphicsScene(parent) {
    this->playerName = name;        // on récupère le nom saisie par l'utilisateur

    this->background.load("../resources/desert2.jpg");
    this->setSceneRect(0,0, background.width(), background.height());       //fond d'écran

    this->timer = new QTimer(this);
    this->timer->start(30);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));            // création des timers
    this->timer2 = new QTimer(this);
    this->timer2->start(1000);
    connect(timer2, SIGNAL(timeout()), this, SLOT(update2()));

    pop_blocs();            // création des blocs
    addItemsBlocs();        // ajout des blocs dans la map

    personnage = new player(0,100,60,80);       // création personnage
    this->addItem(personnage);

    flag = new QGraphicsPixmapItem(QPixmap("../resources/drapeau.png").scaled(30,30)); // création point d'arrivée
    flag->setPos(90, 60);
    this->addItem(flag);

    info3 = new QGraphicsSimpleTextItem(*name);     //on récupère le nom saisie pour le mettre dans un QGraphicsSimpleTextItem
    this->addItem(info3);

    info = new QGraphicsSimpleTextItem(QString::number(time));      //timer
    this->addItem(info);

    info2 = new QGraphicsSimpleTextItem("Touches :\n"               //info à l'écran
                                        "-> pour aller à droite\n"
                                        "<- pour aller à gauche\n"
                                        "space pour sauter\n"
                                        "vous pouvez vous accrocher aux murs");
    info2->setPos(20,160);
    this->addItem(info2);

    monster = new QGraphicsPixmapItem(QPixmap("../resources/golem.png").scaled(50,50));     //création d'un ennemi
    monster->setPixmap(monster->pixmap().transformed(QTransform().scale(-1, 1)));
    monster->setPos(200, 160);
    this->addItem(monster);
};

void MyScene::update() {

    for(QGraphicsView *x : this->views()){          //suivre le personnage
        x->centerOn(personnage);
    }
    if (personnage->collidesWithItem(flag)){        //condition de victoire
        win = true;
    }
    if(win){                                        //victoire
        auto game = new SecondWindow(this->playerName,this->time);
        game->show();
            dead= true;
            win = false;
    }
    if(personnage->y() > 800){                  //condition de décès
        dead = true;
    }
    if(dead){                                   //décès
        personnage->setPos(20, 250);
        dead = false;
    }
    QPointF pos = personnage->pos();                //déplacement du personnage, de son nom et du timer
    personnage->setPos(pos.rx()+x, pos.ry()+y);
    info->setPos(pos.rx()+x, pos.ry()+y-30);
    info3->setPos(pos.rx()+x+20, pos.ry()+y-30);

    QPointF posMob = monster->pos();                //déplacement ennemi
    monster->setPos(posMob.rx()+xm, posMob.ry());
    if (personnage->collidesWithItem(monster)){
        dead=true;
    }

    collSol = false;
    collLeft = false;
    collRight = false;

    for (auto wall : this->pileBlocsSol) {                  // gérer la collision en fonction des blocs
        if (personnage->collidesWithItem(wall)) {
            collSol = true;
        }
    }
    for (auto wall : this->pileBlocsKill) {
        if (personnage->collidesWithItem(wall)) {
            dead = true;
        }
    }
    for (auto wall : this->pileBlocsLeft) {
        if (personnage->collidesWithItem(wall)) {
            collLeft = true;
            cout << "left" <<endl;
        }
            if (monster->collidesWithItem(wall)) {      //collision de l'ennemi
                monster->setPixmap(monster->pixmap().transformed(QTransform().scale(-1, 1)));
                xm=-2;
            }
    }
    for (auto wall : this->pileBlocsRight) {
        if (personnage->collidesWithItem(wall)) {
            collRight = true;
        }
            if (monster->collidesWithItem(wall)) {  //collision de l'ennemi
                monster->setPixmap(monster->pixmap().transformed(QTransform().scale(-1, 1)));
                xm=2;
            }
    }
    if(collLeft){               //collision joueur
        right = false;
    }
    if(collRight){              //collision joueur
        left = false;
    }
    if (!collSol & !jumping) {      //tomber dans le vide
            y=10;
    }
    if (collSol & !jumping){
        y=0;
    }
    if(jumping){                //le joueur saute
        y-=5;
        if(y<-35){
            y=0;
            jumping = false;
        }
    }
    if(left){               //déplacement gauche
        x=-5;
    }
    else if(right){         //déplacement droit
        x=5;
    }
    else{
        x=0;
    }
};

void MyScene::update2() {               //incrémentation du timer toutes les secondes
    delete info;
    time=time+1;
    info = new QGraphicsSimpleTextItem(QString::number(time));
    this->addItem(info);
};

void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {  // fond d'écran
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}


MyScene::~MyScene() {
}

void MyScene::keyReleaseEvent(QKeyEvent *event) {       //ne pas appuyer sur les touches
    if(event->key() == Qt::Key_Right){
        right = false;
    }
    if(event->key() == Qt::Key_Left){
        left = false;
    }
}
void MyScene::keyPressEvent(QKeyEvent *event) {         //appuyer sur les touches
    if(event->key() == Qt::Key_Right){
        right = true;
    } // aller à droite
    if(event->key() == Qt::Key_Left){
        left = true;
    } // aller à gauche
    if(event->key() == Qt::Key_Space){                  //sauter
        for(auto wall : this->pileBlocsSol){
            if(personnage->collidesWithItem(wall)){
                jumping = true;
            }
        }
    }
}

void MyScene::pop_blocs() {
    this->pileBlocsSol.push_back(new map_items_sol(0, 400));
    this->pileBlocsRight.push_back(new map_items_wall_right(100, 400));
    this->pileBlocsSol.push_back(new map_items_sol(200, 550));
    this->pileBlocsSol.push_back(new map_items_sol(300, 550));
    this->pileBlocsSol.push_back(new map_items_sol(400, 550));
    this->pileBlocsSol.push_back(new map_items_sol(500, 550));
    this->pileBlocsSol.push_back(new map_items_sol(600, 550));
    this->pileBlocsSol.push_back(new map_items_sol(700, 550));
    this->pileBlocsSol.push_back(new map_items_sol(800, 550));//first jump

    pop_pyramide();
    pop_jump();

    this->pileBlocsSol.push_back(new map_items_sol(200, 200, 400, 10));
    this->pileBlocsSol.push_back(new map_items_sol(800, 100, 300, 20));
    this->pileBlocsKill.push_back(new map_items_kill(850, 70, 30, 30));
    this->pileBlocsRight.push_back(new map_items_wall_right(200, 110, 10, 90));
    this->pileBlocsLeft.push_back(new map_items_wall_left(590, 110, 10, 90));
    this->pileBlocsSol.push_back(new map_items_sol(590,100, 100, 10));
    this->pileBlocsSol.push_back(new map_items_sol(110,100, 100, 10));
}

void MyScene::addItemsBlocs() {
    int nbBlocSolKill = this->pileBlocsKill.size();

    for (unsigned int i = 0; i < nbBlocSolKill; i++) {
        map_items_kill* oui = this->pileBlocsKill[i];
        this->addItem(oui);
    }
    int nbBlocSol = this->pileBlocsSol.size();

    for (unsigned int i = 0; i < nbBlocSol; i++) {
        map_items_sol* oui = this->pileBlocsSol[i];
        this->addItem(oui);
    }
    int nbBlocWallLeft = this->pileBlocsLeft.size();

    for (unsigned int i = 0; i < nbBlocWallLeft; i++) {
        map_items_wall_left* oui = this->pileBlocsLeft[i];
        this->addItem(oui);
    }
    int nbBlocWallRight = this->pileBlocsRight.size();

    for (unsigned int i = 0; i < nbBlocWallRight; i++) {
        map_items_wall_right* oui = this->pileBlocsRight[i];
        this->addItem(oui);
    }
}

void MyScene::pop_pyramide() {
    this->pileBlocsLeft.push_back(new map_items_wall_left(300, 530, 10, 20));
    this->pileBlocsSol.push_back(new map_items_sol(300, 520, 30, 10));

    this->pileBlocsLeft.push_back(new map_items_wall_left(330, 510, 10, 20));
    this->pileBlocsSol.push_back(new map_items_sol(330, 500, 30, 10));

    this->pileBlocsLeft.push_back(new map_items_wall_left(360, 490, 10, 20));
    this->pileBlocsSol.push_back(new map_items_sol(360, 480, 30, 10));

    this->pileBlocsLeft.push_back(new map_items_wall_left(390, 470, 10, 20));
    this->pileBlocsSol.push_back(new map_items_sol(390, 460, 30, 10));

    this->pileBlocsLeft.push_back(new map_items_wall_left(420, 450, 10, 20));
    this->pileBlocsSol.push_back(new map_items_sol(420, 440, 200, 10));
    this->pileBlocsKill.push_back(new map_items_kill(480, 410, 30, 30));


    this->pileBlocsRight.push_back(new map_items_wall_right(610, 450, 10, 20));
    this->pileBlocsSol.push_back(new map_items_sol(620, 460, 30, 10));

    this->pileBlocsRight.push_back(new map_items_wall_right(640, 470, 10, 20));
    this->pileBlocsSol.push_back(new map_items_sol(650, 480, 30, 10));

    this->pileBlocsRight.push_back(new map_items_wall_right(670, 490, 10, 20));
    this->pileBlocsSol.push_back(new map_items_sol(680, 500, 30, 10));

    this->pileBlocsRight.push_back(new map_items_wall_right(700, 510, 10, 20));
    this->pileBlocsSol.push_back(new map_items_sol(710, 520, 30, 10));
    this->pileBlocsRight.push_back(new map_items_wall_right(730, 530, 10, 20));
}

void MyScene::pop_jump() {
    this->pileBlocsLeft.push_back(new map_items_wall_left(1050, 550, 10, 50));
    this->pileBlocsSol.push_back(new map_items_sol(1050, 550));
    this->pileBlocsSol.push_back(new map_items_sol(1050, 550));

    this->pileBlocsLeft.push_back(new map_items_wall_left(1220, 420, 10, 50));
    this->pileBlocsSol.push_back(new map_items_sol(1220, 420, 10, 50));

    this->pileBlocsRight.push_back(new map_items_wall_right(1100, 350, 10, 50));
    this->pileBlocsSol.push_back(new map_items_sol(1100, 350, 10, 50));

    this->pileBlocsLeft.push_back(new map_items_wall_left(1220, 270, 10, 50));
    this->pileBlocsSol.push_back(new map_items_sol(1220, 270, 10, 50));

    this->pileBlocsRight.push_back(new map_items_wall_right(1100, 190, 10, 50));
    this->pileBlocsSol.push_back(new map_items_sol(1100, 190, 10, 50));

    this->pileBlocsLeft.push_back(new map_items_wall_left(1220, 100, 10, 50));
    this->pileBlocsSol.push_back(new map_items_sol(1220, 100, 10, 50));

    //this->pileBlocsSol.push_back(new map_items_sol(1360, 150, 300, 30));
    //this->pileBlocsLeft.push_back(new map_items_wall_left(1350, 150, 10, 30));

}


