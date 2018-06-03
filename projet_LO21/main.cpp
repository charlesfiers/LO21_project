#include <QApplication>
#include <iostream>
#include "autocell.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    AutoCell fenetre;
    std::cout << "ok" << std::endl;
    fenetre.show();
    return app.exec();
}
