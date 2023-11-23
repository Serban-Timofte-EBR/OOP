#include <iostream>
#include <string>
using namespace std;

class Smarphone {
	//telefonul ocupa x nr. Biti: 8B contacte + 4B nrContacte + 1 Niv. Baterie + Const String IMEI = 13B default + cati B are IMEI ( depinde de compilator )
private:
	string* contacte = nullptr;
	int nrContacte = 0;

	const string IMEI;
	char nivelBaterie = 0; //de la 0 la 100

public:
	string* get_contacte() {
		if (this->contacte == nullptr) { return nullptr; }
		string* lista = new string[this->nrContacte];
		for (int i = 0; i < this->nrContacte; i++) {
			lista[i] = this->contacte[i];
		}
		return lista;
	}

	int get_nrContancte() { return this->nrContacte; }

	void set_contacte(string* lista, int nrContacte) {
		if (lista == nullptr) { throw exception("Lista is empty!"); }
		delete[] this->contacte;
		this->nrContacte = nrContacte;
		this->contacte = new string[nrContacte];
		for (int i = 0; i < nrContacte; i++) {
			this->contacte[i] = lista[i];
		}
	}

	void printConsola() {
		cout << "IMEI: " << this->IMEI << endl;
		cout << "Nivel Baterie: " << (int)this->nivelBaterie << "%" << endl;
		if (this->nrContacte == 0) {
			cout << "Agenda nu detine contacte!" << endl;
		}
		else {
			cout << "Agenda: ";
			for (int i = 0; i < this->nrContacte; i++) {
				cout << " " << this->contacte[i];
			}
			cout << endl;
		}
	}

	Smarphone(string IMEI, string* contacte, int nrContacte) : IMEI(IMEI), nivelBaterie(100) {
		this->set_contacte(contacte, nrContacte);
	}

	Smarphone(const Smarphone& tel):IMEI(tel.IMEI) { //pun const pentru control si a nu gresi alocarea
		this->nivelBaterie = tel.nivelBaterie;
		this->set_contacte(tel.contacte, tel.nrContacte);
	}

	~Smarphone() {
		delete[] this->contacte;
	}

	//cand am camp dinamic, trebuie sa implementez operatorul egal
	void operator=(const Smarphone& tel) {
		if (this == &tel) { return; }
		//dezalocare in setter
		this->set_contacte(tel.contacte, tel.nrContacte);
		this->nivelBaterie = tel.nivelBaterie;
	}
};


int main() {
	string agenda[] = { "Gigel", "Ana", "Ionel" };
	int nrContacte = 3;

	Smarphone telefon("1234", agenda, nrContacte);
	telefon.printConsola();

	Smarphone telefon2("2222", agenda, nrContacte);
	telefon2.printConsola();

	//apel constructor de copiere explicit
	Smarphone clonaTelefon = telefon2; // => (daca nu am copy pointer ) dangling pointer ( dezaloc de 2 ori pointerul contacte prin destructor)

	//int* pointer = new int[10];
	//delete[] pointer;
	//de aici inainte avem dangling pointer
	//pointer = nullptr;
	//aici nu mai este dangling pointer

	clonaTelefon = telefon; //clonaTelefon.operator=(telefon)

	return 0;
}