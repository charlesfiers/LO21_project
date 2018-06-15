#include "automate.h"

//Etat
Etat::Etat(unsigned int h, unsigned int l) : dimHauteur(h), dimLargeur(l), valeur(new bool*[h]) {
    for (unsigned int i = 0; i < h; i++) {
        valeur[i] = new bool[l];
    }
    for (unsigned int i = 0; i < h; i++) {
        for (unsigned int j = 0; j < l; j++) {
            valeur[i][j] = false;
        }
    }
}

Etat::~Etat() {
    for (unsigned int i = 0; i < dimHauteur; i++) delete[] valeur[i];
    delete[] valeur;
}

Etat::Etat(const Etat& e) : dimHauteur(e.dimHauteur), dimLargeur(e.dimLargeur), valeur(new bool*[dimHauteur]) {
    for (unsigned int i = 0; i < dimHauteur; i++) {
        valeur[i] = new bool[dimLargeur];
        for (unsigned int j = 0; j < dimLargeur; j++) valeur[i][j] = e.valeur[i][j];
    }
}

Etat& Etat::operator=(const Etat& e) {
    if (this != &e) {
        if ((dimHauteur != e.dimHauteur) || (dimLargeur != e.dimLargeur)) {
            bool** newvaleur = new bool*[e.dimHauteur];
            for (unsigned int i = 0; i < e.dimHauteur; i++) {
                newvaleur[i] = new bool[e.dimLargeur];
                for (unsigned int j = 0; j < dimLargeur; j++) newvaleur[i][j] = e.valeur[i][j];
            }
            bool** old = valeur;
            valeur = newvaleur;
            for (unsigned int i = 0; i < dimHauteur; i++) delete[] old[i];
            delete[] old;
            dimHauteur = e.dimHauteur;
            dimLargeur = e.dimLargeur;
            delete[] old;
        }else
            for (unsigned int i = 0; i < e.dimHauteur; i++)
                for (unsigned int j = 0; j < e.dimLargeur; i++)
                    valeur[i][j] = e.valeur[i][j];
    }
    return *this;
}

void Etat::setCellule(unsigned int i, unsigned int j, bool val) {
    if ((i >= dimHauteur) || (j >= dimLargeur)) throw AutomateException("Erreur Cellule");
    valeur[i][j] = val;
}

bool Etat::getCellule(unsigned int i, unsigned int j) const {
    if ((i >= dimHauteur) || (j >= dimLargeur)) throw AutomateException("Erreur Cellule");
    return valeur[i][j];
}

std::ostream& operator<<(std::ostream& f, const Etat& e) {
    for (unsigned int i = 0; i < e.getHauteur(); i++) {
        for (unsigned int j = 0; j < e.getLargeur(); j++)
            if (e.getCellule(i, j)) f << "x"; else f << " ";
        f << "\n";
    }
    return f;
}

//AutomateDim1

short unsigned int AutomateDim1::NumBitToNum(const std::string& numBit) {
    if (numBit.size() != 8) throw AutomateException("Numero d'automate indefini");
    int puissance = 1;
    short unsigned int numero = 0;
    for (int i = 7; i >= 0; i--) {
        if (numBit[i] == '1') numero += puissance;
        else if (numBit[i] != '0') throw AutomateException("Numero d'automate indefini");
        puissance *= 2;
    }
    return numero;
}

std::string AutomateDim1::NumToNumBit(short unsigned int num) {
    std::string numeroBit;
    if (num > 256) throw AutomateException("Numero d'automate indefini");
    unsigned short int p = 128;
    int i = 7;
    while (i >= 0) {
        if (num >= p) {
            numeroBit.push_back('1');
            num -= p;
        }
        else { numeroBit.push_back('0'); }
        i--;
        p = p / 2;
    }
    return numeroBit;
}

AutomateDim1::AutomateDim1(unsigned short int num) : numero(num), numeroBit(NumToNumBit(num)){}

AutomateDim1::AutomateDim1(const std::string& num) :numero(NumBitToNum(num)),numeroBit(num) {}

void AutomateDim1::appliquerTransition(const Etat& dep, Etat& dest) const {
    if (dep.getHauteur() != 1) {
        throw AutomateException("Automate Dimension Erreur");
        return;
    }
    if (dep.getLargeur() != dest.getLargeur()) dest = dep;
    for (unsigned int i = 0; i < dep.getLargeur(); i++) {
        unsigned short int conf = 0;
        if (i > 0) conf += dep.getCellule(0, i-1) * 4;
        conf += dep.getCellule(0, i) * 2;
        if (i < dep.getLargeur() - 1) conf += dep.getCellule(0, i+1);
        dest.setCellule(0, i, numeroBit[7-conf]-'0');
    }
}

std::ostream& operator<<(std::ostream& f, const AutomateDim1& A) {
    f << A.getNumero() << " : " << A.getNumeroBit() << "\n";
    return f;
}

//AutomateDim2

AutomateDim2::AutomateDim2(unsigned short int minV, unsigned short int maxV,
                                             unsigned short int minM, unsigned short int maxM) :
    minVivante(minV), maxVivante(maxV), minMorte(minM), maxMorte(maxM) {}

unsigned int indiceAutomate2d45(unsigned short int min, unsigned short int max) {
    return ( ( 9*(min)+(max+1) )-( ((min)*(min+1))/2 ) );
}

unsigned int indiceAutomate2d2025(unsigned short int minV, unsigned short int maxV,
                              unsigned short int minM, unsigned short int maxM) {
    return ( 45*indiceAutomate2d45(minV,maxV) + indiceAutomate2d45(minM,maxM) );
}

