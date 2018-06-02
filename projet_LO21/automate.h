#include <string>
#include <iostream>

class AutomateException {
public:
	AutomateException(const std::string& message) :info(message) {}
	std::string getInfo() const { return info; }
private:
	std::string info;
};

class Etat {
	//Si dimHauteur == 1 c'est un dimension, sinon il est deux dimension
	unsigned int dimLargeur;
	unsigned int dimHauteur;
	unsigned int short** valeur;
	//ici bool->int pour les autres automates qu'on veut
public:
	Etat():dimLargeur(0),dimHauteur(0), valeur(nullptr) {}
	Etat(unsigned int h , unsigned int l);
	~Etat();
	Etat(const Etat& e);
	Etat& operator=(const Etat& e);
	void setCellule(unsigned int i, unsigned int j, unsigned int short val);
	unsigned int short getCellule(unsigned int i, unsigned int j) const;
	unsigned int getLargeur() const { return dimLargeur; }
	unsigned int getHauteur() const { return dimHauteur; }
};

std::ostream& operator<<(std::ostream& f, const Etat& e);

class Automate {
public:
	virtual void appliquerTransition(const Etat& dep, Etat& dest) const = 0;
	//QJsonObject& save() const;
};

class AutomateUnDimension:public Automate {
	unsigned short int numero;
	std::string numeroBit;
	AutomateUnDimension(unsigned short int num);
	AutomateUnDimension(const std::string& num);
	~AutomateUnDimension() = default;
	AutomateUnDimension(const AutomateUnDimension& a) = default;
	AutomateUnDimension& operator=(const AutomateUnDimension& a) = default;
	friend class AutomateManager;
	static short unsigned int NumBitToNum(const std::string& num);
	static std::string NumToNumBit(short unsigned int num);
public:
	unsigned short int getNumero() const { return numero; }
	const std::string& getNumeroBit() const { return numeroBit; }
	virtual void appliquerTransition(const Etat& dep, Etat& dest) const;
};

std::ostream& operator<<(std::ostream& f, const AutomateUnDimension& t);

class AutomateDeuxDimension :public Automate {
	unsigned short int numCellVivant;
	unsigned short int numCellMorte;
	std::string numBitCellVivant;
	std::string numBitCellMorte;
	AutomateDeuxDimension(unsigned short int n,unsigned short int m);
	AutomateDeuxDimension(const std::string& BitVivant,const std::string& BitMorte);
	~AutomateDeuxDimension() = default;
	AutomateDeuxDimension(const AutomateDeuxDimension& a) = default;
	AutomateDeuxDimension& operator=(const AutomateDeuxDimension& a) = default;
	friend class AutomateManager;
	static short unsigned int NumBitToNum(const std::string& num);
	static std::string NumToNumBit(short unsigned int num);
public:
	unsigned short int getNumCellVivant() const { return numCellVivant; }
	unsigned short int getNumCellMorte() const { return numCellMorte; }
	const std::string& getNumeroBitVivant() const { return numBitCellVivant; }
	const std::string& getNumeroBitMorte() const { return numBitCellMorte; }
	virtual void appliquerTransition(const Etat& dep, Etat& dest) const;
};

std::ostream& operator<<(std::ostream& f, const AutomateDeuxDimension& t);

class Simulateur {
	const Automate& automate;
	Etat** etats=nullptr;
	const Etat* depart=nullptr;
	unsigned int nbMaxEtats;
	unsigned int rang=0;
	void build(unsigned int c);
	Simulateur(const Simulateur& s) = delete;
	Simulateur& operator=(const Simulateur& s) = delete;
public:
	Simulateur(const Automate& a, unsigned int buffer = 2);
	Simulateur(const Automate& a, const Etat& dep, unsigned int buffer = 2);
	void setEtatDepart(const Etat& e);
	void run(unsigned int nbSteps); // génère les n prochains états
	void next(); // génère le prochain état
	const Etat& dernier() const;
	unsigned int getRangDernier() const { return rang; }
	void reset(); // revenir à l'état de départ
	~Simulateur();
	friend class Iterator;
	class Iterator {
		friend class Simulateur;
		Simulateur* sim = nullptr;
		int i = 0;
		Iterator(Simulateur* s):sim(s), i(s->rang){}
	public:
		Iterator() {}
		bool isDone() const { 
			return sim == nullptr || 
				   (i == -1 && sim->rang<sim->nbMaxEtats) ||
				   i == sim->rang - sim->nbMaxEtats;
		}
		void next() {
			if (isDone())
				throw AutomateException("error, next on an iterator which is done");
			i--;
			if (i == -1 && sim->rang >= sim->nbMaxEtats) i = sim->nbMaxEtats - 1;
		}
		Etat& current() const {
			if (isDone())
				throw AutomateException("error, indirection on an iterator which is done");
			return *sim->etats[i%sim->nbMaxEtats];
		}
	};
	Iterator getIterator() {
		return Iterator(this);
	}
	class ConstIterator {
		friend class Simulateur;
		const Simulateur* sim = nullptr;
		int i = 0;
		ConstIterator(const Simulateur* s) :sim(s), i(s->rang) {}
	public:
		ConstIterator() {}
		bool isDone() const {
			return sim==nullptr || (i == -1 && sim->rang<sim->nbMaxEtats) ||
				i== sim->rang - sim->nbMaxEtats;
		}
		void next() {
			if (isDone())
				throw AutomateException("error, next on an iterator which is done");
			i--;
			if (i == -1 && sim->rang >= sim->nbMaxEtats) i = sim->nbMaxEtats - 1;
		}
		const Etat& current() const {
			if (isDone())
				throw AutomateException("error, indirection on an iterator which is done");
			return *sim->etats[i%sim->nbMaxEtats];
		}
	};
	ConstIterator getIterator() const{
		return ConstIterator(this);
	}
	ConstIterator getConstIterator() const {
		return ConstIterator(this);
	}

