#include <iostream>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <string>
#include <fstream>

#include "MenuWindows.h"
#include "MyThirdScene.hpp"
#include "MySecondScene.hpp"

using std::cout; using std::ofstream;
using std::endl; using std::string;
using std::fstream;
using namespace std;


MyThirdScene::MyThirdScene(QString* name,int time, QObject* parent) : QGraphicsScene(parent) {

    this->background.load("../resources/nuite.jpg");                        //background
    this->setSceneRect(0,0, background.width(), background.height());

    this->playerName=name;
    this->time=time;

    this->timer = new QTimer(this);             //création des timers
    this->timer->start(30);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer2 = new QTimer(this);
    this->timer2->start(1000);
    connect(timer2, SIGNAL(timeout()), this, SLOT(update2()));

    pop_blocs();
    addItemsBlocs();
    this->pileBlocsSol[1]->hide();

    monster = new QGraphicsPixmapItem(QPixmap("../resources/golem.png").scaled(500,500));
    monster->setPixmap(monster->pixmap().transformed(QTransform().scale(-1, 1)));
    monster->setPos(100, 260);
    this->addItem(monster);

    water = new QGraphicsRectItem(0,200,background.width(),300);
    this->addItem(water);
    water->hide();

    personnage = new player(0,0,60,80);
    this->addItem(personnage);

    flag = new QGraphicsPixmapItem(QPixmap("../resources/oeuf.png").scaled(30,30));
    flag->setPos(background.width()-50, 180);
    this->addItem(flag);

    info = new QGraphicsSimpleTextItem(QString::number(time));
    this->addItem(info);

    info3 = new QGraphicsSimpleTextItem(*name);
    this->addItem(info3);
};

void MyThirdScene::update() {

    for(QGraphicsView *x : this->views()){
        x->centerOn(personnage);
    }

    if (personnage->collidesWithItem(flag)){
        win = true;
    }
    if(win) {
        ofstream outfile ("../score.txt", ios::app);                //on enregistre le score du joueur
        std::string nam = this->playerName->toStdString();
        outfile << this->time << " secondes - Réalisé par "<< nam <<  endl ;
        auto game = new FourthWindow(this->playerName);
        game->show();
        dead = true;
        win = false;
    }
    if(personnage->y() > 500){
        dead = true;
    }
    if(dead){
        monster->setPos(100, 260);
        this->pileBlocsSol[1]->setPos(210, 330);
        personnage->setPos(0, 0);
        dead = false;
    }
    if(personnage->collidesWithItem(water)){
        QPointF posM = monster->pos();
        monster->setPos(posM.rx()+2, posM.ry());
        QPointF posM2 = this->pileBlocsSol[1]->pos();
        this->pileBlocsSol[1]->setPos(posM2.rx()+2, posM2.ry());
    }
    QPointF pos = personnage->pos();
    personnage->setPos(pos.rx()+x, pos.ry()+y);
    info->setPos(pos.rx()+x, pos.ry()+y-30);
    info3->setPos(pos.rx()+x+20, pos.ry()+y-30);

    collSol = false;
    collLeft = false;
    collRight = false;

    for (auto wall : this->pileBlocsSol) {          //détection de collisions
        if (personnage->collidesWithItem(wall)) {
            collSol = true;
        }
    }
    for (auto pic : this->pileBlocsKill) {          //détection de collisions des items qui tuent le joueur
        QPointF posM3 = pic->pos();
        pic->setPos(posM3.rx()-5, posM3.ry());
        if (personnage->collidesWithItem(pic)) {
            dead = true;
        }
    }
    for (auto wall : this->pileBlocsLeft) {
        if (personnage->collidesWithItem(wall)) {
            collLeft = true;
            cout << "left" <<endl;
        }
    }
    for (auto wall : this->pileBlocsRight) {
        if (personnage->collidesWithItem(wall)) {
            collRight = true;
        }
    }
    if(collLeft){
        right = false;
    }
    if(collRight){
        left = false;
    }
    if (!collSol & !jumping) {
            y=10;
    }
    if (collSol & !jumping){
        y=0;
    }
    if(jumping){
        y-=5;
        if(y<-35){
            y=0;
            jumping = false;
        }
    }
    if(left){
        x=-5;
    }
    else if(right){
        x=5;
    }
    else{
        x=0;
    }
};

void MyThirdScene::update2() {
    delete info;
    time=time+1;
    info = new QGraphicsSimpleTextItem(QString::number(time));
    this->addItem(info);
    int oof = rand() % 500 + 200 ;
    this->pileBlocsKill.push_back(new map_items_kill(background.width(), oof, 30, 25));
    this->addItem(this->pileBlocsKill[this->n]);
    n++;
};

void MyThirdScene::drawBackground(QPainter *painter, const QRectF &rect) {      //background
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

MyThirdScene::~MyThirdScene() {

}

void MyThirdScene::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Right){
        right = false;
    }
    if(event->key() == Qt::Key_Left){
        left = false;
    }
}
void MyThirdScene::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Right){
        right = true;
    } // aller à droite
    if(event->key() == Qt::Key_Left){
        left = true;
    } // aller à gauche
    if(event->key() == Qt::Key_Space){          //sauter
        for(auto wall : this->pileBlocsSol){
            if(personnage->collidesWithItem(wall)){
                jumping = true;
            }
        }
    }
}

void MyThirdScene::pop_blocs() {

    this->pileBlocsSol.push_back(new map_items_sol(0, 100, 50, 10));
    this->pileBlocsSol.push_back(new map_items_sol(210, 330, 250, 1));
    this->pileBlocsSol.push_back(new map_items_sol(background.width()-50, 210, 50, 10));
}

void MyThirdScene::addItemsBlocs() {
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

