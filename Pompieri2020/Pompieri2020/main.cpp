#include <iostream>
#include <string>
#include <fstream>
using namespace std;

enum class TipPompier {
	SERVANT,
	SEFFORMATIE,
	VOLUNTAR,
	SOFER
};

class Pompier {
	const int idPompier;
	string nume;
	TipPompier tip;
	int nrInterventii = 0;
	int* durata = nullptr;

public:
	static int NR_POMPIERI;

	string get_nume() { return this->nume; }

	void set_nume(string nume) {
		if (nume == "" || nume.length() < 3) {
			cout << "Invalid Nume!" << endl;
		}
		else {
			this->nume = nume;
		}
	}

	void set_tip(TipPompier tip) {
		if (tip == TipPompier::SOFER || tip == TipPompier::SERVANT || tip == TipPompier::SEFFORMATIE || tip == TipPompier::VOLUNTAR) {
			this->tip = tip;
		}
		else {
			cout << "Invalid tip!" << endl;
		}
	}

	void set_distanta(int* lista, int nr) {
		delete[] this->durata;
		this->durata = new int[nr];

		for (int i = 0; i < nr; i++) {
			this->durata[i] = lista[i];
		}

		this->nrInterventii = nr;
	}

	int* get_distanta() {
		int* copy = new int[this->nrInterventii];

		for (int i = 0; i < this->nrInterventii; i++) {
			copy[i] = this->durata[i];
		}

		return copy;
	}

	int get_nr() { return this->nrInterventii; }

	Pompier() : idPompier(++NR_POMPIERI) {
		this->nume = "None";
		this->tip = TipPompier::VOLUNTAR;
	}
	
	Pompier(string nume, TipPompier tip) : idPompier(++NR_POMPIERI) {
		this->set_nume(nume);
		this->set_tip(tip);
	}

	Pompier(const Pompier& pomp) : idPompier(pomp.idPompier) {
		this->set_nume(pomp.nume);
		this->set_tip(pomp.tip);
		this->set_distanta(pomp.durata, pomp.nrInterventii);
	}

	~Pompier() {
		delete[] this->durata;
	}

	Pompier& operator=(const Pompier& pomp) {
		if (this == &pomp) {
			return *this;
		}
		else {
			this->set_nume(pomp.nume);
			this->set_tip(pomp.tip);
			this->set_distanta(pomp.durata, pomp.nrInterventii);
		}
	}

	friend ostream& operator<<(ostream& cons, Pompier& pomp);

	void adaugaInterventie(int dur) {
		int* copy = new int[this->nrInterventii + 1];
		for (int i = 0; i < this->nrInterventii; i++) {
			copy[i] = this->durata[i];
		}
		copy[this->nrInterventii] = dur;
		delete[] this->durata;
		this->durata = copy;
		this->nrInterventii += 1;
	}

	float durataMedie() {
		float med = 0.0;
		for (int i = 0; i < this->nrInterventii; i++) {
			med += this->durata[i];
		}
		med = med / this->nrInterventii;
		return med;
	}

	int interventiiDepasite(int val) {
		int nr = 0;
		for (int i = 0; i < this->nrInterventii; i++) {
			if (this->durata[i] > val) {
				nr += 1;
			}
		}
		return nr;
	}

	int& operator[](int index) {
		if (index < 1 || index  > this->nrInterventii) {
			throw exception("Invalid index!");
		}
		else {
			return this->durata[index-1];
		}
	}

	friend ofstream& operator <<(ofstream& doc, Pompier& pomp);
	friend ifstream& operator>>(ifstream& doc, Pompier& pomp);
};

int Pompier::NR_POMPIERI = 0;

ostream& operator<<(ostream& cons, Pompier& pomp) {
	cons << "ID: " << pomp.idPompier << endl;
	cons << "Nume: " << pomp.nume << endl;
	cons << "Tip: " << int(pomp.tip) << endl;
	cons << "Nr interventii: " << pomp.nrInterventii << endl;
	cons << "Interventii: ";
	for (int i = 0; i < pomp.nrInterventii; i++) {
		cons << pomp.durata[i] << " ";
	}
	cons << endl;
	return cons;
}

ofstream& operator <<(ofstream& doc, Pompier& pomp) {
	doc << pomp.idPompier << endl;
	doc << pomp.nume.length() + 1 << endl;
	doc << pomp.nume << endl;
	doc << int(pomp.tip) << endl;
	doc << pomp.nrInterventii << endl;
	for (int i = 0; i < pomp.nrInterventii; i++) {
		doc << pomp.durata[i] << endl;
	}
	return doc;
}

ifstream& operator>>(ifstream& doc, Pompier& pomp) {
	if (pomp.durata != nullptr) {
		delete[] pomp.durata;
	}

	int id;
	doc >> id;

	int numeLen;
	doc >> numeLen;

	doc >> pomp.nume;

	int tipInt;
	doc >> tipInt;
	pomp.tip = TipPompier(tipInt);

	doc >> pomp.nrInterventii;
	pomp.durata = new int[pomp.nrInterventii];
	for (int i = 0; i < pomp.nrInterventii; i++) {
		doc >> pomp.durata[i];
	}

	return doc;

}

