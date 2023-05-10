#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <fstream>
#include <windows.h>

using namespace std;

ifstream in("Masini.txt");

class IOInterface
{
    virtual istream &citire(istream &in) = 0;
    virtual ostream &afisare(ostream &out) const = 0;
    virtual void citireFisier() = 0;
};

class Masina : public IOInterface
{
protected:
    string firma;
    string model;
    int an;
    double pret;
    int cp;
    int torque;
    char *tractiune;
    bool citit = false;

public:
    // Constructori + Destructor
    Masina();
    Masina(string firma, string model, int an, double pret, int cp, int torque, char *tractiune);
    Masina(const Masina &obj);
    ~Masina();
    // Getters
    string getfirma() { return this->firma; }
    string getmodel() { return this->model; }
    int getan() { return this->an; }
    double getpret() { return this->pret; }
    int getcp() { return this->cp; }
    int gettorque() { return this->torque; }
    const char *gettractiune() const { return this->tractiune; }
    // Setters
    void setfirma(string firma) { this->firma = firma; }
    void setmodel(string model) { this->model = model; }
    void setan(int an) { this->an = an; }
    void setpret(double pret) { this->pret = pret; }
    void setcp(int cp) { this->cp = cp; }
    void settorque(int torque) { this->torque = torque; }
    void settractiune(char *tractiune) { this->tractiune = tractiune; }
    // Supraincarcare Operatori
    Masina &operator=(const Masina &obj);
    friend istream &operator>>(istream &in, Masina &obj) { return obj.citire(in); }
    friend ostream &operator<<(ostream &out, const Masina &obj) { return obj.afisare(out); }
    Masina &operator++();
    Masina operator++(int);
    Masina operator+(const Masina &obj);
    Masina operator+(int x);
    Masina operator-(const Masina &obj);
    Masina operator-(int x);
    bool operator==(const Masina &obj);
    bool operator>(const Masina &obj);
    operator string();
    operator double();
    // Metode
    virtual istream &citire(istream &in)
    {
        cout << "\nFirma: ";
        in >> this->firma;
        cout << "Model: ";
        in >> this->model;
        cout << "An fabricare: ";
        in >> this->an;
        cout << "Pret: ";
        in >> this->pret;
        cout << "Cai putere: ";
        in >> this->cp;
        cout << "Torque: ";
        in >> this->torque;
        cout << "Tractiune: ";
        if (this->tractiune != NULL)
        {
            delete[] this->tractiune;
            this->tractiune = NULL;
        }
        char aux[100];
        in >> aux;
        this->tractiune = new char[strlen(aux) + 1];
        strcpy(this->tractiune, aux);
        return in;
    }
    virtual ostream &afisare(ostream &out) const
    {
        out << "\nFirma: " << this->firma;
        out << "\nModel: " << this->model;
        out << "\nAn Fabricare: " << this->an;
        out << "\nPret: " << this->pret;
        out << "\nCai putere: " << this->cp;
        out << "\nTorque: " << this->torque;
        out << "\nTractiune: " << this->tractiune;
        out << endl;
        return out;
    }
    virtual void citireFisier()
    {
        in >> this->firma;
        in >> this->model;
        in >> this->an;
        in >> this->pret;
        in >> this->cp;
        in >> this->torque;
        in >> this->tractiune;
    }
};
Masina::Masina()
{
    this->firma = "Anonim";
    this->model = "Anonim";
    this->an = 0;
    this->pret = 0.0;
    this->cp = 0;
    this->torque = 0;
    this->tractiune = new char[strlen("Anonim") + 1];
    strcpy(this->tractiune, "Anonim");
}
Masina::Masina(string firma, string model, int an, double pret, int cp, int torque, char *tractiune)
{
    this->firma = firma;
    this->model = model;
    this->an = an;
    this->pret = pret;
    this->cp = cp;
    this->torque = torque;
    if (this->tractiune != NULL)
    {
        delete[] this->tractiune;
        this->tractiune = NULL;
    }
    this->tractiune = new char[strlen(tractiune) + 1];
    strcpy(this->tractiune, tractiune);
}
Masina::Masina(const Masina &obj)
{
    this->firma = obj.firma;
    this->model = obj.model;
    this->an = obj.an;
    this->pret = obj.pret;
    this->cp = obj.cp;
    this->torque = obj.torque;
    if (this->tractiune != NULL)
    {
        delete[] this->tractiune;
        this->tractiune = NULL;
    }
    this->tractiune = new char[strlen(obj.tractiune) + 1];
    strcpy(this->tractiune, obj.tractiune);
}
Masina::~Masina()
{
    delete[] this->tractiune;
    this->tractiune = NULL;
}

