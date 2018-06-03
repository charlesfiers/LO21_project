#include <QApplication>
#include <iostream>
#include "autocell.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
//    AutoCell fenetre;
//    fenetre.show();

    AutoCellFactory fac;

    //On enregistre des types
    AutoCellFactory::Register("AutomateDim1",new AutoCellDim1);

    //On crée des objets via la fabrique
    AutoCell *fenetre = fac.Create("AutomateDim1");

    fenetre->show();

    delete fenetre;

    return app.exec();
}
