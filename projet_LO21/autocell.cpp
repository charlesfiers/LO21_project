#include "autocell.h"

unsigned int AutoCell::dimension=25;

AutoCell::AutoCell(QWidget* parent):QWidget(parent){
    num= new QSpinBox(this);
    num->setRange(0,255);
    num->setValue(0);
    numl=new QLabel("Numéro");
    numc=new QVBoxLayout;
    numc->addWidget(numl);
    numc->addWidget(num);

    numeroc=new QHBoxLayout;
    numeroc->addLayout(numc);

    zeroOneValidator=new QIntValidator(this);
    zeroOneValidator->setRange(0,1);

    for(unsigned int i=0; i<8; i++){
        numeroBit[i]=new QLineEdit(this);
        numeroBit[i]->setFixedWidth(20);
        numeroBit[i]->setMaxLength(1);
        numeroBit[i]->setText("0");
        numeroBit[i]->setValidator(zeroOneValidator);
        numeroBitl[i]=new QLabel;
        bitc[i]=new QVBoxLayout;
        bitc[i]->addWidget(numeroBitl[i]);
        bitc[i]->addWidget(numeroBit[i]);
        numeroc->addLayout(bitc[i]);
    }
    numeroBitl[0]->setText("111");
    numeroBitl[1]->setText("110");
    numeroBitl[2]->setText("101");
    numeroBitl[3]->setText("100");
    numeroBitl[4]->setText("011");
    numeroBitl[5]->setText("010");
    numeroBitl[6]->setText("001");
    numeroBitl[7]->setText("000");

    couche=new QVBoxLayout;
    couche->addLayout(numeroc);
    depart=new QTableWidget(1,dimension,this);
    couche->addWidget(depart);
    setLayout(couche);

    unsigned int taille=25;
    depart->setFixedSize(dimension*taille,taille);
    depart->horizontalHeader()->setVisible(false);
    depart->verticalHeader()->setVisible(false);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for(unsigned int i=0; i<dimension; i++){
        depart->setColumnWidth(i,taille);
        depart->setItem(0,i,new QTableWidgetItem(""));
    }
    connect(depart,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(cellActivation(QModelIndex)));

    connect(num,SIGNAL(valueChanged(int)),
            this,SLOT(synchronizeNumToNumBit(int)));
    for(unsigned int i=0; i<8; i++)
        connect(numeroBit[i],SIGNAL(textChanged(QString)),
                this, SLOT(synchronizeNumBitToNum(QString)));

    simulation=new QPushButton("Simulation");
    couche->addWidget(simulation);
    connect(simulation,SIGNAL(clicked()),
            this, SLOT(faireSimulation()));
    etats=new QTableWidget(dimension,dimension,this);
    etats->setFixedSize(dimension*taille,dimension*taille);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // non éditable
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(unsigned int i=0; i<dimension; i++){
        etats->setColumnWidth(i, taille);
        etats->setRowHeight(i, taille);
        for(unsigned int j=0; j<dimension; j++){
            etats->setItem(j,i,new QTableWidgetItem(""));
        }
    }
    couche->addWidget(etats);
}

void AutoCell::faireSimulation(){
    Etat e(dimension);
    for(unsigned int i=0; i<dimension; i++)
        if (depart->item(0,i)->text()!="") e.setCellule(i,true);
    const Automate& A=
 AutomateManager::getAutomateManager().getAutomate(num->value());
    Simulateur S(A,e);
    for(unsigned int i=0; i<dimension; i++){
        S.next();
        const Etat& d=S.dernier();
        for(unsigned int j=0; j<dimension; j++){
            if (d.getCellule(j)){
                etats->item(i,j)->setBackgroundColor("black");
            }else{
                etats->item(i,j)->setBackgroundColor("white");

            }
        }
    }
}

void AutoCell::cellActivation(const QModelIndex& index){
    if (depart->item(0,index.column())->text()==""){ // désactivée
        depart->item(0,index.column())->setText("_");
        depart->item(0,index.column())->setBackgroundColor("black");
        depart->item(0,index.column())->setTextColor("black");
    }else{ // activée
        depart->item(0,index.column())->setText("");
        depart->item(0,index.column())->setBackgroundColor("white");
        depart->item(0,index.column())->setTextColor("white");
    }
}


void AutoCell::synchronizeNumToNumBit(int j){
    std::string numbit=NumToNumBit(j);
    for(unsigned int i=0; i<8; i++)
        numeroBit[i]->setText(QString(numbit[i]));
}
void AutoCell::synchronizeNumBitToNum(const QString& s){
    for(unsigned int i=0; i<8; i++)
        if (numeroBit[i]->text()=="") return;
    std::string str;
    for(unsigned int i=0; i<8; i++)
        str+=numeroBit[i]->text().toStdString();
    int i=NumBitToNum(str);
    num->setValue(i);
}

