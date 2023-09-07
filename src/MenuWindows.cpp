#include "MenuWindows.h"
#include <QtWidgets/QVBoxLayout>
#include <QApplication>
#include "MainWindow.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// la premiere fenetre à s'afficher
FirstWindow::FirstWindow(QMainWindow* parent) : QMainWindow(parent) { // displaying the main menu window
    this->setWindowTitle("Golem's quest");
    this->setFixedSize(600, 400);

    widgetParent = new QWidget();
    auto* layout = new QVBoxLayout;

    prologue = new QLabel("Bienvenue dans Golem's quest.<br> Depuis plusieurs années, les golems, ont envahi le désert de Kabiba,<br>"
                          " le lieu sacré où les singes y vivaient paisiblement. <br>"
                          " En plus de cela, les golems ont volé l'oeuf dorée contenant le futur roi singe<br>"
                          "Votre objectif est donc de récupérer l'oeuf doré afin de restaurer la gloire des singes<br><br><br>"
                          "Entrez votre nom :");
    prologue->setFixedSize(600,120);
    layout->addWidget(this->prologue);

    this->name = new QTextEdit("");
    name->setFixedSize(500,50);
    layout->addWidget(this->name);

    this->newGame = new QPushButton("Nouvelle partie");
    layout->addWidget(this->newGame);

    this->leaderboard = new QPushButton("Score");
    layout->addWidget(this->leaderboard);

    this->quitGame = new QPushButton("Quitter le jeu");
    layout->addWidget(this->quitGame);

    widgetParent->setLayout(layout);
    this->setCentralWidget(widgetParent);

    connect(this->newGame, SIGNAL(clicked()), this, SLOT(newGameWindow()));
    connect(this->leaderboard, SIGNAL(clicked()), this, SLOT(printLeaderboard()));
    connect(this->quitGame, SIGNAL(clicked()), this, SLOT(test())); //close()
};

void FirstWindow::printLeaderboard(){
    auto lead = new Leaderboard();
    lead->show();
};
void FirstWindow::test(){
    QCoreApplication::quit();
};
void FirstWindow::newGameWindow() {

    this->close();
    namePlayer = new QString(name->toPlainText());
    auto game = new MainWindow(this->namePlayer,0,nullptr,0);
    game->showFullScreen();
};

// fenetre s'affiche apres le niveau 1
SecondWindow::SecondWindow(QString* name,int time, QMainWindow* parent) : QMainWindow(parent) {
    this->setWindowTitle("Golem's quest");
    this->setFixedSize(600, 400);

    this->time = time;
    this->namePlayer=name;

    widgetParent = new QWidget();
    auto* layout = new QVBoxLayout;

    prologue = new QLabel("Golem's quest. Episode 2<br> Après avoir passé de nombreuses journées à souffrir dans le désert<br>"
                          " de Kabiba, vous parvenez finalement à le surpasser. <br>"
                          " La prochaine étape du voyage est de traverser l'océan appelé Hasbull.<br>"
                          "Votre objectif se rapproche à vue d'oeil, continuez ainsi !");

    prologue->setFixedSize(600,100);
    layout->addWidget(this->prologue);

    this->newGame = new QPushButton("Niveau suivant");
    layout->addWidget(this->newGame);

    this->restart = new QPushButton("Recommencer la partie (vous perdrez votre progression)");
    layout->addWidget(this->restart);

    this->leaderboard = new QPushButton("Score ");
    layout->addWidget(this->leaderboard);

    this->quitGame = new QPushButton("Quitter le jeu (vous perdrez votre progression)");
    layout->addWidget(this->quitGame);

    widgetParent->setLayout(layout);
    this->setCentralWidget(widgetParent);

    connect(this->newGame, SIGNAL(clicked()), this, SLOT(nextGameWindow()));
    connect(this->restart, SIGNAL(clicked()), this, SLOT(restartGameWindow()));
    connect(this->leaderboard, SIGNAL(clicked()), this, SLOT(printLeaderboard()));
    connect(this->quitGame, SIGNAL(clicked()), this, SLOT(test()));
};

void SecondWindow::nextGameWindow() {
    this->close();
    auto game = new MainWindow(this->namePlayer,this->time,nullptr,1);
    game->showFullScreen();
};
void SecondWindow::restartGameWindow(){
    this->close();
    auto game = new MainWindow(this->namePlayer,0,nullptr,0);
    game->showFullScreen();
};
void SecondWindow::test(){
    QCoreApplication::quit();
};
void SecondWindow::printLeaderboard(){
    auto lead = new Leaderboard();
    lead->show();
};

