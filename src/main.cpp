#include <QApplication>
#include "MenuWindows.h"

int main(int argc, char *argv[]) {

    QApplication application(argc, argv);       //création de l'application

    FirstWindow oui;
    oui.show();                 //création et affichage de la fenetre

    return application.exec();
}
