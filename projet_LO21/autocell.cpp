#include "autocell.h"
#include "automate.h"

unsigned int AutoCell::dimension = 25;
unsigned int AutoCell::dimensionHauteur = 8;

AutoCell::AutoCell(QWidget* parent) : QWidget(parent) {
    srand(time(NULL));
    symetrie = new QPushButton("Symetrie");
    symetrie->setFixedWidth(200);
    num = new QSpinBox(this);
    num->setRange(0,255);
    num->setValue(0);
    num->setFixedWidth(200);
    numl = new QLabel("Numéro");
    numc = new QVBoxLayout;

    numc->addWidget(numl);
    numc->addWidget(num);
    numc->addWidget(symetrie);
    numeroc = new QHBoxLayout;
    numeroc->addLayout(numc);

    zeroOneValidator = new QIntValidator(this);
    zeroOneValidator->setRange(0,1);

    for (unsigned int i = 0; i < 8; i++) {
        numeroBit[i] = new QLineEdit(this);
        numeroBit[i]->setFixedWidth(20);
        numeroBit[i]->setMaxLength(1);
        numeroBit[i]->setText("0");
        numeroBit[i]->setValidator(zeroOneValidator);
        numeroBitl[i] = new QLabel;
        bitc[i] = new QVBoxLayout;
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

    couche = new QVBoxLayout;
    couche->addLayout(numeroc);
    depart = new QTableWidget(1,dimension,this);

    unsigned int taille = 25;
    depart->setFixedSize(dimension*taille,taille);
    depart->horizontalHeader()->setVisible(false);
    depart->verticalHeader()->setVisible(false);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for (unsigned int i = 0; i < dimension; i++) {
        depart->setColumnWidth(i,taille);
        depart->setItem(0,i,new QTableWidgetItem(""));
    }

    couche->addWidget(depart);
    start = new QPushButton("Lancer simulation");
    start->setFixedWidth(200);
    couche->addWidget(start);

    bouclage = new QVBoxLayout;

    boucle = new QPushButton("Boucler la simulation");
    boucle->setFixedWidth(200);
    stop = new QPushButton("Stoper la simulation");
    stop->setFixedWidth(200);
    stop_v = 0;

    pasl = new QLabel("Vitesse");
    pas = new QSpinBox(this);
    pas->setFixedWidth(200);
    pas->setValue(0);
    pas->setRange(1,5);
    couche->addLayout(bouclage);
    pap = new QPushButton("Pas à pas");
    pap->setFixedWidth(200);
    rnd = new QPushButton("Etat initial aléatoire");
    rnd->setFixedWidth(200);

    bouclage->addWidget(boucle);
    bouclage->addWidget(stop);
    bouclage->addWidget(pasl);
    bouclage->addWidget(pas);
    bouclage->addWidget(pap);
    bouclage->addWidget(rnd);

    simulation = new QTableWidget(dimensionHauteur,dimension,this);
    couche->addWidget(simulation);
    simulation->setFixedSize(dimension*taille,dimensionHauteur*taille);
    simulation->horizontalHeader()->setVisible(false);
    simulation->verticalHeader()->setVisible(false);
    simulation->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    simulation->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimensionHauteur; j++){
            simulation->setColumnWidth(i,taille);
            simulation->setRowHeight(j,taille);
            simulation->setItem(j,i,new QTableWidgetItem(""));
        }
    }
    xml_button = new QPushButton("Exporter en XML");
    xml_button2 = new QPushButton("Charger XML");
    xml_button->setFixedWidth(200);
    xml_button2->setFixedWidth(200);
    couche->addWidget(xml_button);
    couche->addWidget(xml_button2);
    couche->addWidget(simulation);
    setLayout(couche);

    connect(num,SIGNAL(valueChanged(int)),this,SLOT(synchronizeNumToNumBit(int)));

    for(int i=0; i<8; i++)
        connect(numeroBit[i],SIGNAL(textChanged(QString)),this,SLOT(synchronizeNumBitToNum()));

    connect(depart,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));
    connect(start,SIGNAL(clicked(bool)),this,SLOT(simul()));
    connect(pap,SIGNAL(clicked(bool)),this,SLOT(simul_pap()));
    connect(boucle,SIGNAL(clicked(bool)),this,SLOT(boucler()));
    connect(stop,SIGNAL(clicked(bool)),this,SLOT(stop_thread()));
    connect(rnd,SIGNAL(clicked(bool)),this,SLOT(etat_rnd()));
    connect(symetrie,SIGNAL(clicked(bool)),this,SLOT(symetric()));
    connect(xml_button,SIGNAL(clicked(bool)),this,SLOT(export_xml()));
    connect(xml_button2,SIGNAL(clicked(bool)),this,SLOT(charger_xml()));
}

