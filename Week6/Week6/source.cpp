#include <iostream>
using namespace std;

enum class TipAuto {SCUTER, DUBA, AUTO};

class Util {
public:
	static string* copiereVector(string* vector, int nrElemente) {
		if (vector == nullptr) { return nullptr; }
		string* copie = new string[nrElemente];
		for (int i = 0; i < nrElemente; i++) { copie[i] = vector[i]; }
		return copie;
	}

	static void vectorStrings(string* vector, int nrElemente) {
		if (vector == nullptr) { cout << "NullPtr" << endl; }
		for (int i = 0; i < nrElemente; i++) { cout << vector[i] << " "; }
	}
};

class Curier {
private:
	string nume = "";
	string* traseuLivrari = nullptr;
	int nrLocatii = 0;
	int nrPachete = 0;
	TipAuto autoLivrare = TipAuto::AUTO;

public:
	string get_nume() {
		return this->nume;
	}

	string* get_traseu() {
		return Util::copiereVector(this->traseuLivrari, this->nrLocatii);
	}

	int get_nrLocatii() {
		return this->nrLocatii;
	}

	int get_nrPachete() {
		return this->nrPachete;
	}

	TipAuto get_TipAuto() {
		return this->autoLivrare;
	}

	void set_nume(string nume) {
		this->nume = nume;
	}

	void set_nrPachete(int nrPachete) {
		if (nrPachete < 0) { throw exception("Nr Negativ"); }
		this->nrPachete = nrPachete;
	}

	//nu se separa numarul de locatii cu traseu 
	void set_traseu(string* traseu, int nrLocatii) {
		delete[] this->traseuLivrari;
		this->traseuLivrari = Util::copiereVector(traseu, nrLocatii);
		this->nrLocatii = nrLocatii;
	}

	void set_tipAuto(TipAuto tip) {
		this->autoLivrare = tip;
	}

	//CONSTRUCTORS
	Curier(string nume, TipAuto tipAuto = TipAuto::AUTO) {
		this->set_nume(nume);
		this->set_tipAuto(tipAuto);
	}

	//DESTRUCTOR - clean-up la nivel de memorie si de logica
	~Curier() {
		delete[] this->traseuLivrari;
	}
};

int main() {
	Curier curier("Ion", TipAuto::DUBA);

	cout << curier.get_nume() << endl;

	curier.set_nume("Gigel");
	
	string locatii[] = { "Piata Victoriei", "Piata Romana", "Unirii", "Universitate" };
	int nrLocatii = 4;

	curier.set_traseu(locatii, nrLocatii);
	curier.set_nrPachete(10);
	curier.set_tipAuto(TipAuto::DUBA);

	cout << curier.get_nume() << endl;
	//Take care at memory leaks, because you print a copy to the string
	string* traseu = curier.get_traseu();
	Util::vectorStrings(traseu, curier.get_nrLocatii());
	delete[] traseu;

	//testare destructor
	{
		Curier c2("IDK");
	}

	//testare destructor
	Curier* pCurier = new Curier("Bob");
	delete pCurier;
}