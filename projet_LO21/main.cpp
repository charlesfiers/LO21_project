#include <QApplication>
#include <iostream>
#include "autocell.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    AutoCellDim1 fenetre;
    fenetre.show();
    return app.exec();
}