void AutoCell::cellActivation(const QModelIndex& index) {
    if (depart->item(0,index.column())->text()=="") { // désactivée
        depart->item(0,index.column())->setText("_");
        depart->item(0,index.column())->setBackgroundColor("black");
        depart->item(0,index.column())->setTextColor("black");
    } else { // activée
        depart->item(0,index.column())->setText("");
        depart->item(0,index.column())->setBackgroundColor("white");
        depart->item(0,index.column())->setTextColor("white");
    }
}

void AutoCell::simul(){
    const AutomateDim1& a = AutomateManager::getAutomateManager().getAutomateDim1(num->value());
    Etat e(1,dimension);
    for(int i=0; i<dimension; i++){
        if(depart->item(0,i)->text()!=""){
            e.setCellule(0,i,true);
        }
    }
    Simulateur s(a,e);
    for(int j=0; j<dimensionHauteur; j++){
        s.next();
        for(int i=0; i<dimension; i++){
            if(s.dernier().getCellule(0,i)){
                simulation->item(j,i)->setBackgroundColor("black");
                simulation->item(j,i)->setText("_");
            }else{
                simulation->item(j,i)->setBackgroundColor("white");
                simulation->item(j,i)->setText("");
            }
        }
    }
}

void AutoCell::simul_pap(){
    const AutomateDim1& a = AutomateManager::getAutomateManager().getAutomateDim1(num->value());
    Etat e(1,dimension);
    for(int i=0; i<dimension; i++){
        if(depart->item(0,i)->text()!=""){
            e.setCellule(0,i,true);
        }
    }
    Simulateur s(a,e);
    for(int j=0; j<dimensionHauteur; j++){
        s.next();
        for(int i=0; i<dimension; i++){
            if(s.dernier().getCellule(0,i)){
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
    int i = 0;
    while(stop_v != 1){
        simul();
        num->setValue(i);
        if(i!=255){
            i++;
        }else{
            i=0;
        }

        QThread::msleep(pas->value()*75);
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
    stop_v = 0;
}

void AutoCell::etat_rnd(){
    int r1 = rand();
    int r2;
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

void AutoCell::synchronizeNumToNumBit(int j) {
    std::string numbit = AutomateDim1::NumToNumBit(j);
    for (unsigned int i = 0; i < 8; i++)
        numeroBit[i]->setText(QString(numbit[i]));
}

void AutoCell::synchronizeNumBitToNum() {
    for (unsigned int i = 0; i < 8; i++)
        if (numeroBit[i]->text()=="") return;
    std::string str;
    for (unsigned int i = 0; i < 8; i++)
        str += numeroBit[i]->text().toStdString();
    int i = AutomateDim1::NumBitToNum(str);
    num->setValue(i);
}

void AutoCell::export_xml(){
    Etat e(1,dimension);
    for(int i=0; i<dimension; i++){
        if(depart->item(0,i)->text()!=""){
            e.setCellule(0,i,true);
        }
    }
    Xml_Dom doc;
    doc.ajouter_config(num->value(),e);
}

void AutoCell::stop_thread(){
    stop_v = 1;
}

void AutoCell::charger_xml(){
    Xml_Dom doc;
    QString s = doc.charger_config();
    std::string ss = s.toStdString();
    std::cout << ss << std::endl;
}