Masina &Masina::operator=(const Masina &obj)
{
    if (this != &obj)
    {
        this->firma = obj.firma;
        this->model = obj.model;
        this->an = obj.an;
        this->pret = obj.pret;
        this->cp = obj.cp;
        this->torque = obj.torque;
        if (this->tractiune != NULL)
        {
            delete[] this->tractiune;
            this->tractiune = NULL;
        }
        this->tractiune = new char[strlen(obj.tractiune) + 1];
        strcpy(this->tractiune, obj.tractiune);
    }
    return *this;
}
Masina &Masina::operator++()
{
    this->cp++;
    this->torque++;
    return *this;
}
Masina Masina::operator++(int)
{
    Masina aux(*this);
    ++*this;
    return aux;
}
Masina Masina::operator+(const Masina &obj)
{
    Masina aux(*this);
    aux.cp += obj.cp;
    aux.torque += obj.torque;
    aux.pret += obj.pret;
    return aux;
}
Masina Masina::operator+(int x)
{
    Masina aux(*this);
    aux.cp += x;
    aux.torque += x;
    aux.pret += x;
    return aux;
}
Masina Masina::operator-(const Masina &obj)
{
    Masina aux(*this);
    aux.cp -= obj.cp;
    aux.torque -= obj.torque;
    aux.pret -= obj.pret;
    return aux;
}
Masina Masina::operator-(int x)
{
    Masina aux(*this);
    aux.cp -= x;
    aux.torque -= x;
    aux.pret -= x;
    return aux;
}
bool Masina::operator==(const Masina &obj) { return this->pret == obj.pret; }
bool Masina::operator>(const Masina &obj) { return this->pret > obj.pret; }
Masina::operator string() { return this->model; }
Masina::operator double() { return this->pret; }

class MasinaCombustibil : virtual public Masina
{
protected:
    float consum;
    float capacitateCilindrica;
    string tipMotor;

public:
    // Constructori
    MasinaCombustibil();
    MasinaCombustibil(string firma, string model, int an, double pret, int cp, int torque, char *tractiune,
                      float consum, float capacitateCilindrica, string tipMotor);
    MasinaCombustibil(const MasinaCombustibil &obj);
    // Getters
    float getconsum() { return this->consum; }
    float getcapacitateCilindrica() { return this->capacitateCilindrica; }
    string gettipMotor() { return this->tipMotor; }
    // Setters
    void setconsum(float consum) { this->consum = consum; }
    void setcapacitateCilindrica(float capacitateCilindrica) { this->capacitateCilindrica = capacitateCilindrica; }
    void settipMotor(string tipMotor) { this->tipMotor = tipMotor; }
    // Supraincarcare Operatori
    MasinaCombustibil &operator=(const MasinaCombustibil &obj);
    friend istream &operator>>(istream &in, MasinaCombustibil &obj) { return obj.citire(in); }
    friend ostream &operator<<(ostream &out, const MasinaCombustibil &obj) { return obj.afisare(out); }
    MasinaCombustibil &operator++();
    MasinaCombustibil operator++(int);
    MasinaCombustibil operator+(const MasinaCombustibil &obj);
    MasinaCombustibil operator+(int x);
    MasinaCombustibil operator-(const MasinaCombustibil &obj);
    MasinaCombustibil operator-(int x);
    // Metode
    virtual istream &citire(istream &in)
    {
        if (!citit)
        {
            Masina::citire(in);
            citit = true;
        }
        cout << "Consum: ";
        in >> this->consum;
        cout << "Capacitate Cilindrica: ";
        in >> this->capacitateCilindrica;
        cout << "Tip Motor: ";
        in >> this->tipMotor;
        return in;
    }
    virtual ostream &afisare(ostream &out) const
    {
        Masina::afisare(out);
        out << "Consum: " << this->consum << " l/100km" << endl;
        out << "Capacitate Cilindrica: " << this->capacitateCilindrica << " cc" << endl;
        out << "Tip Motor: " << this->tipMotor << endl;
        return out;
    }
    virtual void citireFisier()
    {
        if (!citit)
        {
            Masina::citireFisier();
            citit = true;
        }
        in >> this->consum;
        in >> this->capacitateCilindrica;
        in >> this->tipMotor;
    }
};
MasinaCombustibil::MasinaCombustibil() : Masina()
{
    this->consum = 0.0;
    this->capacitateCilindrica = 0.0;
    this->tipMotor = "Anonim";
}
MasinaCombustibil::MasinaCombustibil(string firma, string model, int an, double pret, int cp, int torque, char *tractiune, float consum,
                                     float capacitateCilindrica, string tipMotor) : Masina(firma, model, an, pret, cp, torque, tractiune)
{
    this->consum = consum;
    this->capacitateCilindrica = capacitateCilindrica;
    this->tipMotor = tipMotor;
}
MasinaCombustibil::MasinaCombustibil(const MasinaCombustibil &obj) : Masina(obj)
{
    this->consum = obj.consum;
    this->capacitateCilindrica = obj.capacitateCilindrica;
    this->tipMotor = obj.tipMotor;
}

