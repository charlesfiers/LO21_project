#include "Xml_Dom.h"
#include <iostream>
using namespace std;

Xml_Dom::Xml_Dom() : QWidget()
{
    QDomDocument* doc = new QDomDocument("mon_xml");
    QFile* file = new QFile("/Users/charles/Desktop/Cours_UTC/LO21/LO21_project/projet_LO21/doc1.xml");
    if(!file->open(QIODevice::ReadWrite))
    {
        QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
        return;
    }
    dom_element = doc->documentElement();
    noeud = dom_element.firstChild();
    while(!noeud.isNull())
    {
        if(!dom_element.isNull())
            QMessageBox::information(this, "Nom de la balise", "Le nom de la balise est " + dom_element.tagName());
                noeud = noeud.nextSibling();
    }
}

QString Xml_Dom::charger_config(){
    return dom_element.nodeName();
}

void Xml_Dom::ajouter_config(int nb, Etat e){
    std::cout << "ok" << std::endl;
    QDomElement new_element = doc->createElement("config");
    new_element.setAttribute("automate_number",nb);
    doc->appendChild(new_element);
    std::stringstream out;
    out << e;
    new_element.appendChild(doc->createTextNode(QString::fromStdString(out.str())));
    QString write_doc = doc->toString();
    QTextStream stream(file);
    stream << "<?xml version='1.0' encoding='UTF-8'?>" << write_doc; // On utilise l'opérateur << pour écrire write_doc dans le document XML.
    file->close();
}

Xml_Dom::~Xml_Dom()
{

}
