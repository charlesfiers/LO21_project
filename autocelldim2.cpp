#include "autocelldim2.h"
#include "automate.h"



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

    xml_button3 = new QPushButton("Exporter en XML Dim2");
    xml_button4 = new QPushButton("Charger XML Dim2");
    xml_button3->setFixedWidth(200);
    xml_button4->setFixedWidth(200);

    couche->addWidget(xml_button3);
    couche->addWidget(xml_button4);

    couche->addWidget(start);
    couche->addWidget(boucle);
    couche->addWidget(rnd);
    couche->addWidget(stop);

    connect(simulation,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));
    connect(start,SIGNAL(clicked(bool)),this,SLOT(simul()));
    connect(boucle,SIGNAL(clicked(bool)),this,SLOT(boucler()));
    connect(stop,SIGNAL(clicked(bool)),this,SLOT(stop_thread()));
    connect(rnd,SIGNAL(clicked(bool)),this,SLOT(etat_rnd()));
    connect(xml_button3,SIGNAL(clicked(bool)),this,SLOT(export_xml()));
    connect(xml_button4,SIGNAL(clicked(bool)),this,SLOT(charger_xml()));

    setLayout(bornes);
        setLayout(couche);
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

void AutoCellDim2::export_xml(){
    Etat e(dimensionHauteur,dimension);
    for(unsigned int i=0;i<dimensionHauteur;i++){


    for(int j=0; j<dimension; j++){
        if(simulation->item(j,i)->text()!=""){
            e.setCellule(i,j,true);
        }
    }
    }
    Xml_Dom doc;
    std::cout<<"aaaaaaaaaaaa"<<std::endl<<e<<std::endl;
    doc.ajouter_config(2000,e);
}

void AutoCellDim2::charger_xml(){
    Xml_Dom doc;
    QMap<std::string,std::string> s = doc.charger_config();
    //std::string ss = s.toStdString();
    //std::cout << s["regle"] << std::endl;
    //std::cout << s["etat"] << "||||" << s["etat"].size()<< std::endl;
    Etat e(dimensionHauteur,dimension);
    for(unsigned int i=0;i<dimensionHauteur;i++){

    e.setValue(s[std::string("etat")+std::to_string(i)]);
    }

    /* a implementer : e->QTable
    for(int j=0; j<dimension;j++){
        if(simulation->item(0,j)->text() == ""){
            e->item(0,j)->setBackgroundColor("white");
            e->item(0,j)->setText("");
        }else{
            e->item(0,j)->setBackgroundColor("black");
            e->item(0,j)->setText("_");
        }
    }*/
    std::cout<<"etat:"<<e;
}

