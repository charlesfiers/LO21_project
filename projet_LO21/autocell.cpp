#include "autocell.h"
#include "automate.h"

int AutoCell::dimension=25;
int AutoCell::dimension2=15;

AutoCell::AutoCell(QWidget* parent):QWidget(parent) {
    symetrie = new QPushButton("Symétrie");
    num = new QSpinBox(this);
    num->setRange(0,255);
    num->setValue(0);
    numl = new QLabel("Numéro");
    numc = new QVBoxLayout;
    numc->addWidget(numl);
    numc->addWidget(num);
    numc->addWidget(symetrie);

    numeroc = new QHBoxLayout;
    numeroc->addLayout(numc);

    zeroOneValidator = new QIntValidator(this);
    zeroOneValidator->setRange(0,1);

    for(int i=0; i<8; i++){
        numeroBit[i] = new QLineEdit(this);
        numeroBit[i]->setFixedWidth(20);
        numeroBit[i]->setMaxLength(1);
        numeroBit[i]->setText("0");
        numeroBitl[i] = new QLabel;
        bitc[i] = new QVBoxLayout;
        bitc[i]->addWidget(numeroBit[i]);
        bitc[i]->addWidget(numeroBitl[i]);
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

    couche = new QVBoxLayout;
    couche->addLayout(numeroc);
    depart = new QTableWidget(1,dimension,this);

    unsigned int taille=25;
    depart->setFixedSize(dimension*taille,taille);
    depart->horizontalHeader()->setVisible(false);
    depart->verticalHeader()->setVisible(false);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for(int i=0; i<dimension; i++){
        depart->setColumnWidth(i,taille);
        depart->setItem(0,i,new QTableWidgetItem(""));
    }

    couche->addWidget(depart);
    start = new QPushButton("Lancer simulation");
    couche->addWidget(start);

    bouclage = new QVBoxLayout;

    boucle = new QPushButton("Boucler la simulation");

    pasl = new QLabel("pas");
    pas = new QSpinBox(this);
    pas->setValue(0);
    pas->setRange(1,5);
    couche->addLayout(bouclage);
    pap = new QPushButton("Pas à pas");
    rnd = new QPushButton("Etat initial aléatoire");

    bouclage->addWidget(boucle);
    bouclage->addWidget(pasl);
    bouclage->addWidget(pas);
    bouclage->addWidget(pap);
    bouclage->addWidget(rnd);

    simulation = new QTableWidget(dimension2,dimension,this);
    couche->addWidget(simulation);
    simulation->setFixedSize(dimension*taille,dimension2*taille);
    simulation->horizontalHeader()->setVisible(false);
    simulation->verticalHeader()->setVisible(false);
    simulation->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    simulation->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension2; j++){
            simulation->setColumnWidth(i,taille);
            simulation->setRowHeight(j,taille);
            simulation->setItem(j,i,new QTableWidgetItem(""));
        }
    }
    couche->addWidget(simulation);
    setLayout(couche);

    connect(num,SIGNAL(valueChanged(int)),this,SLOT(synchronizeNumToNumBit(int)));

    for(int i=0; i<8; i++)
        connect(numeroBit[i],SIGNAL(textChanged(QString)),this,SLOT(synchronizeNumBitToNum()));

    connect(depart,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));
    connect(start,SIGNAL(clicked(bool)),this,SLOT(simul()));
    connect(pap,SIGNAL(clicked(bool)),this,SLOT(simul2()));
    connect(boucle,SIGNAL(clicked(bool)),this,SLOT(boucler()));
    connect(rnd,SIGNAL(clicked(bool)),this,SLOT(etat_rnd()));
    connect(symetrie,SIGNAL(clicked(bool)),this,SLOT(symetric()));

}

void AutoCell::synchronizeNumToNumBit(int j){
    std::string numbit = NumToNumBit(j);
    for(int i=0; i<8; i++)
        numeroBit[i]->setText(QString(numbit[i]));
}

void AutoCell::synchronizeNumBitToNum(){
    for(int i=0; i<8; i++)
        if(numeroBit[i]->text()=="") return;
    std::string str;
    for(int i=0; i<8; i++)
        str += numeroBit[i]->text().toStdString();
    int i = NumBitToNum(str);
    num->setValue(i);
}

void AutoCell::cellActivation(const QModelIndex &index){
    if(depart->item(0,index.column())->text()==""){
        depart->item(0,index.column())->setText("_");
        depart->item(0,index.column())->setBackgroundColor("black");
        depart->item(0,index.column())->setTextColor("black");
    }else{
        depart->item(0,index.column())->setText("");
        depart->item(0,index.column())->setBackgroundColor("white");
        depart->item(0,index.column())->setTextColor("white");
    }
}

void AutoCell::simul(){
    const Automate& a = AutomateManager::getAutomateManager().getAutomate(num->value());
    Etat e(dimension);
    for(int i=0; i<dimension; i++){
        if(depart->item(0,i)->text()!=""){
            e.setCellule(i,true);
        }
    }
    Simulateur s(a,e);
    for(int j=0; j<dimension2; j++){
        s.next();
        for(int i=0; i<dimension; i++){
            if(s.dernier().getCellule(i)){
                simulation->item(j,i)->setBackgroundColor("black");
                simulation->item(j,i)->setText("_");
            }else{
                simulation->item(j,i)->setBackgroundColor("white");
                simulation->item(j,i)->setText("");
            }
        }
    }
}

void AutoCell::simul2(){
    const Automate& a = AutomateManager::getAutomateManager().getAutomate(num->value());
    Etat e(dimension);
    for(int i=0; i<dimension; i++){
        if(depart->item(0,i)->text()!=""){
            e.setCellule(i,true);
        }
    }
    Simulateur s(a,e);
    for(int j=0; j<dimension2; j++){
        s.next();
        for(int i=0; i<dimension; i++){
            if(s.dernier().getCellule(i)){
                simulation->item(j,i)->setBackgroundColor("black");
            }else{
                simulation->item(j,i)->setBackgroundColor("white");
            }
        }
    }
    num->setValue(num->value()+1);
    if(num->value()>=255) num->setValue(0);
}


void AutoCell::boucler(){
    for(int i=1; i<255; i++){
        //num->setValue(i);
        simul();
        QThread::usleep(pas->value()*300);
        for(int j=0; j<dimension;j++){
            if(simulation->item(0,j)->text() == ""){
                depart->item(0,j)->setBackgroundColor("white");
                depart->item(0,j)->setText("");
            }else{
                depart->item(0,j)->setBackgroundColor("black");
                depart->item(0,j)->setText("_");
            }
        }
        QCoreApplication::processEvents();
    }
}

void AutoCell::etat_rnd(){
    srand(time(NULL));
    int r1 = rand();
    int r2;
    QModelIndex q;
    for(int i=0; i< dimension; i++){
        r2 = rand();
        if(r2 > r1){
            depart->item(0,i)->setText("_");
            depart->item(0,i)->setBackgroundColor("black");
        }else{
            depart->item(0,i)->setText("");
            depart->item(0,i)->setBackgroundColor("white");
        }
    }
}

void AutoCell::symetric(){
    for(int i=0; i<dimension/2;i++){
        if(depart->item(0,i)->text()=="_"){
            depart->item(0,dimension-i-1)->setText("_");
            depart->item(0,dimension-i-1)->setBackgroundColor("black");
        }else{
            depart->item(0,dimension-i-1)->setText("");
            depart->item(0,dimension-i-1)->setBackgroundColor("white");
        }
    }
}