MasinaCombustibil &MasinaCombustibil::operator=(const MasinaCombustibil &obj)
{
    if (this != &obj)
    {
        Masina::operator=(obj);
        this->consum = obj.consum;
        this->capacitateCilindrica = obj.capacitateCilindrica;
        this->tipMotor = obj.tipMotor;
    }
    return *this;
}
MasinaCombustibil &MasinaCombustibil::operator++()
{
    Masina::operator++();
    return *this;
}
MasinaCombustibil MasinaCombustibil::operator++(int)
{
    MasinaCombustibil aux(*this);
    ++*this;
    return aux;
}
MasinaCombustibil MasinaCombustibil::operator+(const MasinaCombustibil &obj)
{
    Masina::operator+(obj);
    MasinaCombustibil aux(*this);
    aux.capacitateCilindrica += obj.capacitateCilindrica;
    return aux;
}
MasinaCombustibil MasinaCombustibil::operator+(int x)
{
    Masina::operator+(x);
    MasinaCombustibil aux(*this);
    aux.capacitateCilindrica += x;
    return aux;
}
MasinaCombustibil MasinaCombustibil::operator-(const MasinaCombustibil &obj)
{
    Masina::operator-(obj);
    MasinaCombustibil aux(*this);
    aux.capacitateCilindrica -= obj.capacitateCilindrica;
}
MasinaCombustibil MasinaCombustibil::operator-(int x)
{
    Masina::operator-(x);
    MasinaCombustibil aux(*this);
    aux.capacitateCilindrica -= x;
    return aux;
}

class MasinaElectrica : virtual public Masina
{
protected:
    float range;
    string tipBaterie;
    float capacitateBaterie;
    int chargeTime;

public:
    // Constructori
    MasinaElectrica();
    MasinaElectrica(string firma, string model, int an, double pret, int cp, int torque, char *tractiune, float range, string tipBaterie,
                    float capacitateBaterie, int chargeTime);
    MasinaElectrica(const MasinaElectrica &obj);
    // Getters
    float getrange() { return this->range; }
    string gettipBaterie() { return this->tipBaterie; }
    float getcapacitateBaterie() { return this->capacitateBaterie; }
    int getchargeTime() { return this->chargeTime; }
    // Setters
    void setrange(float range) { this->range = range; }
    void settipBaterie(string tipBaterie) { this->tipBaterie = tipBaterie; }
    void setcapacitateBaterie(float capacitateBaterie) { this->capacitateBaterie = capacitateBaterie; }
    void setchargeTime(int chargeTime) { this->chargeTime = chargeTime; }
    // Supraincarcare Operatori
    MasinaElectrica &operator=(const MasinaElectrica &obj);
    friend istream &operator>>(istream &in, MasinaElectrica &obj) { return obj.citire(in); }
    friend ostream &operator<<(ostream &out, const MasinaElectrica &obj) { return obj.afisare(out); }
    MasinaElectrica &operator++();
    MasinaElectrica operator++(int);
    MasinaElectrica operator+(const MasinaElectrica &obj);
    MasinaElectrica operator+(int x);
    MasinaElectrica operator-(const MasinaElectrica &obj);
    MasinaElectrica operator-(int x);
    // Metode
    virtual istream &citire(istream &in)
    {
        if (!citit)
        {
            Masina::citire(in);
            citit = true;
        }
        cout << "Range: ";
        in >> this->range;
        cout << "Tip Baterie: ";
        in >> this->tipBaterie;
        cout << "Capacitate Baterie: ";
        in >> this->capacitateBaterie;
        cout << "Timp de Incarcare: ";
        in >> this->chargeTime;
        return in;
    }
    virtual ostream &afisare(ostream &out) const
    {
        Masina::afisare(out);
        out << "Range: " << this->range << " km";
        out << "\nTip Baterie: " << this->tipBaterie;
        out << "\nCapacitate Baterie: " << this->capacitateBaterie << " kWh";
        out << "\nTimp de incarcare: " << this->chargeTime << " minute";
        return out;
    }
    virtual void citireFisier()
    {
        if (!citit)
        {
            Masina::citireFisier();
            citit = true;
        }
        in >> this->range;
        in >> this->tipBaterie;
        in >> this->capacitateBaterie;
        in >> this->chargeTime;
    }
};
MasinaElectrica::MasinaElectrica() : Masina()
{
    this->range = 0.0;
    this->tipBaterie = "Anonim";
    this->capacitateBaterie = 0.0;
    this->chargeTime = 0;
}
MasinaElectrica::MasinaElectrica(string firma, string model, int an, double pret, int cp, int torque, char *tractiune, float range, string tipBaterie,
                                 float capacitateBaterie, int chargeTime) : Masina(firma, model, an, pret, cp, torque, tractiune)
{
    this->range = range;
    this->tipBaterie = tipBaterie;
    this->capacitateBaterie = capacitateBaterie;
    this->chargeTime = chargeTime;
}
MasinaElectrica::MasinaElectrica(const MasinaElectrica &obj) : Masina(obj)
{
    this->range = obj.range;
    this->tipBaterie = obj.tipBaterie;
    this->capacitateBaterie = obj.capacitateBaterie;
    this->chargeTime = obj.chargeTime;
}

