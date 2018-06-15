#include "Xml_Dom.h"
#include <iostream>
using namespace std;

Xml_Dom::Xml_Dom() : QWidget()
{
    QFile* file = new QFile("/Users/charles/Desktop/Cours_UTC/LO21/LO21_project/projet_LO21/doc1.xml");
    if(!file->open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
        return;
    }
    /*dom_element = doc->documentElement();
    noeud = dom_element.firstChild();
    while(!noeud.isNull())
    {
        if(!dom_element.isNull())
            QMessageBox::information(this, "Nom de la balise", "Le nom de la balise est " + dom_element.tagName());
                noeud = noeud.nextSibling();
    }*/
}

QString Xml_Dom::charger_config(){
    QXmlStreamReader Rxml;

            QString filename = QFileDialog::getOpenFileName(this,
                                       tr("Open Xml"), ".",
                                       tr("Xml files (*.xml)"));

        QFile file(filename);
            if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            std::cerr << "Error: Cannot read file " << qPrintable(filename)
                      << ": " << qPrintable(file.errorString())
                      << std::endl;

        }

        Rxml.setDevice(&file);
        Rxml.readNext();

        while(!Rxml.atEnd())
        {
            if(Rxml.isStartElement())
            {
                if(Rxml.name() == "LAMPS")
                {
                    Rxml.readNext();
                }
                else if(Rxml.name() == "LIGHT1")
                {
                    while(!Rxml.atEnd())
                                {
                                 if(Rxml.isEndElement())
                                 {
                                    Rxml.readNext();
                                    break;
                                 }
                                 else if(Rxml.isCharacters())
                                 {
                                    Rxml.readNext();
                                 }
                                 else if(Rxml.isStartElement())
                                 {
                                 if(Rxml.name() == "State")
                                 {
                                    Rxml.ReadStateElement();
                                 }
                                 else if(Rxml.name() == "Room")
                                 {
                                    Rxml.ReadRoomElement();
                                 }
                                 else if(Rxml.name() == "Potencial")
                                 {
                                    Rxml.ReadPotencialElement();
                                 }
                                 Rxml.readNext();
                             }
                             else
                             {
                             Rxml.readNext();
                             }
                        }
                }
            }
        else
        {
            Rxml.readNext();
        }

        file.close();

            if (Rxml.hasError())
        {
           std::cerr << "Error: Failed to parse file "
                     << qPrintable(filename) << ": "
                     << qPrintable(Rxml.errorString()) << std::endl;
            }
        else if (file.error() != QFile::NoError)
        {
            std::cerr << "Error: Cannot read file " << qPrintable(filename)
                      << ": " << qPrintable(file.errorString())
                      << std::endl;
        }
    }
}

void Xml_Dom::ajouter_config(int nb, Etat e){
    QXmlStreamWriter xmlWriter(file);
    std::cout << "ok" << std::endl;
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("config");
    xmlWriter.writeAttribute("règle", "nb");
    xmlWriter.writeTextElement("état", "e");
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file->close();
}

Xml_Dom::~Xml_Dom()
{

}
