#include "MainWindow.h"
#include "MySecondScene.hpp"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QString* name,int time, QWidget* parent, int i) : QMainWindow(parent)
{
    level=i; // on choisit la scene a creer en fonction de i pris en argument
    if(level==0){       // on creer la première scene
        this->mainScene = new MyScene(name,nullptr);
        this->mainView = new QGraphicsView;
        this->mainView->setScene(mainScene);
        mainView->setWindowTitle("View personnage");
        this->setCentralWidget(mainView);
        this->setWindowTitle("Gaming");
    }
    if(level==1){       // on creer la seconde scene
        this->mainSecondScene = new MySecondScene(name,time,nullptr);
        this->mainView = new QGraphicsView;
        this->mainView->setScene(mainSecondScene);
        mainView->setWindowTitle("View personnage");
        this->setCentralWidget(mainView);
        this->setWindowTitle("Gaming");
    }
    if(level==2){       // on creer la troisieme scene
        this->mainThirdScene = new MyThirdScene(name,time,nullptr);
        this->mainView = new QGraphicsView;
        this->mainView->setScene(mainThirdScene);
        mainView->setWindowTitle("View personnage");
        this->setCentralWidget(mainView);
        this->setWindowTitle("Gaming");
    }
};
MainWindow::~MainWindow(){

}

