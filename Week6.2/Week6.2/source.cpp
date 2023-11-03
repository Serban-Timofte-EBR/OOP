#include <iostream>
#include <string>
using namespace std;

enum class Stare {CLIENT, RIDICAT, DEPOZIT, LIVRAT};

class Util {
public:
	static char* copiereVector(const char* vector) {
		if (vector == nullptr) { return nullptr; }
		char* copie = new char[strlen(vector) + 1];
		strcpy_s(copie, strlen(vector) + 1, vector);
		return copie;
	}
};

class Pachet {
	const int id;
	char* adresaLivrare = nullptr;
	float greutate = 0.0;
	bool fragil = false;
	Stare stare = Stare::RIDICAT;

	static int PACHETE_IN_DEPOZIT; //static NON-CONST nu poate fi initializat in clasa
	/*
		Avem static int si nu doar int, deoarece obiectul are atribute specifice lui.
		int PACHETE_IN_DEPOZIT: Obiectul Pachet stie cate pachete sunt in depozit. Adaug 
		un nou pachet => trebuie sa actualizez in toate obiectele PACHET 
		(static somehow global)
	*/
	static int GENERATOR_ID;

public:
	static const int LIMITA_DIMENSIUNE_ADRESA = 5; //static const int poate fi initializat in clasa
	static const float LIMITA_GREUTATE_PACHETE_MICI;

	void set_adresa(string adresa) {
		if (adresa.size() < LIMITA_DIMENSIUNE_ADRESA) { throw exception("Adresa gresita!"); }
		delete[] this->adresaLivrare;
		this->adresaLivrare = Util::copiereVector(adresa.c_str()); // conversie string -> char*
	}

	string get_adresa() {
		//nu mai copiem cu Util fiindca deja returnam copie prin string()
		return string(this->adresaLivrare);
	}

	void set_greutate(float valoare) {
		if (valoare < 0) { throw exception("Valoare negativa!"); }
		this->greutate = valoare;
	}
	
	float get_greutate() {
		return this->greutate;
	}

	void este_fragil() {
		this->fragil = true;
	}

	void nu_este_fragil() {
		this->fragil = false;
	}

	bool get_fragil() {
		return this->fragil;
	}

	void set_stare(Stare stare) {
		if (stare == Stare::DEPOZIT) {
			this->PACHETE_IN_DEPOZIT += 1;
		}

		if (this->stare == Stare::DEPOZIT) {
			this->PACHETE_IN_DEPOZIT -= 1;
		}

		this->stare = stare;
	}

	Stare get_stare() {
		return this->stare;
	}

	static int get_nrPacheteDepozit() {
		return Pachet::PACHETE_IN_DEPOZIT;
	}

	Pachet(const char* adresa, float greutate, bool fragil):
		id(++Pachet::GENERATOR_ID), fragil(fragil) //fac asta unde nu am validare in setter => this->fragil = fragil
	{
		this->set_greutate(greutate);
		this->set_adresa(adresa);
	}

	//constructor default
	Pachet():id(++Pachet::GENERATOR_ID) {}

	int get_id() {
		return this->get_id();
	}

	~Pachet() {
		delete[] this->adresaLivrare;
		if (this->stare == Stare::DEPOZIT) {
			Pachet::PACHETE_IN_DEPOZIT -= 1;
		}
	}

	//copy constructor
	Pachet(Pachet& p):id(p.id), fragil(p.fragil) {
		this->set_adresa(p.get_adresa());
		this->set_greutate(p.get_greutate());
		this->set_stare(p.get_stare());
	}
};

const float Pachet::LIMITA_GREUTATE_PACHETE_MICI = 10.0; //static const float este initializat doar in afara clasei
int Pachet::PACHETE_IN_DEPOZIT = 0;
int Pachet::GENERATOR_ID = 0;

int main() {
	Pachet pachet;
	pachet.set_adresa("Starea Dorobanti 15");
	pachet.este_fragil();
	pachet.set_stare(Stare::RIDICAT);

	cout << "Adresa de livrare este: " << pachet.get_adresa() << endl;
	cout << "Pachete in depozit: " << pachet.get_nrPacheteDepozit() << endl;

	pachet.set_stare(Stare::DEPOZIT);
	cout << "Pachete in depozit: " << pachet.get_nrPacheteDepozit() << endl;

	return 0;
}