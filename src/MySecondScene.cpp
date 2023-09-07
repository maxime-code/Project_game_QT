//
// Created by mroqu on 31/05/2022.
//
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <QGraphicsView>
#include <string>

#include "MenuWindows.h"
#include "MySecondScene.hpp"
#include "MyScene.h"

using namespace std;


MySecondScene::MySecondScene(QString* name,int time, QObject* parent) : QGraphicsScene(parent) {

    this->playerName=name;
    this->time=time;

    this->setSceneRect(0, 0, 3000, 2000);

    this->timer = new QTimer(this);         //création des timer
    this->timer->start(30);//30 ms
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer2 = new QTimer(this);
    this->timer2->start(1000);// 1s
    connect(timer2, SIGNAL(timeout()), this, SLOT(update2()));

    this->setSceneRect(0, 0, 3000, 2000);
    eau = new QGraphicsPixmapItem(QPixmap("../resources/eau2.jpg").scaled(3000,2000));
    eau->setPos(0,0);
    this->addItem(eau);

    water = new QGraphicsRectItem(0,630,3000,2000);
    this->addItem(water);

    baleine = new QGraphicsPixmapItem(QPixmap("../resources/baleine.png").scaled(1550,550));
    baleine->setPos(600, 870);
    this->addItem(baleine);

    monster = new QGraphicsPixmapItem(QPixmap("../resources/requin.png").scaled(500,200));
    monster->setPos(1800, 1000);
    this->addItem(monster);

    monster2 = new QGraphicsPixmapItem(QPixmap("../resources/requin.png").scaled(500,200));
    monster2->setPos(1600, 1400);
    this->addItem(monster2);

    bateau = new QGraphicsPixmapItem(QPixmap("../resources/bateau.png").scaled(500,300));
    bateau->setPos(2200,1700);
    this->addItem(bateau);

    pop_blocs();            //création et placement des blocs
    addItemsBlocs();

    personnage = new player(0,0,60,80);         //création personnage
    this->addItem(personnage);

    flag = new QGraphicsPixmapItem(QPixmap("../resources/drapeau.png").scaled(30,30));      //objectif de fin
    flag->setPos(2300,1700); //2300,1700
    this->addItem(flag);

    info = new QGraphicsSimpleTextItem(QString::number(time));      //timer
    this->addItem(info);

    info2 = new QGraphicsSimpleTextItem(" Touches :\n"
                                        "Fleche du haut pour remonter\n"
                                        "dans l'eau");
    info2->setPos(20,250);
    this->addItem(info2);

    info3 = new QGraphicsSimpleTextItem(*name);     // nom saisie du joueur
    this->addItem(info3);
};

void MySecondScene::update() {

    for(QGraphicsView *x : this->views()){      //suivre le personnage
        x->centerOn(personnage);
    }
    if (personnage->collidesWithItem(flag)){            //condition de victoire
        win = true;
    }
    if(win) {
        auto game = new ThirdWindow(this->playerName,this->time);
        game->show();
        dead = true;
        win = false;
    }
    if(personnage->y() > 2000){     //condition de décès
        dead = true;
    }
    if(dead){                   //décès
        personnage->setPos(40, 60);
        dead = false;
    }
    if(personnage->collidesWithItem(water)){            //personnage dans l'eau
        if(up){
            y=-2;
        }
        else{
            y=2;
        }
    }
    QPointF pos = personnage->pos();                    //déplacement du personnage, de son nom et du timer
    personnage->setPos(pos.rx()+x, pos.ry()+y);
    info->setPos(pos.rx()+x, pos.ry()+y-30);
    info3->setPos(pos.rx()+x+20, pos.ry()+y-30);

    QPointF posMob = monster->pos();                //déplacement des ennemis
    monster->setPos(posMob.rx()+xm, posMob.ry());
    if (personnage->collidesWithItem(monster)){
        dead=true;
        }
    QPointF posMob2 = monster2->pos();
    monster2->setPos(posMob2.rx()+xm, posMob2.ry());
    if (personnage->collidesWithItem(monster2)){
        dead=true;
    }
    collSol = false;
    collLeft = false;
    collRight = false;

    for (auto wall : this->pileBlocsSol) {              //détection les collisions du personnages, et ennemis avec les blocs/l'eau
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
        if (monster->collidesWithItem(wall)) {
            xm=-2;
            monster->setPixmap(monster->pixmap().transformed(QTransform().scale(-1, 1)));
        }
        if (monster2->collidesWithItem(wall)) {
            xm=-2;
            monster2->setPixmap(monster2->pixmap().transformed(QTransform().scale(-1, 1)));
        }
    }
    for (auto wall : this->pileBlocsRight) {
        if (personnage->collidesWithItem(wall)) {
            collRight = true;
        }
        if (monster->collidesWithItem(wall)) {
            xm=2;
            monster->setPixmap(monster->pixmap().transformed(QTransform().scale(-1, 1)));
        }
        if (monster2->collidesWithItem(wall)) {
            xm=2;
            monster2->setPixmap(monster2->pixmap().transformed(QTransform().scale(-1, 1)));
        }
    }
    if(collLeft){
        right = false;
    }
    if(collRight){
        left = false;
    }
    if (!collSol & !jumping) {
            if(personnage->collidesWithItem(water)){
                y=1;
            }
            else{
                y=10;
            }
    }
    if (collSol & !jumping){
        y=0;
    }
    if(jumping){            //sauter
        y-=5;
        if(y<-35){
            y=0;
            jumping = false;
        }
    }
    if(left){               //gauche
        x=-5;
    }
    else if(right){             //droite
        x=5;
    }
    else{
        x=0;
    }
};

void MySecondScene::update2() {
    delete info;
    time=time+1;
    info = new QGraphicsSimpleTextItem(QString::number(time));
    this->addItem(info);
    cout << time << endl;
};

MySecondScene::~MySecondScene() {

}

void MySecondScene::keyReleaseEvent(QKeyEvent *event) {         // ne pas appuyer sur le clavier
    if(event->key() == Qt::Key_Right){
        right = false;
    }
    if(event->key() == Qt::Key_Left){
        left = false;
    }
    if(event->key() == Qt::Key_Up){
        up = false;
    }
}

void MySecondScene::keyPressEvent(QKeyEvent *event) {       //appuyer sur le clavier
    if(event->key() == Qt::Key_Right){
        right = true;
    }
    if(event->key() == Qt::Key_Left){
        left = true;
    }
    if(event->key() == Qt::Key_Up){
        up = true;
    }
    if(event->key() == Qt::Key_Space){
        for(auto wall : this->pileBlocsSol){
            if(personnage->collidesWithItem(wall)){
                jumping = true;
            }
        }
    }
}

void MySecondScene::pop_blocs() {
        this->pileBlocsSol.push_back(new map_items_sol(0, 100, 100, 100));
        this->pileBlocsRight.push_back(new map_items_wall_right(100, 100, 10, 100));

        this->pileBlocsRight.push_back(new map_items_wall_right(0, 100, 1, 2000));
        this->pileBlocsLeft.push_back(new map_items_wall_left(3000, 100, 1, 2000));
}

void MySecondScene::addItemsBlocs() {
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



