#ifndef AutoCellDim1_H
#define AutoCellDim1_H

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

template <class T> class Prototype : public QWidget {
public:
    virtual ~Prototype(){}
    virtual T* Clone() const = 0;
};

class AutoCell : public Prototype<AutoCell> {
public:
    //void save();
    //void load();
};

class AutoCellDim1 : public AutoCell {
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
    explicit AutoCellDim1(/*QWidget* parent = nullptr*/);
    AutoCell* Clone() const;
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

class AutoCellFactory {
    static std::map<std::string,AutoCell*> m_map;
public:
    //Fonction qui associe clé <=> prototype
    static void Register(const std::string& key, AutoCell* obj);
    //Celle qui va créer les objets
    AutoCell* Create(const std::string& key) const;
};

#endif // AutoCellDim1_H