MasinaElectrica &MasinaElectrica::operator=(const MasinaElectrica &obj)
{
    if (this != &obj)
    {
        Masina::operator=(obj);
        this->range = obj.range;
        this->tipBaterie = obj.tipBaterie;
        this->capacitateBaterie = obj.capacitateBaterie;
        this->chargeTime = obj.chargeTime;
    }
    return *this;
}
MasinaElectrica &MasinaElectrica::operator++()
{
    Masina::operator++();
    return *this;
}
MasinaElectrica MasinaElectrica::operator++(int)
{
    MasinaElectrica aux(*this);
    ++*this;
    return aux;
}
MasinaElectrica MasinaElectrica::operator+(const MasinaElectrica &obj)
{
    Masina::operator+(obj);
    MasinaElectrica aux(*this);
    aux.chargeTime += obj.chargeTime;
    return aux;
}
MasinaElectrica MasinaElectrica::operator+(int x)
{
    Masina::operator+(x);
    MasinaElectrica aux(*this);
    aux.chargeTime += x;
    return aux;
}
MasinaElectrica MasinaElectrica::operator-(const MasinaElectrica &obj)
{
    Masina::operator-(obj);
    MasinaElectrica aux(*this);
    this->chargeTime -= obj.chargeTime;
    return aux;
}
MasinaElectrica MasinaElectrica::operator-(int x)
{
    Masina::operator-(x);
    MasinaElectrica aux(*this);
    this->chargeTime -= x;
    return aux;
}

