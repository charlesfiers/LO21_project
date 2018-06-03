#include <QApplication>
#include <iostream>
#include "automate.h"
#include "autocell.h"

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    AutoCell fenetre;
    fenetre.show();
    return app.exec();
}
