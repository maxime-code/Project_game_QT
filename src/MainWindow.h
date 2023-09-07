#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include "MyScene.h"
#include "MySecondScene.hpp"
#include "MyThirdScene.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT
private :
    int level=0;                //quelle niveau parmis les 3
    MyScene* mainScene;         // scene principale du niveau 1
    MySecondScene* mainSecondScene; // scene principale du niveau 2
    MyThirdScene* mainThirdScene;   // scene principale du niveau 3
    QGraphicsView* mainView;        //view principale
public:

    explicit MainWindow(QString* name,int time=0, QWidget* parent = nullptr, int i = 0);

    ~MainWindow() override;
public slots:
};

#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H