class MasinaHybrid : public MasinaCombustibil, MasinaElectrica
{
    bool selfCharge;
    int emisii;

public:
    // Constructori
    MasinaHybrid();
    MasinaHybrid(string firma, string model, int an, double pret, int cp, int torque, char *tractiune, float consum,
                 float capacitateCilindrica, string tipMotor, float range, string tipBaterie, float capacitateBaterie,
                 int chargeTime, bool selfCharge, int emisii);
    MasinaHybrid(const MasinaHybrid &obj);
    // Getters
    bool getselfCharge() { return this->selfCharge; }
    int getemisii() { return this->emisii; }
    // Setters
    void setselfCharge(bool selfCharge) { this->selfCharge = selfCharge; }
    void setemisii(int emisii) { this->emisii = emisii; }
    // Supraincarare Operatori
    MasinaHybrid &operator=(const MasinaHybrid &obj);
    friend istream &operator>>(istream &in, MasinaHybrid &obj) { return obj.citire(in); }
    friend ostream &operator<<(ostream &out, const MasinaHybrid &obj) { return obj.afisare(out); }
    // Metode
    virtual istream &citire(istream &in) override
    {
        MasinaCombustibil::citire(in);
        MasinaElectrica::citire(in);
        cout << "Este plug-in hybrid?(1 = true/0 = false): ";
        in >> this->selfCharge;
        cout << "Emisii: ";
        in >> this->emisii;
        return in;
    }
    virtual ostream &afisare(ostream &out) const
    {
        Masina::afisare(out);
        out << "Consum: " << this->consum << " l/100km" << endl;
        out << "Capacitate Cilindrica: " << this->capacitateCilindrica << " cc" << endl;
        out << "Tip Motor: " << this->tipMotor << endl;
        out << "Range: " << this->range << " km";
        out << "\nTip Baterie: " << this->tipBaterie;
        out << "\nCapacitate Baterie: " << this->capacitateBaterie << " kWh";
        out << "\nTimp de incarcare: " << this->chargeTime << " minute";
        out << "\nPlug-in hybrid: ";
        if (this->selfCharge)
            out << "true";
        else
            out << "false";
        out << "\nEmisii: " << this->emisii;
        return out;
    }
    virtual void citireFisier()
    {
        MasinaCombustibil::citireFisier();
        MasinaElectrica::citireFisier();
        in >> this->selfCharge;
        in >> this->emisii;
    }
};
MasinaHybrid::MasinaHybrid() : MasinaCombustibil(), MasinaElectrica()
{
    this->selfCharge = false;
    this->emisii = 0;
}
MasinaHybrid::MasinaHybrid(string firma, string model, int an, double pret, int cp, int torque, char *tractiune, float consum,
                           float capacitateCilindrica, string tipMotor, float range, string tipBaterie, float capacitateBaterie,
                           int chargeTime, bool selfCharge, int emisii)
    : MasinaCombustibil(firma, model, an, pret, cp, torque, tractiune, consum, capacitateCilindrica, tipMotor),
      MasinaElectrica(firma, model, an, pret, cp, torque, tractiune, range, tipBaterie, capacitateBaterie, chargeTime)
{
    this->selfCharge = selfCharge;
    this->emisii = emisii;
}
MasinaHybrid::MasinaHybrid(const MasinaHybrid &obj) : MasinaCombustibil(obj), MasinaElectrica(obj)
{
    this->selfCharge = obj.selfCharge;
    this->emisii = obj.emisii;
}

MasinaHybrid &MasinaHybrid::operator=(const MasinaHybrid &obj)
{
    if (this != &obj)
    {
        MasinaCombustibil::operator=(obj);
        MasinaElectrica::operator=(obj);
        this->selfCharge = obj.selfCharge;
        this->emisii = obj.emisii;
    }
    return *this;
}

class Stock
{
    Masina *masina;
    int cantitate;

public:
    // Constructori si deconstructor
    Stock();
    Stock(Masina *masina, int cantitate);
    Stock(const Stock &obj);
    ~Stock();
    // Getters
    Masina *getmasina() const { return this->masina; }
    int getcantitate() { return this->cantitate; }
    // Setters
    void setmasina(Masina *masina) { this->masina = masina; }
    void setcantitate(int cantitate) { this->cantitate = cantitate; }
    // Supraincarcare Operatori
    Stock &operator=(const Stock &obj);
    friend istream &operator>>(istream &in, Stock &obj);
    friend ostream &operator<<(ostream &out, const Stock &obj);
    // Metode
    void citireFisierStock();
};
Stock::Stock()
{
    this->masina = NULL;
    this->cantitate = 0;
}
Stock::Stock(Masina *masina, int cantitate)
{
    this->masina = masina;
    this->cantitate = cantitate;
}
Stock::Stock(const Stock &obj)
{
    Masina *masina = new Masina(*obj.masina);
    this->masina = masina;
    this->cantitate = obj.cantitate;
}
Stock::~Stock()
{
    delete masina;
}

Stock &Stock::operator=(const Stock &obj)
{
    if (this != &obj)
    {
        Masina *masina = new Masina(*obj.masina);
        this->masina = masina;
        this->cantitate = obj.cantitate;
    }
    return *this;
}
istream &operator>>(istream &in, Stock &obj)
{
    cout << "\nAlegeti tipul masinii:";
    cout << "\n1. Masina Benzina/Diesel;"
         << "\n2. Masina Electrica;"
         << "\n3. Masina Hybrid;"
         << "\n(introduceti numarul corespunzator)";
    int k;
    in >> k;
    if (k != 1 && k != 2 && k != 3)
        cout << "\nComanda invalida";
    if (k == 1)
        obj.masina = new MasinaCombustibil();
    if (k == 2)
        obj.masina = new MasinaElectrica();
    if (k == 3)
        obj.masina = new MasinaHybrid();
    in >> *obj.masina;
    cout << "\nCate masini doriti sa fie in stock? ";
    in >> obj.cantitate;
    return in;
}
ostream &operator<<(ostream &out, const Stock &obj)
{
    cout << "\nCout stock";
    out << *obj.masina << endl;
    out << obj.cantitate << " Masini in stock";
    return out;
}