bool AutomateDim2::willBeAlive(unsigned short int n, bool wasAlive) const {
    if (wasAlive)
        if ((n < minVivante) || (n > maxVivante)) return false;
        else return true;
    else
        if ((n < minMorte) || (n > maxMorte)) return false;
        else return true;
}

void AutomateDim2::appliquerTransition(const Etat& dep, Etat& dest) const {
    if (dep.getHauteur() < 2) {
        throw AutomateException("Automate Dimension Erreur");
        return;
    }
    if ((dep.getLargeur() != dest.getLargeur()) || (dep.getHauteur() != dest.getHauteur())) dest = dep;
    for (unsigned int i = 0; i < dep.getHauteur(); i++) {
        for (unsigned int j = 0; j < dep.getLargeur(); j++) {
            unsigned short int conf = 0;
            if (i > 0) conf += dep.getCellule(i - 1, j) ;
            if (i < dep.getHauteur() - 1) conf += dep.getCellule(i + 1, j);
            if (j > 0) conf += dep.getCellule(i , j-1);
            if (j < dep.getLargeur() - 1) conf += dep.getCellule(i, j + 1);
            if (i > 0 && j > 0) conf += dep.getCellule(i - 1, j - 1);
            if ((i < dep.getHauteur() - 1) && (j < dep.getLargeur() - 1)) conf += dep.getCellule(i + 1, j + 1);
            if (i > 0 && (j < dep.getLargeur() - 1)) conf += dep.getCellule(i - 1, j + 1);
            if ((i < dep.getHauteur() - 1) && j > 0) conf += dep.getCellule(i + 1, j - 1);
            if (dep.getCellule(i, j) == 1)
                dest.setCellule(i, j, willBeAlive(conf, true));
            else if (dep.getCellule(i, j) == 0)
                dest.setCellule(i, j, willBeAlive(conf, false));
        }
    }
}

std::ostream& operator<<(std::ostream& f, const AutomateDim2& A) {
    f << "Cell vivante quand vivante et nbr voisins entre " << A.getMinVivante() << " et " << A.getMaxVivante() << "\n";
    f << "Cell vivante quand morte et nbr voisins entre " << A.getMinMorte() << " et " << A.getMaxMorte() << "\n";
    return f;
}

//Simulateur

Simulateur::Simulateur(const Automate& a, unsigned int buffer):
    automate(a), nbMaxEtats(buffer) {
    etats = new Etat*[nbMaxEtats];
    for (unsigned int i = 0; i < nbMaxEtats; i++) etats[i] = nullptr;
}
Simulateur::Simulateur(const Automate& a, const Etat& dep, unsigned int buffer):
    automate(a), depart(&dep), nbMaxEtats(buffer) {
    etats = new Etat*[nbMaxEtats];
    for (unsigned int i = 0; i < nbMaxEtats; i++) etats[i] = nullptr;
    etats[0] = new Etat(dep);
}

void Simulateur::build(unsigned int cellule) {
    if (cellule >= nbMaxEtats) throw AutomateException("erreur taille buffer");
    if (etats[cellule] == nullptr) etats[cellule] = new Etat;
}

void Simulateur::setEtatDepart(const Etat& e) {
    depart = &e;
    reset();
}

void Simulateur::reset() {
    if (depart==nullptr) throw AutomateException("etat depart indefini");
    build(0); *etats[0] = *depart;
    rang = 0;
}

void Simulateur::next() {
    if (depart == nullptr) throw AutomateException("etat depart indefini");
    rang++;
    build(rang%nbMaxEtats);
    automate.appliquerTransition(*etats[(rang - 1) % nbMaxEtats], *etats[rang%nbMaxEtats]);
}

void Simulateur::run(unsigned int nb_steps) {
    for (unsigned int i = 0; i < nb_steps; i++) next();
}

const Etat& Simulateur::dernier() const {
    return *etats[rang%nbMaxEtats];
}

Simulateur::~Simulateur() {
    for (unsigned int i = 0; i < nbMaxEtats; i++) delete etats[i];
    delete[] etats;
}

//AutomateManager

AutomateManager::AutomateManager() {
    for (unsigned int i = 0; i < 256; i++) automatesUneDimension[i] = nullptr;
    for (unsigned int i = 0; i < 2025; i++) automatesDeuxDimension[i] = nullptr;
}

AutomateManager::~AutomateManager() {
    for (unsigned int i = 0; i < 256; i++) delete automatesUneDimension[i];
    for (unsigned int i = 0; i < 2025; i++) delete automatesDeuxDimension[i];
}

AutomateManager::Handler AutomateManager::handler = Handler();

AutomateManager& AutomateManager::getAutomateManager() {
    if (!handler.instance) handler.instance = new AutomateManager;
    return *handler.instance;
}

void AutomateManager::libererAutomateManager() {
    delete handler.instance;
    handler.instance = nullptr;
}

const AutomateDim1& AutomateManager::getAutomateDim1(unsigned short int num) {
    if (!automatesUneDimension[num]) automatesUneDimension[num] = new AutomateDim1(num);
    return *automatesUneDimension[num];
}

const AutomateDim1& AutomateManager::getAutomateDim1(const std::string& numBit) {
    return getAutomateDim1(AutomateDim1::NumBitToNum(numBit));
}

const AutomateDim2& AutomateManager::getAutomateDim2(unsigned int minV, unsigned int maxV,
                                                                      unsigned int minM, unsigned int maxM) {
    if (!automatesDeuxDimension[indiceAutomate2d2025(minV,maxV,minM,maxM)]) automatesDeuxDimension[indiceAutomate2d2025(minV,maxV,minM,maxM)] = new AutomateDim2(minV,maxV,minM,maxM);
    return *automatesDeuxDimension[indiceAutomate2d2025(minV,maxV,minM,maxM)];
}
