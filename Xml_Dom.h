#ifndef XML_DOM
#define XML_DOM

#include <QtGui>
#include <QtXml>
#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QFileDialog>
#include "automate.h"
#include <sstream>
#include <QXmlStreamWriter>
#include <QMap>
class Xml_Dom : public QWidget
{
private:
    //QFile* file;
    QDomDocument* doc;
    QDomNode noeud;
    QDomElement dom_element;
public:
    void ajouter_config(int,Etat);
    void ajouter_config_dim2(unsigned int minv,unsigned int minm,unsigned int maxv,unsigned int maxm, int nb, Etat e);
    QMap<std::string,std::string> charger_config();
    QMap<std::string,std::string> charger_config_dim2();
    Xml_Dom();
    ~Xml_Dom();
    // On rajoutera des variables et des méthodes après.

};

#endif