class FormatieInterventie {
	char idFormatie[30];
	int nrPompieri;
	Pompier** pompieri;

public:

	void set_idChar(char* id) {
		if (id != nullptr) {
			strcpy_s(this->idFormatie, strlen(id) + 1, id);
		}
		else {
			cout << "Invalid input!" << endl;
		}
	}

	FormatieInterventie(const char id[4], int nr, Pompier* vp[]) {
		strcpy_s(this->idFormatie, 4, id);
		this->nrPompieri = nr;
		this->pompieri = new Pompier * [nr];
		for (int i = 0; i < nr; i++) {
			this->pompieri[i] = new Pompier(*vp[i]);
		}
	}

	FormatieInterventie(const FormatieInterventie& f) {
		strcpy_s(this->idFormatie, strlen(f.idFormatie) + 1, f.idFormatie);
		this->nrPompieri = f.nrPompieri;
		this->pompieri = new Pompier * [f.nrPompieri];
		for (int i = 0; i < f.nrPompieri; i++) {
			this->pompieri[i] = new Pompier(*f.pompieri[i]);
		}
	}

	FormatieInterventie& operator=(const FormatieInterventie& f) {
		if (this == &f) { return *this; }
		else {
			strcpy_s(this->idFormatie, strlen(this->idFormatie) + 1, f.idFormatie);
			for (int i = 0; i < this->nrPompieri; i++) {
				delete this->pompieri[i];
			}
			delete[] this->pompieri;

			this->nrPompieri = f.nrPompieri;
			this->pompieri = new Pompier * [this->nrPompieri];
			for (int i = 0; i < this->nrPompieri; i++) {
				this->pompieri[i] = new Pompier(*f.pompieri[i]);
			}
			return *this;
		}
	}

	~FormatieInterventie() {
		for (int i = 0; i < this->nrPompieri; i++) {
			delete this->pompieri[i];
		}
		delete[] this->pompieri;
	}
};

int main() {
	Pompier p1;
	cout << "P1 name: " << p1.get_nume() << endl;

	Pompier p2("Ion", TipPompier::SOFER);
	cout << "P2 name: " << p2.get_nume() << endl;

	int durInterv[3] = { 21, 21, 21 };
	p2.set_distanta(durInterv, 3);

	int p2NR = p2.get_nr();
	int* p2LIST = p2.get_distanta();

	cout << "P2 durata: ";
	for (int i = 0; i < p2NR; i++) {
		cout << p2LIST[i] << " ";
	}
	cout << endl;

	cout << endl;
	cout << endl;
	cout << endl;
	cout << "Copy constr: " << endl;

	Pompier p2_copy(p2);
	int p2CopNR = p2_copy.get_nr();
	int* p2CopLIST = p2_copy.get_distanta();

	cout << "P2_copy durata: ";
	for (int i = 0; i < p2CopNR; i++) {
		cout << p2CopLIST[i] << " ";
	}
	cout << endl;

	cout << endl;
	cout << "Op =: " << endl;
	Pompier p3Egl;
	p3Egl = p2;
	p3Egl.adaugaInterventie(20);
	int p3NR = p3Egl.get_nr();
	int* p3LIST = p3Egl.get_distanta();

	cout << "P3 durata: ";
	for (int i = 0; i < p2CopNR; i++) {
		cout << p3LIST[i] << " ";
	}
	cout << endl;

	cout << endl;
	cout << "Op <<: " << endl;
	cout << p3Egl;
	cout << endl << "Durata med a interventiilor lui P3 este: " << p3Egl.durataMedie() << endl;
	cout << endl << "Inverventii peste 10 a lui P3 este: " << p3Egl.interventiiDepasite(10) << endl;

	p3Egl[2] = 10;
	int p3NR2 = p3Egl.get_nr();
	int* p3LIST2 = p3Egl.get_distanta();

	cout << "P3 durata: ";
	for (int i = 0; i < p3NR2; i++) {
		cout << p3LIST2[i] << " ";
	}
	cout << endl;

	ofstream doc("Reportbi.bin", ios::binary | ios::trunc);
	doc << p3Egl;
	doc.close();

	Pompier p4;
	ifstream docRead("Reportbi.bin", ios::binary);
	docRead >> p4;
	doc.close();
	int p4NR = p4.get_nr();
	int* p4LIST = p4.get_distanta();

	cout << "P4 durata: ";
	for (int i = 0; i < p4NR; i++) {
		cout << p4LIST[i] << " ";
	}
	cout << endl;

	cout << endl << endl << "Formatie" << endl;
	Pompier** list = new Pompier*[2];
	list[0] = &p2;
	list[1] = &p4;
	FormatieInterventie f1("123", 2, list);
	FormatieInterventie f2 = f1;
	FormatieInterventie f3("234", 0, nullptr);
	f3 = f1;

	return 0;
}