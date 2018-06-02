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
                for (unsigned int i = 0; i < dimLargeur) newvaleur[i][j] = e.valeur[i][j];
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
    for (unsigned int i = 0; i < e.getDimHauteur(); i++) {
        for (unsigned int j = 0; j < e.getDimLargeur(); j++)
            if (e.getCellule(i, j)) f << char(178); else f << " ";
        f << "\n";
    }
    return f;
}

//AutomateUneDimension

short unsigned int AutomateUneDimension::NumBitToNum(const std::string& num) {
    if (num.size() != 8) throw AutomateException("Numero d'automate indefini");
    int puissance = 1;
    short unsigned int numero = 0;
    for (int i = 7; i >= 0; i--) {
        if (num[i] == '1') numero += puissance;
        else if (num[i] != '0') throw AutomateException("Numero d'automate indefini");
        puissance *= 2;
    }
    return numero;
}

std::string AutomateUneDimension::NumToNumBit(short unsigned int num) {
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

AutomateUneDimension::AutomateUneDimension(unsigned short int num) : numero(num), numeroBit(NumToNumBit(num)){}

AutomateUneDimension::AutomateUneDimension(const std::string& num) :numero(NumBitToNum(num)),numeroBit(num) {}

void AutomateUneDimension::appliquerTransition(const Etat& dep, Etat& dest) const {
    if (dep.getDimHauteur() != 1) {
        throw AutomateException("Automate Dimension Erreur");
        return;
    }
    if (dep.getDimLargeur() != dest.getDimLargeur()) dest = dep;
    for (unsigned int i = 0; i < dep.getDimLargeur(); i++) {
        unsigned short int conf = 0;
        if (i > 0) conf += dep.getCellule(0, i-1) * 4;
        conf += dep.getCellule(0, i) * 2;
        if (i < dep.getDimLargeur() - 1) conf += dep.getCellule(0, i+1);
        dest.setCellule(0, i, numeroBit[7-conf]-'0');
    }
}

std::ostream& operator<<(std::ostream& f, const Automate& A) {
    f << A.getNumero() << " : " << A.getNumeroBit() << "\n";
    return f;
}

//AutomateDeuxDimension

AutomateDeuxDimension::AutomateDeuxDimension(unsigned short int minVivante, unsigned short int maxVivante,
                                             unsigned short int minMorte, unsigned short int maxMorte) :
    CellVivanteNbrMinVoisins(minVivante), CellVivanteNbrMaxVoisins(maxVivante),
    CellMorteNbrMinVoisins(minMorte), CellMorteNbrMaxVoisins(maxMorte) {}

bool AutomateDeuxDimension::willBeAlive(unsigned short int n, bool wasAlive) {
    if (wasAlive)
        if ((n < CellVivanteNbrMinVoisins) || (n > CellVivanteNbrMaxVoisins))
            return false;
        else
            return true;
    else
        if ((n < CellMorteNbrMinVoisins) || (n > CellMorteNbrMaxVoisins))
            return false;
        else
            return true;
}

void AutomateDeuxDimension::appliquerTransition(const Etat& dep, Etat& dest) const {
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


Simulateur::Simulateur(const Automate& a, unsigned int buffer):
    automate(a), etats(nullptr), depart(nullptr), nbMaxEtats(buffer),rang(0) {
    etats = new Etat*[nbMaxEtats];
    for (unsigned int i = 0; i < nbMaxEtats; i++) etats[i] = nullptr;
}
Simulateur::Simulateur(const Automate& a, const Etat& dep, unsigned int buffer):
    automate(a), etats(nullptr), depart(&dep), nbMaxEtats(buffer),rang(0) {
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

AutomateManager::AutomateManager() {
    for (unsigned int i = 0; i < 256; i++) automates[i] = nullptr;
}

AutomateManager::~AutomateManager() {
    for (unsigned int i = 0; i < 256; i++) delete automates[i];
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

const Automate& AutomateManager::getAutomate(unsigned short int num) {
    if (!automates[num]) automates[num] = new Automate(num);
    return *automates[num];
}
const Automate& AutomateManager::getAutomate(const std::string& numBit) {
    return getAutomate(NumBitToNum(numBit));
}
