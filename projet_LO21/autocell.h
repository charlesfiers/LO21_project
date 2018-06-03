#ifndef AUTOCELL_H
#define AUTOCELL_H

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include "automate.h"

class AutoCell : public QWidget{
    Q_OBJECT
    QSpinBox* num; // numéro
    QLineEdit* numeroBit[8]; // un QLineEdit par bit
    QLabel* numl;
    QLabel* numeroBitl[8];
    QVBoxLayout* numc;
    QVBoxLayout* bitc[8];
    QHBoxLayout* numeroc;
    QIntValidator* zeroOneValidator;
    QVBoxLayout* couche;
    QTableWidget* depart;
    static unsigned int dimension;
    static unsigned int dimensionHauteur;
    QPushButton* simulation;
    QTableWidget* etats;
public:
    explicit AutoCell(QWidget* parent = nullptr);
private slots:
    void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum(const QString& s);
    void cellActivation(const QModelIndex& index);
    void faireSimulation();
};

#endif // AUTOCELL_H
