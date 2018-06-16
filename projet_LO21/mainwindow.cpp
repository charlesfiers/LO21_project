#include "mainwindow.h"
#include "autocell.h"
//#include "autocelldim2.h"

FenPrincipale::FenPrincipale() {
    QTabWidget *onglet = new QTabWidget;
    onglet->addTab(new AutoCellDim1(this), tr("Dim1"));
    onglet->addTab(new AutoCellDim2(this), tr("Dim2"));

    setCentralWidget( onglet );
    QTabWidget::TabPosition(0);
    setWindowTitle(tr("AutoCell"));

}
