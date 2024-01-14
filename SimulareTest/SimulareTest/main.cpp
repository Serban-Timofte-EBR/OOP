#include <iostream>
using namespace std;

enum class type {CITY_BREAK, AVENTURA, MUNTE};

class Vacanta {
private:
	const string nume;
	string destinatie = "";
	type tip = type::CITY_BREAK;
	bool esteAllInclusive = false;
	float* cheltuieli = nullptr;
	int nrCheltuieli = 0;
	int nrPrieteni = 0;

	const static int MAX_BUGET = 10000;

public:

	void set_cheltuieli(float* lista, int nrLista) {
		if (nrLista < 1) { throw exception("Lista invalida!"); }
		else {
			delete[] this->cheltuieli;
			this->cheltuieli = new float[nrLista];
			for (int i = 0; i < nrLista; i++) {
				this->cheltuieli[i] = lista[i];
			}
			this->nrCheltuieli = nrLista;
		}
	}

	float* get_cheltuieli() {
		float* copy = new float[this->nrCheltuieli];
		for (int i = 0; i < this->nrCheltuieli; i++) {
			copy[i] = this->cheltuieli[i];
		}
		return copy;
	}

	Vacanta(string nume, string destinatie, type tip) :nume(nume), destinatie(destinatie), tip(tip) {};

	Vacanta(const Vacanta& v):nume(v.nume) {
		this->destinatie = v.destinatie;
		this->set_cheltuieli(v.cheltuieli, v.nrCheltuieli);
		this->tip = v.tip;
		this->esteAllInclusive = v.esteAllInclusive;
		this->nrPrieteni = v.nrPrieteni;
	}

	~Vacanta() {
		delete[] this->cheltuieli;
	}

	void adaugaExtraOptiuni() {
		this->esteAllInclusive = true;
	}

	bool get_allInclusive() {
		return this->esteAllInclusive;
	}

	Vacanta* operator=(const Vacanta& v) {
		if (this == &v) { return this; }
		this->destinatie = v.destinatie;
		this->set_cheltuieli(v.cheltuieli, v.nrCheltuieli);
		this->tip = v.tip;
		this->esteAllInclusive = v.esteAllInclusive;
		this->nrPrieteni = v.nrPrieteni;
		return this;
	}

	friend ostream& operator<<(ostream& cons, const Vacanta& v);
	friend Vacanta operator*(float nr, Vacanta& v);

	void operator>(const Vacanta& v) {
		float totalChThis = 0;
		for (int i = 0; i < this->nrCheltuieli; i++) {
			totalChThis += this->cheltuieli[i];
		}

		float totalChV = 0;
		for (int i = 0; i < v.nrCheltuieli; i++) {
			totalChV += v.cheltuieli[i];
		}

		if (totalChThis > totalChV) { cout << "Primul argument este mai mare!" << endl; }
	}

	void operator!() {
		float totalCh = 0;
		for (int i = 0; i < this->nrCheltuieli; i++) {
			totalCh += this->cheltuieli[i];
		}

		if (totalCh > MAX_BUGET) { cout << "Bugetul a fost depasit!" << endl; }
		else {
			cout << this->nume << " este in limitele bugetare!" << endl;
		}
	}

	void chBiggerThen(float val) {
		bool flag = false;
		for (int i = 0; i < this->nrCheltuieli; i++) {
			if (this->cheltuieli[i] > val) {
				flag = true;
				cout << "Cheltuiala " << i+1 << " in valoare de " << this->cheltuieli[i] << " depaseste valoarea setata de " << val << "." << endl;
			}
		}

		if (flag == false) {
			cout << "Cheltuielile nu au depasit valoarea setata de " << val << "." << endl;
		}
	}
};

