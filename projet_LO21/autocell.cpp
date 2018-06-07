#include "autocell.h"
#include "automate.h"

unsigned int AutoCellDim1::dimension = 25;
unsigned int AutoCellDim1::dimensionHauteur = 1;

AutoCellDim1::AutoCellDim1(QWidget* parent) : QWidget(parent) {
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

void AutoCellDim1::cellActivation(const QModelIndex& index) {
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

void AutoCellDim1::simul(){
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

void AutoCellDim1::simul_pap(){
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

void AutoCellDim1::boucler(){
    int i = 0;
    while(stop_v != 1){
        simul();
        if(i!=255){
            i++;
        }else{
            i=0;
        }

        QThread::msleep((6-pas->value())*75);
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

void AutoCellDim1::etat_rnd(){
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

void AutoCellDim1::symetric(){
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

void AutoCellDim1::synchronizeNumToNumBit(int j) {
    std::string numbit = AutomateDim1::NumToNumBit(j);
    for (unsigned int i = 0; i < 8; i++)
        numeroBit[i]->setText(QString(numbit[i]));
}

void AutoCellDim1::synchronizeNumBitToNum() {
    for (unsigned int i = 0; i < 8; i++)
        if (numeroBit[i]->text()=="") return;
    std::string str;
    for (unsigned int i = 0; i < 8; i++)
        str += numeroBit[i]->text().toStdString();
    int i = AutomateDim1::NumBitToNum(str);
    num->setValue(i);
}

void AutoCellDim1::export_xml(){
    Etat e(1,dimension);
    for(int i=0; i<dimension; i++){
        if(depart->item(0,i)->text()!=""){
            e.setCellule(0,i,true);
        }
    }
    Xml_Dom doc;
    doc.ajouter_config(num->value(),e);
}

void AutoCellDim1::stop_thread(){
    stop_v = 1;
}

void AutoCellDim1::charger_xml(){
    Xml_Dom doc;
    QString s = doc.charger_config();
    std::string ss = s.toStdString();
    std::cout << ss << std::endl;
}

////////////////// AutoCellDim2 /////////////////////

unsigned int AutoCellDim2::dimension = 15;
unsigned int AutoCellDim2::dimensionHauteur = 15;

AutoCellDim2::AutoCellDim2(QWidget* parent) : QWidget(parent) {
    stop_v = 0;
    srand(time(NULL));

    min_alive_label = new QLabel("min neighboors to stay alive");
    min_alive = new QSpinBox(this);
    min_alive->setRange(0,8);
    min_alive->setValue(0);
    min_alive->setFixedWidth(30);

    max_alive_label = new QLabel("max neighboors to stay alive");
    max_alive = new QSpinBox(this);
    max_alive->setRange(0,8);
    max_alive->setValue(0);
    max_alive->setFixedWidth(30);

    min_born_label = new QLabel("min neighboors to become alive");
    min_born = new QSpinBox(this);
    min_born->setRange(0,8);
    min_born->setValue(0);
    min_born->setFixedWidth(30);

    max_born_label = new QLabel("max neighboors to become alive");
    max_born = new QSpinBox(this);
    max_born->setRange(0,8);
    max_born->setValue(0);
    max_born->setFixedWidth(30);

    pas_label = new QLabel("Vitesse");
    pas = new QSpinBox(this);
    pas->setFixedWidth(200);
    pas->setValue(0);
    pas->setRange(1,5);

    couche = new QVBoxLayout;
    couche->addWidget(min_alive_label);
    couche->addWidget(min_alive);
    couche->addWidget(max_alive_label);
    couche->addWidget(max_alive);
    couche->addWidget(min_born_label);
    couche->addWidget(min_born);
    couche->addWidget(max_born_label);
    couche->addWidget(max_born);
    couche->addWidget(pas_label);
    couche->addWidget(pas);

    bornes = new QHBoxLayout;
    bornes->addLayout(couche);

    simulation = new QTableWidget(dimensionHauteur,dimension,this);
    unsigned int taille = 25;
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
    bornes->addWidget(simulation);

    start = new QPushButton("Simulation pas à pas");
    start->setFixedWidth(200);
    boucle = new QPushButton("Boucler simulation");
    boucle->setFixedWidth(200);
    rnd = new QPushButton("Etat aléatoire");
    rnd->setFixedWidth(200);
    stop = new QPushButton("Stoper simulation");
    stop->setFixedWidth(200);

    couche->addWidget(start);
    couche->addWidget(boucle);
    couche->addWidget(rnd);
    couche->addWidget(stop);

    connect(simulation,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));
    connect(start,SIGNAL(clicked(bool)),this,SLOT(simul()));
    connect(boucle,SIGNAL(clicked(bool)),this,SLOT(boucler()));
    connect(stop,SIGNAL(clicked(bool)),this,SLOT(stop_thread()));
    connect(rnd,SIGNAL(clicked(bool)),this,SLOT(etat_rnd()));

    setLayout(bornes);
}

void AutoCellDim2::cellActivation(const QModelIndex& index) {
    if (simulation->item(index.row(),index.column())->text()=="") {
        simulation->item(index.row(),index.column())->setText("_");
        simulation->item(index.row(),index.column())->setBackgroundColor("black");
        simulation->item(index.row(),index.column())->setTextColor("black");
    } else { // activée
        simulation->item(index.row(),index.column())->setText("");
        simulation->item(index.row(),index.column())->setBackgroundColor("white");
        simulation->item(index.row(),index.column())->setTextColor("white");
    }
}

void AutoCellDim2::simul(){
    const AutomateDim2& a = AutomateManager::getAutomateManager().getAutomateDim2(min_alive->value(),max_alive->value(),min_born->value(),max_born->value());
    Etat e(dimensionHauteur,dimension);
    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimensionHauteur;j++){
            if(simulation->item(j,i)->text()!=""){
                e.setCellule(j,i,true);
            }
        }
    }
    Simulateur s(a,e);
    s.next();
    for(int j=0; j<dimensionHauteur; j++){
        for(int i=0; i<dimension; i++){
            if(s.dernier().getCellule(j,i)){
                simulation->item(j,i)->setBackgroundColor("black");
                simulation->item(j,i)->setText("_");
            }else{
                simulation->item(j,i)->setBackgroundColor("white");
                simulation->item(j,i)->setText("");
            }
        }
    }
    std::cout << e << std::endl;
    std::cout << "======================" << std::endl;
}

void AutoCellDim2::boucler(){
    while(stop_v != 1){
        simul();
        QThread::msleep((6-pas->value())*75);
        QCoreApplication::processEvents();
    }
    stop_v = 0;
}

void AutoCellDim2::stop_thread(){
    stop_v = 1;
}

void AutoCellDim2::etat_rnd(){
    int r1 = rand();
    int r2;
    for(int i=0; i< dimension; i++){
        for(int j=0; j<dimensionHauteur;j++){
            r2 = rand();
            if(r2 > r1){
                simulation->item(j,i)->setText("_");
                simulation->item(j,i)->setBackgroundColor("black");
            }else{
                simulation->item(j,i)->setText("");
                simulation->item(j,i)->setBackgroundColor("white");
            }
        }
    }
}
