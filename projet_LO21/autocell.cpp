#include "autocell.h"
//#include "automate.h"
#include "Xml_Dom.h"

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
    simulation->setVisible(false);
    xml_button = new QPushButton("Exporter en XML");
    xml_button2 = new QPushButton("Charger XML");
    xml_button->setFixedWidth(200);
    xml_button2->setFixedWidth(200);
    couche->addWidget(xml_button);
    couche->addWidget(xml_button2);
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
    std::cout<<"aaaaaaaaaaaa"<<std::endl<<e<<std::endl;
    doc.ajouter_config(num->value(),e);
}

void AutoCellDim1::stop_thread(){
    stop_v = 1;
}

void AutoCellDim1::charger_xml(){
    Xml_Dom doc;
    QMap<std::string,std::string> s = doc.charger_config();
    //std::string ss = s.toStdString();
    //std::cout << s["regle"] << std::endl;
    //std::cout << s["etat"] << "||||" << s["etat"].size()<< std::endl;


    Etat e(1,s["etat0"].size());
    e.setValue(s["etat0"]);

    /*s.remove("regle");
    for(QMap<std::string,std::string>::Iterator i=s.begin(); i!=s.end();++i)
    {
        Etat e(1,s[i.key().size()]);
        e.setValue(s[i.key().size]);
        std::cout << i.key() << "," << i.value().size() << '\n';
    }*/
    //std::cout<<"gggggggg<s[].size();
    //std::cout<<"ssssssssss"<<e.getCellule(1,1);
    //std::cout<<"kokoko";
    //const AutomateDim1& a = AutomateManager::getAutomateManager().getAutomateDim1(num->value());


    //Simulateur s(a,e);
    //std::cout<<e.getCellule(0,1);
        for(int i=0; i<dimension; i++){
            if(e.getCellule(0,i)){
                simulation->item(0,i)->setBackgroundColor("black");
                simulation->item(0,i)->setText("_");
            }else{
                simulation->item(0,i)->setBackgroundColor("white");
                simulation->item(0,i)->setText("");
            }
        }
        num->setValue(std::stoi(s["regle"]));
        //std::cout<<std::stoi(s["regle"])<<std::endl;
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
    //std::cout<<"etat:"<<e;
}

////////////////// AutoCellDim2 /////////////////////

////////////////// AutoCellDim2 /////////////////////


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

    color = new QLabel("Nombre de couleurs");
    nb_color = new QSpinBox(this);
    nb_color->setFixedWidth(30);
    nb_color->setValue(1);
    nb_color->setRange(1,6);

    nb_cellules = new QLabel("Nombre de cellules");
    slider = new QSlider(Qt::Horizontal,this);
    slider->setMinimum(10);
    slider->setMaximum(40);

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
    couche->addWidget(nb_cellules);
    couche->addWidget(slider);
    couche->addWidget(color);
    couche->addWidget(nb_color);

    bornes = new QHBoxLayout;
    bornes->addLayout(couche);
    slider->setValue(15);
    dimension = slider->value();
    dimensionHauteur = slider->value();

    simulation = new QTableWidget(dimensionHauteur,dimension,this);
    unsigned int taille = 25;
    simulation->setFixedSize(15*taille,15*taille);
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

    lifegame_button = new QPushButton("Jeu de la vie");
    lifegame_button->setFixedWidth(200);
    start = new QPushButton("Simulation pas à pas");
    start->setFixedWidth(200);
    boucle = new QPushButton("Boucler simulation");
    boucle->setFixedWidth(200);
    rnd = new QPushButton("Etat aléatoire");
    rnd->setFixedWidth(200);
    stop = new QPushButton("Stoper simulation");
    stop->setFixedWidth(200);
    reset_button = new QPushButton("Reset");
    reset_button->setFixedWidth(200);

    xml_button3 = new QPushButton("Exporter en XML Dim2");
    xml_button4 = new QPushButton("Charger XML Dim2");
    xml_button3->setFixedWidth(200);
    xml_button4->setFixedWidth(200);

    couche->addWidget(xml_button3);
    couche->addWidget(xml_button4);

    couche->addWidget(start);
    couche->addWidget(boucle);
    couche->addWidget(lifegame_button);
    couche->addWidget(rnd);
    couche->addWidget(stop);
    couche->addWidget(reset_button);

    connect(simulation,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));
    connect(start,SIGNAL(clicked(bool)),this,SLOT(simul()));
    connect(boucle,SIGNAL(clicked(bool)),this,SLOT(boucler()));
    connect(stop,SIGNAL(clicked(bool)),this,SLOT(stop_thread()));
    connect(rnd,SIGNAL(clicked(bool)),this,SLOT(etat_rnd()));
    connect(xml_button3,SIGNAL(clicked(bool)),this,SLOT(export_xml()));
    connect(xml_button4,SIGNAL(clicked(bool)),this,SLOT(charger_xml()));
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(slide()));
    connect(reset_button,SIGNAL(clicked(bool)),this,SLOT(reset()));
    connect(lifegame_button,SIGNAL(clicked(bool)),this,SLOT(lifegame()));

    setLayout(bornes);
       // setLayout(couche);
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
                if(nb_color->value()!=1) simulation->item(j,i)->setBackgroundColor(get_color(j,i));
                else simulation->item(j,i)->setBackgroundColor("black");
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
    tab_color[0] = "black";
    tab_color[1] = "blue";
    tab_color[2] = "yellow";
    tab_color[3] = "red";
    tab_color[4] = "green";
    tab_color[5] = "magenta";
    int r1 = rand();
    int r2;
    int r3;
    for(int i=0; i< dimension; i++){
        for(int j=0; j<dimensionHauteur;j++){
            r2 = rand();
            if(r2 > r1){
                r3 = rand() % nb_color->value();
                simulation->item(j,i)->setText("_");
                simulation->item(j,i)->setBackgroundColor(tab_color[r3]);
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
        if(simulation->item(i,j)->text()!=""){
            e.setCellule(i,j,true);
        }
    }
    }
    Xml_Dom doc;
    std::cout<<"aaaaaaaaaaaa"<<std::endl<<e<<std::endl;
    unsigned int nb = AutomateDim2::indiceAutomate2d2025(min_alive->value(),max_alive->value(),min_born->value(),max_born->value());
    //AutomateDim2::func();
    //std::cout<<"gggggg"<<nb;
    doc.ajouter_config_dim2(min_alive->value(),min_born->value(),max_alive->value(),max_born->value(),nb,e);
}

