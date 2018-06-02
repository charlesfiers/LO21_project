#include "automate.h"

//Etat
Etat::Etat(unsigned int h, unsigned int l) :
	dimHauteur(h),dimLargeur(l){
	valeur = new unsigned int short*[h];
	for (unsigned int i = 0; i < h; i++) {
		valeur[i] = new unsigned int short[l];
	}
	for (unsigned int i = 0; i < h; i++){
		for (unsigned int j = 0; j < l; j++) {
			valeur[i][j] = 0;
			/*std::cout << valeur[i][j];*/
		}
	}
}
Etat::~Etat() {
	for (unsigned int i = 0; i < dimHauteur; i++) delete[] valeur[i];
	delete[] valeur;
}

Etat::Etat(const Etat& e) :
	dimLargeur(e.dimLargeur),
	dimHauteur(e.dimHauteur),
	valeur(new unsigned int short*[e.dimHauteur])
{
	for (unsigned int i = 0; i < dimHauteur; i++) {
		valeur[i] = new unsigned int short[dimLargeur];
		for (unsigned int j = 0; j < dimLargeur; j++)
			valeur[i][j] = e.valeur[i][j];
	}
}

void Etat::setCellule(unsigned int i, unsigned int j, unsigned int short val) {
	if ((i >= dimHauteur) || (j >= dimLargeur)) throw AutomateException("Erreur Cellule");
	valeur[i][j] = val;
}

unsigned int short Etat::getCellule(unsigned int i, unsigned int j) const {
	if ((i >= dimHauteur) || (j >= dimLargeur)) throw AutomateException("Erreur Cellule");
	return valeur[i][j];
}



std::ostream& operator<<(std::ostream& f, const Etat& e) {
	for (unsigned int i = 0; i < e.getHauteur(); i++) {
		for (unsigned int j = 0; j < e.getLargeur(); j++)
			if (e.getCellule(i, j)) f << e.getCellule(i, j)<<" "; else f << "0 ";//ici c'est pour bien afficher
		f << "\n";
	}
	return f;
}

Etat& Etat::operator=(const Etat& e) {
	if (this != &e) {
		if ((dimLargeur != e.dimLargeur) || (dimHauteur != e.dimHauteur)) {
			unsigned int short** newvaleur = new unsigned int short*[e.dimHauteur];
			for (unsigned int i = 0; i < e.dimHauteur; i++) {
				newvaleur[i] = new unsigned int short[e.dimLargeur];
				for (unsigned int j = 0; j < e.dimLargeur; j++)
					newvaleur[i][j] = e.valeur[i][j];
			}
			unsigned int short** old = valeur;
			valeur = newvaleur;
			for (unsigned int i = 0; i < dimHauteur; i++) delete[] old[i];
			delete[] old;
			dimHauteur = e.dimHauteur;
			dimLargeur = e.dimLargeur;
		}
		else for (unsigned int i = 0; i < e.dimHauteur; i++) {
			for (unsigned int j = 0; j < e.dimLargeur; j++)
				valeur[i][j] = e.valeur[i][j];
		}
	}
	return *this;
}

//Automate 1 Dimension

short unsigned int AutomateUnDimension::NumBitToNum(const std::string& num) {
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


std::string AutomateUnDimension::NumToNumBit(short unsigned int num) {
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

AutomateUnDimension::AutomateUnDimension(unsigned short int num) :numero(num), numeroBit(NumToNumBit(num)) {
}

AutomateUnDimension::AutomateUnDimension(const std::string& num) : numero(NumBitToNum(num)), numeroBit(num) {
}


void AutomateUnDimension::appliquerTransition(const Etat& dep, Etat& dest) const {
	if (dep.getHauteur() != 1) {
		throw AutomateException("Ce n'est pas un dimension");
		return;
	}
	//Ici je pense que peut-etre c'est mieux d'creer 2 class d'Etats,Etat 1 dimension et Etat 2 dimension
	if (dep.getLargeur() != dest.getLargeur()) dest = dep;
	for (unsigned int i = 0; i < dep.getLargeur(); i++) {
		unsigned short int conf = 0;
		if (i > 0) conf += dep.getCellule(0, i-1) * 4;
		conf += dep.getCellule(0, i) * 2;
		if (i < dep.getLargeur() - 1) conf += dep.getCellule(0, i+1);
		dest.setCellule(0, i, numeroBit[7 - conf] - '0');
	}
}

std::ostream& operator<<(std::ostream& f, const AutomateUnDimension& A) {
	f << A.getNumero() << " : " << A.getNumeroBit() << "\n";
	return f;
}


//Automate 2 Dimension

short unsigned int AutomateDeuxDimension::NumBitToNum(const std::string& num) {
	if (num.size() != 9) throw AutomateException("Numero d'automate indefini");
	int puissance = 1;
	short unsigned int numero = 0;
	for (int i = 8; i >= 0; i--) {
		if (num[i] == '1') numero += puissance;
		else if (num[i] != '0') throw AutomateException("Numero d'automate indefini");
		puissance *= 2;
	}
	return numero;
}

std::string AutomateDeuxDimension::NumToNumBit(short unsigned int num) {
	std::string numeroBit;
	if (num > 512) throw AutomateException("Numero d'automate indefini");
	unsigned short int p = 256;
	int i = 8;
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

AutomateDeuxDimension::AutomateDeuxDimension(unsigned short int n, unsigned short int m) :
	numCellVivant(n), numCellMorte(m),
	numBitCellVivant(NumToNumBit(n)), numBitCellMorte(NumToNumBit(n)) {}

AutomateDeuxDimension::AutomateDeuxDimension(const std::string& BitVivant, const std::string& BitMorte) :
	numCellVivant(NumBitToNum(BitVivant)), numCellMorte(NumBitToNum(BitMorte)),
	numBitCellVivant(BitVivant), numBitCellMorte(BitMorte) {}

void AutomateDeuxDimension::appliquerTransition(const Etat& dep, Etat& dest) const {
	if (dep.getHauteur() < 2) {
		throw AutomateException("Ce n'est pas deux dimension");
		return;
	}
	//Ici je pense que peut-etre c'est mieux d'creer 2 class d'Etats,Etat 1 dimension et Etat 2 dimension
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
				dest.setCellule(i, j, numBitCellVivant[8 - conf] - '0');
			else if (dep.getCellule(i, j) == 0)
				dest.setCellule(i, j, numBitCellMorte[8 - conf] - '0');
		}
	}
}

std::ostream& operator<<(std::ostream& f, const AutomateDeuxDimension& A) {
	f << A.getNumCellVivant() << " : " << A.getNumCellMorte() << " : " << A.getNumeroBitVivant() << " : " << A.getNumeroBitMorte() << "\n";
	return f;
}

//Simulateur
Simulateur::Simulateur(const Automate& a, unsigned int buffer) :
	automate(a), nbMaxEtats(buffer) {
	etats = new Etat*[nbMaxEtats];
	for (unsigned int i = 0; i < nbMaxEtats; i++) etats[i] = nullptr;
}
Simulateur::Simulateur(const Automate& a, const Etat& dep, unsigned int buffer) :
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
	if (depart == nullptr) throw AutomateException("etat depart indefini");
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
	for (unsigned int i = 0; i < 256; i++) automatesUnDimension[i] = nullptr;
	for (unsigned int i = 0; i < 512; i++) automatesDeuxDimension[i] = nullptr;
}

