#ifndef AUTOCELLDIM1_H
#define AUTOCELLDIM1_H
//#include "mainwindow.h"

//#include "Xml_Dom.h"
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
#include <QMap>
class AutoCellDim1 : public QWidget{
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
    static unsigned int dimension;
    static unsigned int dimensionHauteur;
public:
    explicit AutoCellDim1(QWidget* parent = nullptr);
private slots:
    void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum();
    void cellActivation(const QModelIndex& index);
    void simul();
    void simul_pap();
    void boucler();
    void etat_rnd();
    void symetric();
    void export_xml();
    void charger_xml();
    void stop_thread();
};



#endif // AUTOCELLDIM1_H