void Stock::citireFisierStock()
{
    int k;
    in >> k;
    if (k == 1)
        this->masina = new MasinaCombustibil();
    if (k == 2)
        this->masina = new MasinaElectrica();
    if (k == 3)
        this->masina = new MasinaHybrid();
    this->masina->citireFisier();
    in >> this->cantitate;
}

class DealerShip
{
    string nume;
    list<Stock> stockMasini;
    vector<Masina *> masini;

public:
    // Constructori si Deconstructor
    DealerShip();
    DealerShip(string nume, list<Stock> stockMasini, vector<Masina *> masini);
    DealerShip(const DealerShip &obj);
    // Getters
    string getnume() { return this->nume; }
    list<Stock> getstockMasini() { return this->stockMasini; }
    // Setters
    void setnume(string nume) { this->nume = nume; }
    // Supraincarcare operatori
    DealerShip &operator=(const DealerShip &obj);
    // Metode
    void addStock();
    void showStock();
    void showMasini();
    void selectMasina(string model);

    Masina *buyCar(string masinaAleasa);
    void sellCar(string model);

    void addFromFile(int x);
};
DealerShip::DealerShip()
{
    this->nume = "Anonim";
    this->stockMasini = {};
    this->masini = {};
}
DealerShip::DealerShip(string nume, list<Stock> stockMasini, vector<Masina *> masini)
{
    this->nume = nume;
    this->stockMasini = stockMasini;
    this->masini = masini;
}
DealerShip::DealerShip(const DealerShip &obj)
{
    this->nume = obj.nume;
    this->stockMasini = obj.stockMasini;
    this->masini = obj.masini;
}

DealerShip &DealerShip::operator=(const DealerShip &obj)
{
    if (this != &obj)
    {
        this->nume = obj.nume;
        this->stockMasini = obj.stockMasini;
        this->masini = obj.masini;
    }
    return *this;
}

void DealerShip::addStock()
{
    Stock masina;
    cin >> masina;
    stockMasini.push_back(masina);
    masini.push_back(masina.getmasina());
}
void DealerShip::addFromFile(int x)
{
    for (int i = 0; i < x; i++)
    {
        Stock masina;
        masina.citireFisierStock();
        stockMasini.push_back(masina);
    }
}
void DealerShip::showStock()
{
    for (auto aux = stockMasini.begin(); aux != stockMasini.end(); aux++)
        cout << *aux;
}
void DealerShip::showMasini()
{
    for (auto aux = stockMasini.begin(); aux != stockMasini.end(); aux++)
    {
        Masina masina;
        masina = *aux->getmasina();
        cout << endl;
        cout << masina.getfirma() << ' ' << masina.getmodel();
    }
}
void DealerShip::selectMasina(string model)
{
    for (auto aux = stockMasini.begin(); aux != stockMasini.end(); aux++)
    {
        if (aux->getmasina()->getmodel() == model)
        {
            cout << *aux;
            return;
        }
    }
}
Masina *DealerShip::buyCar(string masinaAleasa)
{
    for (auto aux = stockMasini.begin(); aux != stockMasini.end(); aux++)
    {
        Masina *masina;
        if (aux->getmasina()->getmodel() == masinaAleasa)
        {
            masina = aux->getmasina();
            return masina;
        }
    }
}

void DealerShip::sellCar(string model)
{
    for (auto aux = stockMasini.begin(); aux != stockMasini.end(); aux++)
        if (aux->getmasina()->getmodel() == model)
            stockMasini.erase(aux);
}

