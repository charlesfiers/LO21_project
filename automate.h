#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>
#include <iostream>
#include "autocelldim1.h"
#include "autocelldim2.h"

class AutomateException {
public:
    AutomateException(const std::string& message) :info(message) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};

class Etat {
    unsigned int dimHauteur; //Si dimHauteur==1 alors AutomateDim1 sinon AutomateDim2
    unsigned int dimLargeur;
    bool** valeur;
public:
    Etat() : dimHauteur(0), dimLargeur(0), valeur(nullptr) {}
    Etat(unsigned int h, unsigned int l);
    ~Etat();
    Etat(const Etat& e);
    Etat& operator=(const Etat& e);
    void setCellule(unsigned int i, unsigned int j, bool val);
    bool getCellule(unsigned int i, unsigned int j) const;
    unsigned int getLargeur() const { return dimLargeur; }
    unsigned int getHauteur() const { return dimHauteur; }
    void setValue(const std::string & str);
};

std::ostream& operator<<(std::ostream& f, const Etat& e);

class AutomateManager;

class Automate{
public:
    virtual void appliquerTransition(const Etat& dep, Etat& dest) const = 0;
    //QXMLObject save() const;
};

class AutomateDim1 : public Automate {
    unsigned short int numero;
    std::string numeroBit;
    AutomateDim1(unsigned short int num);
    AutomateDim1(const std::string& num);
    virtual ~AutomateDim1() = default;
    AutomateDim1(const AutomateDim1& a) = default;
    AutomateDim1& operator=(const AutomateDim1& a) = default;
    friend class AutomateManager;
    //friend class AutoCell;

public:
    static short unsigned int NumBitToNum(const std::string& numBit);
    static std::string NumToNumBit(short unsigned int num);
    unsigned short int getNumero() const { return numero; }
    const std::string& getNumeroBit() const { return numeroBit; }
    virtual void appliquerTransition(const Etat& dep, Etat& dest) const;
};

std::ostream& operator<<(std::ostream& f, const AutomateDim1& t);


class AutomateDim2 :public Automate { //Alias JV : Jeu de la vie
    unsigned short int minVivante; //Nombre min de voisins vivants si cellule vivante pour vivre (JV : 2)
    unsigned short int maxVivante; //Nombre max de voisins vivants si cellule vivante pour vivre (JV : 3)
    unsigned short int minMorte; //Nombre min de voisins vivants si cellule morte pour vivre (JV : 3)
    unsigned short int maxMorte; //Nombre max de voisins vivants si cellule morte pour vivre (JV : 3)
    static unsigned int indiceAutomate2d45(unsigned short int min, unsigned short int max); //combinaison des min et max possibles (valeurs entre 0 et 8: 45 combinaisons)
    static unsigned int indiceAutomate2d2025(unsigned short int minV, unsigned short int maxV,
                                         unsigned short int minM,   unsigned short int maxM
                                         ); //indice dans le tableau de AutomateManager en fonction des 4 attributs (2025 combinaisons)
    AutomateDim2(unsigned short int minV, unsigned short int maxV,
                          unsigned short int minM,   unsigned short int maxM);
    virtual ~AutomateDim2() = default;
    AutomateDim2(const AutomateDim2& a) = default;
    AutomateDim2& operator=(const AutomateDim2& a) = default;
    friend class AutomateManager;
    //static int func();
    friend class AutoCellDim2;
public:
    unsigned short int getMinVivante() const { return minVivante; }
    unsigned short int getMaxVivante() const { return maxVivante; }
    unsigned short int getMinMorte() const { return minMorte; }
    unsigned short int getMaxMorte() const { return maxMorte; }
    bool willBeAlive(unsigned short int n, bool wasAlive) const;
    virtual void appliquerTransition(const Etat& dep, Etat& dest) const;
};

std::ostream& operator<<(std::ostream& f, const AutomateDim2& t);

class Simulateur {
    const Automate& automate;
    Etat** etats = nullptr;
    const Etat* depart = nullptr;
    unsigned int nbMaxEtats;
    unsigned int rang = 0;
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
        int i;
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
        const Simulateur* sim;
        int i;
        const_iterator(const Simulateur* s) :sim(s), i(s->rang) {}
        const_iterator(const Simulateur* s, int dep) :sim(s), i(dep) {}
    public:
        const_iterator():sim(nullptr),i(0) {}
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

    const_iterator cbegin() const { return const_iterator(this); }
    const_iterator cend() const { if (rang < nbMaxEtats) return const_iterator(this, -1); else return const_iterator(this, rang - nbMaxEtats); }

    //void saveAutomate(const std::string& name) const;
    //void loadAutomate(const std::string& name) const;
    //QXmlObject& saveConfiguration() const;
};

class AutomateManager {
    AutomateDim1* automatesUneDimension[256];
    AutomateDim2* automatesDeuxDimension[2025];
    AutomateManager();
    ~AutomateManager();
    AutomateManager(const AutomateManager& a) = delete;
    AutomateManager& operator=(const AutomateManager& a) = delete;
    struct Handler {
        AutomateManager* instance;
        Handler():instance(nullptr) {}
        ~Handler() { delete instance;  }
    };
    static Handler handler;
public:
    const AutomateDim1& getAutomateDim1(unsigned short int num);
    const AutomateDim1& getAutomateDim1(const std::string& numBit);
    const AutomateDim2& getAutomateDim2(unsigned int minV, unsigned int maxV,
                                                          unsigned int minM, unsigned int maxM);
    static AutomateManager& getAutomateManager();
    static void libererAutomateManager();
};


#endif // AUTOMATE_H
