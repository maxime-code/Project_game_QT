#ifndef CPP_QT_TPMINIPROJET_MENUWINDOWS_H
#define CPP_QT_TPMINIPROJET_MENUWINDOWS_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QMainWindow>

class FirstWindow : public QMainWindow {

Q_OBJECT

private:

    QLabel* prologue;               //texte d'intro
    QPushButton* newGame;           //boutton commencer le jeu
    QTextEdit* name;                //le joueur saisie son nom
    QString* namePlayer;            //récupération du nom
    QPushButton* leaderboard;
    QPushButton* quitGame;          //quitter le jeu
    QWidget* widgetParent;

public:
    explicit FirstWindow(QMainWindow* = nullptr);

public slots:

    void test();
    void newGameWindow();
    void printLeaderboard();
};

class SecondWindow : public QMainWindow {

Q_OBJECT

private:

    QLabel* prologue;               //texte d'intro
    QPushButton* newGame;           //boutton commencer le jeu
    QTextEdit* name;                //le joueur saisie son nom
    QString* namePlayer;            //récupération du nom
    QPushButton* leaderboard;
    QPushButton* restart;
    QPushButton* quitGame;          //quitter le jeu
    QWidget* widgetParent;

    int time;
public:

    explicit SecondWindow(QString* name,int time, QMainWindow* = nullptr);
public slots:

    void nextGameWindow();
    void test();
    void restartGameWindow();
    void printLeaderboard();
};

class ThirdWindow : public QMainWindow {
Q_OBJECT
private:
    QLabel* prologue;       //texte d'intro
    QPushButton* newGame;           //boutton commencer le jeu
    QPushButton* leaderboard;       //le joueur saisie son nom
    QPushButton* quitGame;
    QPushButton* restart;
    QString* namePlayer;        //récupération du nom
    QWidget* widgetParent;


    int time;
public:
    explicit ThirdWindow(QString* name,int time, QMainWindow* = nullptr);
public slots:
    void next2GameWindow();
    void test();
    void printLeaderboard();

    void restartGameWindow();
};

class FourthWindow : public QMainWindow {
Q_OBJECT
private:
    QLabel* prologue;
    QPushButton* leaderboard;
    QPushButton* quitGame;
    QPushButton* restart;
    QString* namePlayer;
    QWidget* widgetParent;
public:
    explicit FourthWindow(QString* name, QMainWindow* = nullptr);
public slots:
    void test();
    void printLeaderboard();

    void restartGameWindow();
};

class Leaderboard : public QMainWindow {
Q_OBJECT
private:
    QLabel* prologue;
    QWidget* widgetParent;
public:
    explicit Leaderboard(QMainWindow* = nullptr);
public slots:
};

#endif //CPP_QT_TPMINIPROJET_MENUWINDOWS_H