AutomateManager::~AutomateManager() {
	for (unsigned int i = 0; i < 256; i++) delete automatesUnDimension[i];
	for (unsigned int i = 0; i < 512; i++) delete automatesDeuxDimension[i];
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

const AutomateUnDimension& AutomateManager::getAutomateUnDimension(unsigned short int num) {
	if (!automatesUnDimension[num]) automatesUnDimension[num] = new AutomateUnDimension(num);
	return *automatesUnDimension[num];
}
const AutomateUnDimension& AutomateManager::getAutomateUnDimension(const std::string& numBit) {
	return getAutomateUnDimension(AutomateUnDimension::NumBitToNum(numBit));
}

const AutomateDeuxDimension& AutomateManager::getAutomateDeuxDimension(unsigned short int nV,unsigned short int nM) {
	if (!automatesDeuxDimension[nV,nM]) automatesDeuxDimension[nV,nM] = new AutomateDeuxDimension(nV,nM);
	return *automatesDeuxDimension[nV,nM];
}
const AutomateDeuxDimension& AutomateManager::getAutomateDeuxDimension(const std::string& BitVivant, const std::string& BitMorte) {
	return getAutomateDeuxDimension(AutomateDeuxDimension::NumBitToNum(BitVivant), AutomateDeuxDimension::NumBitToNum(BitMorte));
}

//AutomateManager::Handler AutomateManager::handler = Handler();
//
////AutomateManager 1 Dimension
//
//AutomateManagerUnDimension::AutomateManagerUnDimension():AutomateManager() {
//	for (unsigned int i = 0; i < 256; i++) automates[i] = nullptr;
//}
//
//AutomateManagerUnDimension::~AutomateManagerUnDimension() {
//	for (unsigned int i = 0; i < 256; i++) delete automates[i];
//}
//
//
//AutomateManagerUnDimension& AutomateManagerUnDimension::getAutomateManager() {
//	if (!handler.instance) handler.instance = new AutomateManagerUnDimension;
//	return *handler.instance;
//}
//
//void AutomateManager::libererAutomateManager() {
//	delete handler.instance;
//	handler.instance = nullptr;
//}
//
//const AutomateUnDimension& AutomateManagerUnDimension::getAutomate(unsigned short int num) {
//	if (!automates[num]) automates[num] = new AutomateUnDimension(num);
//	return *automates[num];
//}
//const AutomateUnDimension& AutomateManagerUnDimension::getAutomate(const std::string& numBit) {
//	return getAutomate(AutomateUnDimension::NumBitToNum(numBit));
//}
//
////AutomateManager 2 Dimensions
//
//AutomateManagerDeuxDimension::AutomateManagerDeuxDimension() {
//	for (unsigned int i = 0; i < 512; i++) automates[i] = nullptr;
//}
//
//AutomateManagerDeuxDimension::~AutomateManagerDeuxDimension() {
//	for (unsigned int i = 0; i < 512; i++) delete automates[i];
//}
//
//const AutomateDeuxDimension& AutomateManagerDeuxDimension::getAutomate(unsigned short int num) {
//	if (!automates[num]) automates[num] = new AutomateDeuxDimension(num);
//	return *automates[num];
//}
//const AutomateDeuxDimension& AutomateManagerDeuxDimension::getAutomate(const std::string& numBit) {
//	return getAutomate(AutomateDeuxDimension::NumBitToNum(numBit));
//}
