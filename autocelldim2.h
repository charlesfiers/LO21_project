#ifndef AUTOCELLDIM2_H
#define AUTOCELLDIM2_H

//#include "mainwindow.h"
//#include "automate.h"
#include <QWidget>
//#include "Xml_Dom.h"

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


class AutoCellDim2 : public QWidget{
    Q_OBJECT
    static unsigned int dimension;
    static unsigned int dimensionHauteur;
    QLabel* min_alive_label;
    QLabel* max_alive_label;
    QLabel* min_born_label;
    QLabel* max_born_label;
    QLabel* pas_label;
    QSpinBox* min_alive;
    QSpinBox* max_alive;
    QSpinBox* min_born;
    QSpinBox* max_born;
    QSpinBox* pas;
    QHBoxLayout* bornes;
    QVBoxLayout* couche;
    QTableWidget* simulation;
    QPushButton* start;
    QPushButton* boucle;
    QPushButton* stop;
    QPushButton* rnd;
    QPushButton* xml_button3;
    QPushButton* xml_button4;
    bool stop_v;
public:
    explicit AutoCellDim2(QWidget* parent = nullptr);
private slots:
    void cellActivation(const QModelIndex& index);
    void simul();
    void boucler();
    void etat_rnd();
    void stop_thread();
    void export_xml();
    void charger_xml();
};

#endif // AUTOCELLDIM2_H