class Client
{
    char *nume;
    double bani;
    Masina *masina;

public:
    // Constructori si Destructor
    Client();
    Client(char *nume, double bani, Masina *masina);
    Client(const Client &obj);
    ~Client();
    // Getters
    const char *getnume() const { return this->nume; }
    double getbani() { return this->bani; }
    Masina *getmasina() const { return this->masina; }
    // Setters
    void setnume(char *nume) { this->nume = nume; }
    void setbani(double bani) { this->bani = bani; }
    void setmasina(Masina *masina) { this->masina = masina; }
    // Supraincarcare Operatori
    Client &operator=(const Client &obj);
    friend istream &operator>>(istream &in, Client &obj);
    friend ostream &operator<<(ostream &out, Client &obj);
    Client &operator++();
    Client operator++(int);
    Client operator+(const Client &obj);
    Client operator+(int x);
    Client operator-(const Client &obj);
    Client operator-(int x);
    bool operator==(const Client &obj);
    bool operator>(const Client &obj);
    // Metode
    void showMasina();
    void sellCar(double pret);
};
Client::Client()
{
    this->nume = new char[strlen("Anonim") + 1];
    strcpy(this->nume, "Anonim");
    this->bani = 0;
    this->masina = new Masina();
}
Client::Client(char *nume, double bani, Masina *masina)
{
    this->nume = new char[strlen(nume) + 1];
    strcpy(this->nume, nume);
    this->bani = bani;
    this->masina = masina;
}
Client::Client(const Client &obj)
{
    if (this->nume != NULL)
    {
        delete[] this->nume;
        this->nume = NULL;
    }
    this->nume = new char[strlen(obj.nume) + 1];
    strcpy(this->nume, obj.nume);
    this->bani = obj.bani;
    Masina *aux = new Masina(*obj.masina);
    this->masina = aux;
}
Client::~Client()
{
    delete[] this->nume;
    delete[] this->masina;
}

Client &Client::operator=(const Client &obj)
{
    if (this != &obj)
    {
        if (this->nume != NULL)
        {
            delete[] this->nume;
            this->nume = NULL;
        }
        this->nume = new char[strlen(obj.nume) + 1];
        strcpy(this->nume, obj.nume);
        this->bani = obj.bani;
        Masina *aux = new Masina(*obj.masina);
        this->masina = aux;
    }
    return *this;
}
istream &operator>>(istream &in, Client &obj)
{
    if (obj.nume != NULL)
    {
        delete[] obj.nume;
        obj.nume = NULL;
    }
    char aux[100];
    cout << "Introduceti numele: ";
    in >> aux;
    obj.nume = new char[strlen(aux) + 1];
    strcpy(obj.nume, aux);
    cout << "Introduceti cati bani doriti sa aveti: ";
    in >> obj.bani;
    return in;
}
ostream &operator<<(ostream &out, Client &obj)
{
    out << "\nNume: " << obj.nume;
    out << "\nBani: " << obj.bani << " euro";
    return out;
}
Client &Client::operator++()
{
    this->bani++;
    return *this;
}
Client Client::operator++(int)
{
    Client aux(*this);
    ++*this;
    return aux;
}
Client Client::operator+(const Client &obj)
{
    Client aux(*this);
    aux.bani += obj.bani;
    return aux;
}
Client Client::operator+(int x)
{
    Client aux(*this);
    aux.bani += x;
    return aux;
}
Client Client::operator-(const Client &obj)
{
    Client aux(*this);
    aux.bani -= obj.bani;
    return aux;
}
Client Client::operator-(int x)
{
    Client aux(*this);
    aux.bani -= x;
    return aux;
}
bool Client::operator==(const Client &obj) { return this->nume == obj.nume; }
bool Client::operator>(const Client &obj) { return this->bani > obj.bani; }

void Client::showMasina() { cout << this->masina->getfirma() << ' ' << this->masina->getmodel(); }
void Client::sellCar(double pret)
{
    this->masina = new Masina();
    this->bani += pret;
}