QColor AutoCellDim2::get_color(int j, int i){
    int cpt[nb_color->value()];
    QColor tab[nb_color->value()];
    unsigned int k =0;
    unsigned int nb_color_diff = 0;
    for(k=0;k<nb_color->value();k++){
        cpt[k]=0;
    }
    for(k=0;k<nb_color->value();k++){
    }
    k=0;
    if(j<dimensionHauteur-1 && simulation->item(j+1,i)->backgroundColor().name()!="#ffffff"){
        while (k<nb_color->value() && tab[k]!=simulation->item(j+1,i)->backgroundColor()) {
            k++;
        }
        if(k==nb_color->value()){
            tab[nb_color_diff] = simulation->item(j+1,i)->backgroundColor();
            cpt[nb_color_diff]++;
            nb_color_diff++;
        }else if(tab[k]==simulation->item(j+1,i)->backgroundColor()) cpt[k]++;
        k=0;
    }
    if(j<dimensionHauteur-1 && i<dimension-1 && simulation->item(j+1,i+1)->backgroundColor().name()!="#ffffff"){
        while (k<nb_color->value() && tab[k]!=simulation->item(j+1,i+1)->backgroundColor()) {
            k++;
        }

        if(k==nb_color->value()){
            tab[nb_color_diff] = simulation->item(j+1,i+1)->backgroundColor();
            cpt[nb_color_diff]++;
            nb_color_diff++;
        }else if(tab[k]==simulation->item(j+1,i+1)->backgroundColor()) cpt[k]++;
        k=0;
    }

    if(i<dimension-1 && simulation->item(j,i+1)->backgroundColor().name()!="#ffffff"){
        while (k<nb_color->value() && tab[k]!=simulation->item(j,i+1)->backgroundColor()) {
            k++;
        }

        if(k==nb_color->value()){
            tab[nb_color_diff] = simulation->item(j,i+1)->backgroundColor();
            cpt[nb_color_diff]++;
            nb_color_diff++;
        }else if(tab[k]==simulation->item(j,i+1)->backgroundColor()) cpt[k]++;
        k=0;
    }

    if(j>0 && i>0 && simulation->item(j-1,i-1)->backgroundColor().name()!="#ffffff"){
        while (k<nb_color->value() && tab[k]!=simulation->item(j-1,i-1)->backgroundColor()) {
            k++;
        }

        if(k==nb_color->value()){
            tab[nb_color_diff] = simulation->item(j-1,i-1)->backgroundColor();
            cpt[nb_color_diff]++;
            nb_color_diff++;
        }else if(tab[k]==simulation->item(j-1,i-1)->backgroundColor()) cpt[k]++;
        k=0;
    }

    if(i>0 && simulation->item(j,i-1)->backgroundColor().name()!="#ffffff"){
        while (k<nb_color->value() && tab[k]!=simulation->item(j,i-1)->backgroundColor()) {
            k++;
        }

        if(k==nb_color->value()){
            tab[nb_color_diff] = simulation->item(j,i-1)->backgroundColor();
            cpt[nb_color_diff]++;
            nb_color_diff++;
        }else if(tab[k]==simulation->item(j,i-1)->backgroundColor()) cpt[k]++;
        k=0;
    }

    if(j>0 && simulation->item(j-1,i)->backgroundColor().name()!="#ffffff"){
        while (k<nb_color->value() && tab[k]!=simulation->item(j-1,i)->backgroundColor()) {
            k++;
        }

        if(k==nb_color->value()){
            tab[nb_color_diff] = simulation->item(j-1,i)->backgroundColor();
            cpt[nb_color_diff]++;
            nb_color_diff++;
        }else if(tab[k]==simulation->item(j-1,i)->backgroundColor()) cpt[k]++;
        k=0;
    }
    if(i>0 && j<dimensionHauteur-1 && simulation->item(j+1,i-1)->backgroundColor().name()!="#ffffff"){
        while (k<nb_color->value() && tab[k]!=simulation->item(j+1,i-1)->backgroundColor()) {
            k++;
        }

        if(k==nb_color->value()) {
            tab[nb_color_diff] = simulation->item(j+1,i-1)->backgroundColor();
            cpt[nb_color_diff]++;
            nb_color_diff++;
        }else if(tab[k]==simulation->item(j+1,i-1)->backgroundColor()) cpt[k]++;
        k=0;
    }
    if(j>0 && i<dimension-1 && simulation->item(j-1,i+1)->backgroundColor().name()!="#ffffff"){
        while (k<nb_color->value() && tab[k]!=simulation->item(j-1,i+1)->backgroundColor()) {
            k++;
        }

        if(k==nb_color->value()) {
            tab[nb_color_diff] = simulation->item(j-1,i+1)->backgroundColor();
            cpt[nb_color_diff]++;
            nb_color_diff++;
        }else if(tab[k]==simulation->item(j-1,i+1)->backgroundColor()) cpt[k]++;
    }
    unsigned int max = 0;
    for(k=0;k<nb_color_diff;k++){
        if(cpt[k]>cpt[max]) max = k;
    }
    if(tab[0]==nullptr) return simulation->item(j,i)->backgroundColor();
    return tab[max];
}