ostream& operator<<(ostream& cons, const Vacanta& v) {
	cons << "Numele: " << v.nume << endl;
	cons << "Destinatie: " << v.destinatie << endl;
	cons << "Tip: ";
	if (v.tip == type::AVENTURA) { cons << "AVENTURA"; }
	else if (v.tip == type::CITY_BREAK) { cons << "CITY_BREAK"; }
	else if (v.tip == type::MUNTE) { cons << "MUNTE"; }
	else { cons << "INVALID"; }
	cons << endl;
	cons << "Este All Inclusive: " << v.esteAllInclusive << endl;
	cons << "NrCheltuieli: " << v.nrCheltuieli << endl;
	cons << "Cheltuieli: ";
	for (int i = 0; i < v.nrCheltuieli; i++) {
		cons << v.cheltuieli[i] << " ";
	}
	cons << endl;
	cons << "Numar Prienteni: " << v.nrPrieteni << endl;
	return cons;
}

Vacanta operator*(float nr, Vacanta& v) {
	Vacanta newVac = v;
	float* chNew = new float[v.nrCheltuieli];

	for (int i = 0; i < v.nrCheltuieli; i++) {
		chNew[i] = nr * v.cheltuieli[i];
	}

	newVac.set_cheltuieli(chNew, v.nrCheltuieli);
	delete[] chNew;

	return newVac;
}


int main() {
	Vacanta v1("Vacanta iarna", "Predeal", type::MUNTE);
	float* ch = new float[3] {10.5, 25.7, 80.6};
	int nrCh = 3;

	v1.set_cheltuieli(ch, nrCh);
	float* chgetted = new float[3];
	cout << "Cheltuieli prin getter (v1): " << endl;
	chgetted = v1.get_cheltuieli();
	for (int i = 0; i < 3; i++) {
		cout << chgetted[i] << " ";
	}
	cout << endl;

	cout << endl << "---------------------------------------" << endl;
	cout << "Destructor Testing" << endl;
	Vacanta* v2 = new Vacanta("Vacanta de vara", "Roma", type::CITY_BREAK);
	v2->set_cheltuieli(ch, nrCh);
	delete v2;
	cout << "Object from HEAP was finished!" << endl;

	cout << endl << "---------------------------------------" << endl;
	cout << "Copy Constructor" << endl;
	Vacanta vCopy = v1;
	float* chCopy = new float[3];
	chCopy = vCopy.get_cheltuieli();
	cout << "Cheltuielile copiei: " << endl;
	for (int i = 0; i < 3; i++) {
		cout << chCopy[i] << " ";
	}

	cout << endl << "---------------------------------------" << endl;
	cout << "v1.adaugaExtraOptiuni()" << endl;
	v1.adaugaExtraOptiuni();
	cout << "Este All Inclusive? : " << v1.get_allInclusive() << endl;

	cout << endl << "---------------------------------------" << endl;
	cout << "Operator =" << endl;
	Vacanta v3("Bucuresti", "Bucuresti", type::CITY_BREAK);
	v3 = v1;
	float* chV3 = new float[3];
	chV3 = v3.get_cheltuieli();
	cout << "Cheltuieli V3 dupa v3=v1: " << endl;
	for (int i = 0; i < 3; i++) {
		cout << chV3[i] << " ";
	}
	cout << endl;

	cout << endl << "---------------------------------------" << endl;
	cout << "Operator << (pe V1):" << endl;
	cout << v1;

	cout << endl << "---------------------------------------" << endl;
	cout << "Operator * (pe V3):" << endl;
	v3 = 0.5 * v1;
	cout << endl << "V1:" << endl;
	cout << v1 << endl;
	cout << endl << "V3:" << endl;
	cout << v3 << endl;

	cout << endl << "---------------------------------------" << endl;
	cout << "Operator >: " << endl;
	cout << " v3>v1: " << endl;
	v3 > v1;
	cout << " V1>V3: " << endl;
	v1 > v3;

	cout << endl << "---------------------------------------" << endl;
	cout << "Operator !: " << endl;
	!v1;

	cout << endl << "---------------------------------------" << endl;
	cout << "Functie depasesc valoare data: " << endl;
	v1.chBiggerThen(12.5);

	delete[] ch;
	delete[] chgetted;
	return 0;
};