int main()
{
    // Alegere dealership + initializare obiecte
    system("CLS");
    Client client;
    DealerShip baseDS("All You Need Dealership", {}, {});
    DealerShip dealerShip;
    string numeDS;
    cout << "Bine ati venit la simulatorul de cumparat masini\n\n"
         << "Alegeti o optiune:"
         << "\n1. Dealership Default;"
         << "\n2. Creati un Dealership;"
         << "\n(introduceti numarul corespunzator)\n";
    int k;
    cin >> k;
    if (k == 1)
    {
        dealerShip = baseDS;
        system("CLS");
        cout << "\nAti ales Dealership Default"
             << "\nBine v-am gasit la " << baseDS.getnume() << '!';
        int nrMasini;
        in >> nrMasini;
        dealerShip.addFromFile(nrMasini);
        Sleep(2000);
    }
    if (k == 2)
    {
        baseDS.~DealerShip();
        system("CLS");
        cout << "\nAti ales Dealership Custom\n"
             << "\nIntroduceti numele dorit pentru Dealership: ";
        string aux;
        cin >> aux;
        dealerShip.setnume(aux);
        system("CLS");
        cout << endl;
        cout << "Ati creat Dealership " << dealerShip.getnume();
        cout << endl;
        int contor = 1;
        while (contor > 0 && contor < 5)
        {
            system("CLS");
            cout << "\n1. Adaugati Masini;"
                 << "\n2. Eliminati Masini;"
                 << "\n3. Afisati Stock;"
                 << "\n4. Terminat;"
                 << "\n(introduceti numarul corespunzator)\n";
            cin >> contor;
            if (contor < 1 && contor > 5)
                cout << "\nComanda invalida;\n";
            else
            {
                switch (contor)
                {
                case 1:
                {
                    dealerShip.addStock();
                    break;
                }
                case 2:
                {
                    string model;
                    cout << "\nCe masina doriti sa eliminati?";
                    cin >> model;
                    dealerShip.sellCar(model);
                    cout << "\nMasina eliminata cu succes!";
                    Sleep(1000);
                    break;
                }
                case 3:
                {
                    cout << "\nMasini in Stock: \n";
                    dealerShip.showStock();
                    Sleep(3000);
                    break;
                }
                case 4:
                {
                    contor = 0;
                    system("CLS");
                    break;
                }
                }
            }
        }
    }
    // Citire date
    cout << "\n\nContinuati prin a va introduce datele\n";
    cin >> client;
    cout << "\nIntroduceti CNP: ";
    Sleep(2000);
    cout << "\n\nJust kidding :)";
    Sleep(2000);
    system("CLS");
    cout << "\nNe bucuram sa te avem alaturi, " << client.getnume() << '!';
    if (client.getbani() > 100000)
        cout << "\nObervam ca aveti un portofel cam gros";
    numeDS = dealerShip.getnume();
    Sleep(3000);
    system("CLS");
    int contor = 1;
    // Main menu
    while (contor > 0 && contor < 4)
    {
        system("CLS");
        cout << endl
             << numeDS << endl;
        cout << "\nAlegeti o optiune: ";
        cout << "\n1.Detalii client;"
             << "\n2.Browse Dealership;"
             << "\n3.Vinde masina;"
             << "\n4.Incheiati sesiunea;"
             << endl;
        cin >> contor;
        if (contor < 1 && contor > 4)
            cout << "\nComanda Invalida.";
        else
        {
            switch (contor)
            {
            case 1:
            {
                system("CLS");
                cout << endl
                     << numeDS << endl;
                cout << "\nDetalii client:\n";
                cout << client;
                if (client.getmasina()->getmodel() == "Anonim")
                    cout << "\nNu detineti o masina.";
                else
                {
                    cout << "\nMasina detinuta este:\n";
                    client.showMasina();
                    cout << "\n Doriti detalii pentru masina? (Y/N)\n";
                    char input;
                    cin >> input;
                    if (strchr("Yy", input))
                        cout << "\n Masina este: \n";
                    cout << *client.getmasina();
                }
                string goBack;
                cout << "\nInput anything to continue...";
                cin >> goBack;
                break;
            }
            case 2:
            {
                int browse = 1;
                if (browse == 1)
                {
                    system("CLS");
                    cout << endl;
                    cout << "\nMasinile valabile sunt:\n ";
                    dealerShip.showMasini();
                    char input;
                    cout << "\nDoriti sa primiti detalii pentru o masina?(Y/N)\n";
                    cin >> input;
                    if (strchr("Yy", input))
                    {
                        string masinaAleasa;
                        cout << "\nPentru care model de masina doriti sa primiti detalii?\n";
                        cin >> masinaAleasa;
                        dealerShip.selectMasina(masinaAleasa);
                        cout << "\nDoriti sa cumparati masina?(Y/N)\n";
                        char inputBuy;
                        cin >> inputBuy;
                        if (strchr("Yy", inputBuy))
                        {
                            if (client.getmasina()->getan() != 0)
                            {
                                cout << "\nTrebuie intai sa vindeti masina pe care o aveti!";
                                browse = 0;
                            }
                            else
                            {
                                client.setmasina(dealerShip.buyCar(masinaAleasa));
                                cout << "\nAti achizionat " << masinaAleasa;
                            }
                        }
                    }
                    cout << "\n1.Browse masini;"
                         << "\n2.Reveniti la meniul principal;"
                         << "\n(introduceti numarul corespunzator)\n";
                    cin >> browse;
                }
                break;
            }
            case 3:
            {
                if (client.getmasina()->getmodel() == "Anonim")
                    cout << "\nNu aveti ce masina sa vindeti!";
                else
                {
                    cout << "\nMasina vanduta!";
                    client.sellCar(client.getmasina()->getpret());
                }
                Sleep(2000);
                break;
            }
            case 4:
            {
                contor = 0;
                cout << "\n\nVa multumim!";
                break;
            }
            }
        }
    }
    in.close();
}