	class iterator {
		friend class Simulateur;
		Simulateur* sim = nullptr;
		int i = 0;
		iterator(Simulateur* s) :sim(s), i(s->rang) {}
		iterator(Simulateur* s, int dep) :sim(s), i(dep) {}
	public:
		iterator() {}
		iterator& operator++() {
			i--;
			if (i == -1 && sim->rang >= sim->nbMaxEtats) i = sim->nbMaxEtats - 1;
			return *this;
		}
		Etat& operator*() const {
			return *sim->etats[i%sim->nbMaxEtats];
		}
		bool operator!=(iterator it) const { return sim != it.sim || i != it.i; }
	};

	iterator begin() {	return iterator(this); }
	iterator end() { if (rang < nbMaxEtats) return iterator(this, -1); else return iterator(this, rang - nbMaxEtats);  }

	class const_iterator {
		friend class Simulateur;
		const Simulateur* sim = nullptr;
		int i = 0;
		const_iterator(const Simulateur* s) :sim(s), i(s->rang) {}
		const_iterator(const Simulateur* s, int dep) :sim(s), i(dep) {}
	public:
		const_iterator() {}
		const_iterator& operator++() {
			i--;
			if (i == -1 && sim->rang >= sim->nbMaxEtats) i = sim->nbMaxEtats - 1;
			return *this;
		}
		const Etat& operator*() const {
			return *sim->etats[i%sim->nbMaxEtats];
		}
		bool operator!=(const_iterator it) const { return sim != it.sim || i != it.i; }
	};

	const_iterator begin() const { return const_iterator(this); }
	const_iterator end() const { if (rang < nbMaxEtats) return const_iterator(this, -1); else return const_iterator(this, rang - nbMaxEtats); }
	const_iterator cbegin() const { return const_iterator(this); }
	const_iterator cend() const { if (rang < nbMaxEtats) return const_iterator(this, -1); else return const_iterator(this, rang - nbMaxEtats); }
	
	//void saveAutomate(const std::string& name) const;
	//void loadAutomate(const std::string& name) const;
	//QJsonObject& saveConfiguration() const;
};

class AutomateManager {
	AutomateUnDimension* automatesUnDimension[256];
	AutomateDeuxDimension* automatesDeuxDimension[512];
	AutomateManager();
	~AutomateManager();
	AutomateManager(const AutomateManager& a) = delete;
	AutomateManager& operator=(const AutomateManager& a) = delete;
	struct Handler {
		AutomateManager* instance;
		Handler() :instance(nullptr) {}
		~Handler() { delete instance; }
	};
	static Handler handler;
public:
	const AutomateUnDimension& getAutomateUnDimension(unsigned short int num);
	const AutomateUnDimension& getAutomateUnDimension(const std::string& num);
	const AutomateDeuxDimension& getAutomateDeuxDimension(unsigned short int nV, unsigned short int nM);
	const AutomateDeuxDimension& getAutomateDeuxDimension(const std::string& BitVivant, const std::string& BitMorte);
	static AutomateManager& getAutomateManager();
	static void libererAutomateManager();
};
//
//class AutomateManager {
//	AutomateManager(const AutomateManager& a) = delete;
//	AutomateManager& operator=(const AutomateManager& a) = delete;
//protected:
//		struct Handler {
//		AutomateManager* instance;
//		Handler():instance(nullptr) {}
//		~Handler() { delete instance;  }
//	};
//	static Handler handler;
//};
//
//class AutomateManagerUnDimension :public AutomateManager {
//	Automate* automates[256];
//	AutomateManagerUnDimension();
//	~AutomateManagerUnDimension();
//public:
//	static AutomateManagerUnDimension& getAutomateManager();
//	static void libererAutomateManager();
//	const AutomateUnDimension& getAutomate(unsigned short int num);
//	const AutomateUnDimension& getAutomate(const std::string& num);
//};
//
//class AutomateManagerDeuxDimension :public AutomateManager {
//	Automate* automates[512];
//	AutomateManagerDeuxDimension();
//	~AutomateManagerDeuxDimension();
//public:
//	static AutomateManagerDeuxDimension& getAutomateManager();
//	static void libererAutomateManager();
//	const AutomateDeuxDimension& getAutomate(unsigned short int num);
//	const AutomateDeuxDimension& getAutomate(const std::string& num);
//};