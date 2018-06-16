#include <QApplication>
//#include <iostream>
//#include "autocell.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    //AutoCellDim1 fenetre;

    FenPrincipale w;
    w.show();

    //fenetre.show();
    return app.exec();
}