// fenetre s'affiche apres le niveau 2
ThirdWindow::ThirdWindow(QString* name,int time, QMainWindow* parent) : QMainWindow(parent) {
    this->setWindowTitle("Golem's quest");
    this->setFixedSize(600, 400);

    this->time = time;
    this->namePlayer=name;

    widgetParent = new QWidget();
    auto* layout = new QVBoxLayout;

    prologue = new QLabel("Golem's quest. Episode 3<br> Vous avez réussi à passer l'océan Hasbull.<br>"
                          " En plus de cela, vous avez appris où se trouve l'oeuf dorée contenant le roi singe. <br>"
                          " La prochaine étape du voyage est de traverser une montagne à l'aide d'un géant.<br>"
                          "Votre objectif est très proche, n'abandonnez pas !");

    prologue->setFixedSize(600,100);
    layout->addWidget(this->prologue);

    this->newGame = new QPushButton("Niveau suivant");
    layout->addWidget(this->newGame);

    this->restart = new QPushButton("Recommencer la partie (vous perdrez votre progression)");
    layout->addWidget(this->restart);

    this->leaderboard = new QPushButton("Score ");
    layout->addWidget(this->leaderboard);

    this->quitGame = new QPushButton("Quitter le jeu (vous perdrez votre progression)");
    layout->addWidget(this->quitGame);

    widgetParent->setLayout(layout);
    this->setCentralWidget(widgetParent);

    connect(this->newGame, SIGNAL(clicked()), this, SLOT(next2GameWindow()));
    connect(this->restart, SIGNAL(clicked()), this, SLOT(restartGameWindow()));
    connect(this->leaderboard, SIGNAL(clicked()), this, SLOT(printLeaderboard()));
    connect(this->quitGame, SIGNAL(clicked()), this, SLOT(test()));
};

void ThirdWindow::next2GameWindow() {
    this->close();
    auto game = new MainWindow(this->namePlayer,this->time,nullptr,2);
    game->showFullScreen();
};
void ThirdWindow::restartGameWindow(){
    this->close();
    auto game = new MainWindow(this->namePlayer,0,nullptr,0);
    game->showFullScreen();
};
void ThirdWindow::test(){
    QCoreApplication::quit();
};
void ThirdWindow::printLeaderboard(){
    auto lead = new Leaderboard();
    lead->show();
};

// fenetre s'affiche quand le jeu est fini
FourthWindow::FourthWindow(QString* name, QMainWindow* parent) : QMainWindow(parent) {
    this->setWindowTitle("Golem's quest");
    this->setFixedSize(600, 400);

    widgetParent = new QWidget();
    auto* layout = new QVBoxLayout;

    this->namePlayer=name;

    prologue = new QLabel("Félicitations, vous avez réussi Golem's Quest.<br>"
                          " Votre score a été enregistré, vous pouvez le consulter en cliquant <br>"
                          " sur le boutton score.");

    prologue->setFixedSize(600,100);
    layout->addWidget(this->prologue);

    this->restart = new QPushButton("Recommencer la partie");
    layout->addWidget(this->restart);

    this->leaderboard = new QPushButton("Score ");
    layout->addWidget(this->leaderboard);

    this->quitGame = new QPushButton("Quitter le jeu (vous perdrez votre progression)");
    layout->addWidget(this->quitGame);

    widgetParent->setLayout(layout);
    this->setCentralWidget(widgetParent);

    connect(this->restart, SIGNAL(clicked()), this, SLOT(restartGameWindow()));
    connect(this->leaderboard, SIGNAL(clicked()), this, SLOT(printLeaderboard()));
    connect(this->quitGame, SIGNAL(clicked()), this, SLOT(test()));
};

void FourthWindow::printLeaderboard(){
    auto lead = new Leaderboard();
    lead->show();
};
void FourthWindow::restartGameWindow(){
    this->close();
    auto game = new MainWindow(this->namePlayer,0,nullptr,0);
    game->showFullScreen();
};
void FourthWindow::test(){
    QCoreApplication::quit();
};



Leaderboard::Leaderboard(QMainWindow *) {
    this->setWindowTitle("Leaderboard");
    this->setFixedSize(600, 400);

    widgetParent = new QWidget();
    auto* layout = new QVBoxLayout;

    prologue = new QLabel("");
    int nb=0;
    std::ifstream filein("../score.txt");
    std::vector<std::string> listeNoms;
    std::string ligne;
    while(std::getline(filein, ligne)) {
        //size_t posit = ligne.find(" ");
        std::string nom = ligne.substr(0);
        std::stringstream ss;
        ss << ligne.substr();
        std::cout << nom << std::endl;
        listeNoms.push_back(nom);
        ++nb;
    }

    for(int i=0; i<nb; i++){
        QString oui = prologue->text();
        QString non = oui + "\n"+  "<br>" + QString::fromStdString(listeNoms[i]);
        prologue->setText(non);
        }

    prologue->setFixedSize(600,500);
    layout->addWidget(this->prologue);

    widgetParent->setLayout(layout);
    this->setCentralWidget(widgetParent);
}
