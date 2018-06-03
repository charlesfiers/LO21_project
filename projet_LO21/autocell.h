#ifndef AUTOCELL_H
#define AUTOCELL_H

#include "Xml_Dom.h"
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <ctime>
#include <QCoreApplication>
#include <stdlib.h>
#include <QStandardItemModel>
#include <QThread>
#include <QComboBox>
#include <QRadioButton>

class AutoCell : public QWidget{
    Q_OBJECT
    QSpinBox* num; // numéro
    QLabel* numl;
    QLabel* pasl;
    QLineEdit* numeroBit[8]; // un QLineEdit par bit QLabel* numl;
    QLabel* numeroBitl[8];
    QVBoxLayout* numc;
    QSpinBox* pas;
    QVBoxLayout* bitc[8];
    QHBoxLayout* numeroc;
    QIntValidator* zeroOneValidator;
    QTableWidget* depart;
    QVBoxLayout* couche;
    QVBoxLayout* bouclage;
    static int dimension;
    static int dimension2;
    QTableWidget* simulation;
    QPushButton* start;
    QPushButton* boucle;
    QPushButton* stop;
    QPushButton* pap;
    QPushButton* rnd;
    QPushButton* symetrie;
    QPushButton* xml_button;
    QPushButton* xml_button2;

    bool stop_v;
public:
    explicit AutoCell(QWidget* parent = nullptr);
private slots:
    void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum();
    void cellActivation(const QModelIndex& index);
    void simul();
    void simul2();
    void boucler();
    void etat_rnd();
    void symetric();
    void export_xml();
    void charger_xml();
    void stop_thread();
};

#endif // AUTOCELL_H
