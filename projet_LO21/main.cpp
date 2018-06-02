#include <QApplication>
#include <iostream>
#include <QtXml>
#include <QtGui>
#include "xmldoc.h"


int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    QDomDocument* dom = new QDomDocument("doc1");
    QFile doc_xml("doc1.xml");
    if(!doc_xml.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "erreur open read" << std::endl;
        doc_xml.close();
        return 1;
    }
    QString error;
    int i,j;
    if(!dom->setContent(&doc_xml,false,&error,&i,&j))
    {
        std::cout << error.toStdString() << i << j << std::endl;
        doc_xml.close();
        return 2;
    }
    QDomElement docElem = dom->documentElement();
    QDomElement write_elem = dom->createElement("information");
    write_elem.setAttribute("id", 2);
    write_elem.setAttribute("value", "L'inflation arrive en France");
    docElem.appendChild(write_elem);
    QString write_doc = dom->toString();

    QTextStream stream(&doc_xml);

    stream << write_doc;
    doc_xml.close();
    return 0;
}
