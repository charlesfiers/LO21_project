#include <QApplication>
#include <iostream>
#include "autocell.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    AutoCellDim2 fenetre;
    std::cout << "ok final" << std::endl;
    fenetre.show();
    return app.exec();
}
