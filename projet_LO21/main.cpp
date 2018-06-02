#include <QApplication>
#include <iostream>
#include <QtGui>
#include <QtXml>
#include "autocell.h"
#include "Xml_Dom.h"

using namespace std;

//int main(int argc, char* argv[]) {
//    QApplication app(argc, argv);
//    AutoCell fenetre;
//    fenetre.show();
//    return app.exec();
//}


int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    Xml_Dom *Dom = new Xml_Dom();
    Dom->show();

    return app.exec();
}
