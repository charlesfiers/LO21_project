#include "Xml_Dom.h"
#include <iostream>
using namespace std;

Xml_Dom::Xml_Dom() : QWidget()
{

    /*dom_element = doc->documentElement();
    noeud = dom_element.firstChild();
    while(!noeud.isNull())
    {
        if(!dom_element.isNull())
            QMessageBox::information(this, "Nom de la balise", "Le nom de la balise est " + dom_element.tagName());
                noeud = noeud.nextSibling();
    }*/
}

QMap<std::string,std::string> Xml_Dom::charger_config(){
    QFile *file = new QFile("./doc.xml");
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(file);
    QMap<std::string,std::string> res;
    xmlReader.readNext();
            //Reading from the file
            while (!xmlReader.isEndDocument())
            {
                if (xmlReader.isStartElement())
                {
                    QString name = xmlReader.name().toString();
                    if (name == "regle")
                    {
                        //std::cout<<xmlReader.readElementText().toUtf8().constData()<<std::endl;
                        res["regle"] = xmlReader.readElementText().toUtf8().constData();
                    }
                    else if (name.mid(0,4) == "etat")
                    {
                        //std::cout<<xmlReader.readElementText().toUtf8().constData()<<std::endl;
                        res[name.toStdString().c_str()]= xmlReader.readElementText().toStdString();
                        //std::cout<<"Dddd"<<name.toStdString();
                        //std::cout<<"lklklklklk"<<name.toStdString().c_str();
                        //std::cout<<xmlReader.readElementText().toStdString()<<"dddddddd";
                        //std::cout<<res[name.toStdString().c_str()].size()<<"zzzzzzzzzzzzz";
                    }
                    //else {std::cout<<xmlReader.readElementText().toStdString()<<"dddddddd";}
                }
                xmlReader.readNext();
}



        file->close();
        delete file;
        return res;
}

void Xml_Dom::ajouter_config(int nb, Etat e){

    QFile* file = new QFile("./doc.xml");

    if(!file->open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
        return;
    }
    //Etat e2(2,3);
    QXmlStreamWriter xmlWriter(file);
    std::cout << "in ajouter-config, e: " << e <<std::endl;

    std::cout << "in ajouter-config, nb: " << nb <<std::endl;
    std::ostringstream stream;
    stream << e;
    std::string str =  stream.str();
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("config");
    xmlWriter.writeTextElement("regle", std::to_string(nb).c_str());

    for(unsigned int i=0;i<e.getHauteur();i++)
    {
        std::string s=std::string("etat")+std::to_string(i);
        xmlWriter.writeTextElement(s.c_str(),str.substr(0, str.find('\n')).c_str());
        str = str.substr(str.find('\n')+1);
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file->close();
    delete file;
}

QMap<std::string,std::string> Xml_Dom::charger_config_dim2(){
    QFile *file = new QFile("/Users/Vincent/Desktop/doc_dim2.xml");
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(file);
    QMap<std::string,std::string> res;
    xmlReader.readNext();
            //Reading from the file
            while (!xmlReader.isEndDocument())
            {
                if (xmlReader.isStartElement())
                {
                    QString name = xmlReader.name().toString();
                    if (name == "regle")
                    {
                        //std::cout<<xmlReader.readElementText().toUtf8().constData()<<std::endl;
                        res["regle"] = xmlReader.readElementText().toUtf8().constData();
                    }
                    else if (name == "minv")
                    {
                        //std::cout<<xmlReader.readElementText().toUtf8().constData()<<std::endl;
                        res["minv"] = xmlReader.readElementText().toUtf8().constData();
                    }
                    else if (name == "maxv")
                    {
                        //std::cout<<xmlReader.readElementText().toUtf8().constData()<<std::endl;
                        res["maxv"] = xmlReader.readElementText().toUtf8().constData();
                    }
                    else if (name == "minm")
                    {
                        //std::cout<<xmlReader.readElementText().toUtf8().constData()<<std::endl;
                        res["minm"] = xmlReader.readElementText().toUtf8().constData();
                    }
                    else if (name == "maxm")
                    {
                        //std::cout<<xmlReader.readElementText().toUtf8().constData()<<std::endl;
                        res["maxm"] = xmlReader.readElementText().toUtf8().constData();
                    }
                    else if (name.mid(0,4) == "etat")
                    {
                        //std::cout<<xmlReader.readElementText().toUtf8().constData()<<std::endl;
                        res[name.toStdString().c_str()]= xmlReader.readElementText().toStdString();
                        //std::cout<<"Dddd"<<name.toStdString();
                        //std::cout<<"lklklklklk"<<name.toStdString().c_str();
                        //std::cout<<xmlReader.readElementText().toStdString()<<"dddddddd";
                        //std::cout<<res[name.toStdString().c_str()].size()<<"zzzzzzzzzzzzz";
                    }
                    //else {std::cout<<xmlReader.readElementText().toStdString()<<"dddddddd";}
                }
                xmlReader.readNext();
}



        file->close();
        delete file;
        return res;
}


void Xml_Dom::ajouter_config_dim2(unsigned int minv,unsigned int minm,unsigned int maxv,unsigned int maxm, int nb, Etat e){

    QFile* file = new QFile("/Users/Vincent/Desktop/doc_dim2.xml");

    if(!file->open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
        return;
    }
    //Etat e2(2,3);
    QXmlStreamWriter xmlWriter(file);
    std::cout << "in ajouter-config, e: " << e <<std::endl;

    std::cout << "in ajouter-config, nb: " << nb <<std::endl;
    std::ostringstream stream;
    stream << e;
    std::string str =  stream.str();
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("config");
    xmlWriter.writeTextElement("regle", std::to_string(nb).c_str());
    xmlWriter.writeTextElement("minv", std::to_string(minv).c_str());
    xmlWriter.writeTextElement("minm", std::to_string(minm).c_str());
    xmlWriter.writeTextElement("maxv", std::to_string(maxv).c_str());
    xmlWriter.writeTextElement("maxm", std::to_string(maxm).c_str());

    for(unsigned int i=0;i<e.getHauteur();i++)
    {
        std::string s=std::string("etat")+std::to_string(i);
        xmlWriter.writeTextElement(s.c_str(),str.substr(0, str.find('\n')).c_str());
        str = str.substr(str.find('\n')+1);
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file->close();
    delete file;
}

Xml_Dom::~Xml_Dom()
{
    //file->close();
}
