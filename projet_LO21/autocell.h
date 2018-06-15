#ifndef AUTOCELL_H
#define AUTOCELL_H

#include "Xml_Dom.h"
#include "automate.h"
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
#include <QColor>

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

class AutoCellDim2 : public QWidget{
    Q_OBJECT
    static unsigned int dimension;
    static unsigned int dimensionHauteur;
    QLabel* min_alive_label;
    QLabel* max_alive_label;
    QLabel* min_born_label;
    QLabel* max_born_label;
    QLabel* pas_label;
    QLabel* color;
    QSpinBox* min_alive;
    QSpinBox* max_alive;
    QSpinBox* min_born;
    QSpinBox* max_born;
    QSpinBox* pas;
    QSpinBox* nb_color;
    QHBoxLayout* bornes;
    QVBoxLayout* couche;
    QTableWidget* simulation;
    QPushButton* start;
    QPushButton* boucle;
    QPushButton* stop;
    QPushButton* rnd;
    QColor tab_color[6];
    bool stop_v;
    QColor get_color(int,int);
public:
    explicit AutoCellDim2(QWidget* parent = nullptr);
private slots:
    void cellActivation(const QModelIndex& index);
    void simul();
    void boucler();
    void etat_rnd();
    void stop_thread();
};

#endif // AUTOCELL_H