void AutoCellDim2::charger_xml(){
    Xml_Dom doc;
    QMap<std::string,std::string> s = doc.charger_config_dim2();
    //std::string ss = s.toStdString();
    //std::cout << s["regle"] << std::endl;
    //std::cout << s["etat"] << "||||" << s["etat"].size()<< std::endl;
    //-------------------Lecture d'etat dim2-----------------------
    Etat e(dimensionHauteur,dimension);
    for(unsigned int i=0;i<dimensionHauteur;i++){
            //e.setValue(s[std::string("etat")+std::to_string(p)]);
            //std::cout<<s[std::string("etat")+std::to_string(p)];


            for (unsigned int j = 0; j < dimension; j++){
                e.setCellule(i,j,(s[std::string("etat")+std::to_string(i)].at(j) == 'x'));
            }


    }
    for(int j=0; j<dimensionHauteur; j++){
        for(int i=0; i<dimension; i++){
            if(e.getCellule(j,i)){
                simulation->item(j,i)->setBackgroundColor("black");
                simulation->item(j,i)->setText("_");
            }else{
                simulation->item(j,i)->setBackgroundColor("white");
                simulation->item(j,i)->setText("");
            }
        }
    }

    //------------------Lecture d'automate dim2-------------------
    min_alive->setValue(std::stoi(s["minv"]));
    min_born->setValue(std::stoi(s["minm"]));
    max_alive->setValue(std::stoi(s["maxv"]));
    max_born->setValue(std::stoi(s["maxm"]));


}

void AutoCellDim2::slide(){
    dimension = slider->value();
    dimensionHauteur = slider->value();
    delete simulation;
    simulation = new QTableWidget(dimensionHauteur,dimension,this);
    unsigned int taille = 25;
    simulation->setFixedSize(15*taille,15*taille);
    simulation->horizontalHeader()->setVisible(false);
    simulation->verticalHeader()->setVisible(false);
    simulation->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    simulation->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for(int i=0; i<dimension; i++){
       for(int j=0; j<dimensionHauteur; j++){
           simulation->setColumnWidth(i,15*taille/dimension);
           simulation->setRowHeight(j,15*taille/dimensionHauteur);
           simulation->setItem(j,i,new QTableWidgetItem(""));
        }
    }
    connect(simulation,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));
    bornes->addWidget(simulation);
}

void AutoCellDim2::reset(){
    for(int i=0; i<dimension; i++){
           for(int j=0; j<dimensionHauteur; j++){
               simulation->item(j,i)->setText("");
               simulation->item(j,i)->setBackgroundColor("white");
            }
        }
}

void AutoCellDim2::lifegame(){
    min_alive->setValue(2);
    max_alive->setValue(3);
    min_born->setValue(3);
    max_born->setValue(3);
}
