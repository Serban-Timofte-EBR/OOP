#include <iostream>
#include <string>
using namespace std;

class Produs {
	string denumire = "";
	float pret = 0.0;
	int vanzariLunare[12];
	int lunaCurenta = 0;	// de la 0 la 11 (0 - Ianurie; 11 - Decembrie)

public:
	Produs(string nume, float pret):denumire(nume), pret(pret) {
		for (int i = 0; i < 12; i++) {
			this->vanzariLunare[i] = 0;
		}
	}

	//pot face si return type void si return;
	Produs& operator=(const Produs& p) { //& are rolul de a evita copy constructor
		//verifici si protejezi in caz de laptop = laptop
		if (this == &p) {
			return *this;
		}

		this->denumire = p.denumire;
		this->pret = p.pret;
		for (int i = 0; i < 12; i++) {
			this->vanzariLunare[i] = p.vanzariLunare[i];
		}
		this->lunaCurenta = p.lunaCurenta;

		return *this;
	}

	//Cum implementez un operator?
		// Prin metoda globala sau membra?
		// Cum ii deosebesc? ( ce signatura au? )
		//Ce trebuie sa faca operatorul?

	string get_denumire() {
		return this->denumire;
	}

	friend void operator<<(ostream& consola, Produs& p);

	//primesc ca functie membra clasa deja un this ca prim parametru
	//NU modificam parametrii
	Produs operator+(int valoare) {
		Produs rezultat = *this;
		rezultat.pret += valoare;
		return rezultat;
	}
};

//Orice operator nu are ca prin paramentru Produs, se implemeteaza prin functie globala
void operator<<(ostream& consola, Produs& p) {
	consola << "Denumire Produs: " << p.get_denumire() << endl;
	consola << "Pret Produs: " << p.pret << endl;
	consola << "Vanzaari luanre: " << endl;

	for (int i = 0; i < 12; i++) {
		consola << " " << p.vanzariLunare[i];
	}

	consola << endl << "Luna curenta: " << p.lunaCurenta << endl;
}

Produs operator+(int valoare, Produs& p) {
	return p + valoare;
}

int main() {
	Produs laptop("Laptop", 2500);
	Produs altProdus ("", 2500);
	Produs temp("", 2500);

	altProdus = laptop;
	temp = altProdus = laptop;

	//operator pentru lucru cu stream-urile standar de input/output => cout << laptop; cin >> laptop;
	cout << laptop;
	//cin >> laptop;

	////operator matematici 
	////binari 
	laptop = laptop + 20; //creste pretul cu 20
	laptop = 30 + laptop; //creste pretul cu 30
	//altProdus = laptop + temp;
	////la fel -, /, *
	cout << laptop;

	//laptop += 35; //modificam vanzarile pentru luna curenta
	////la fel pentru -=, /= si *=

	////unari 
	//temp = laptop++; //trecem la luna urmatoare - postincrementare
	//temp = ++laptop; //trecem la luna urmatoare - preincrementare
	////la fel -- cu cele doua forme

	////operatori logici
	//if (laptop == temp) {
	//	cout << "Cele doua produse sunt identice!" << endl;
	//}

	//if (laptop > 500) {
	//	cout << "Este un produs scump!" << endl;
	//}

	//if (laptop >= temp) {
	//	cout << "Are pretul mai mare sau egal!" << endl;
	//}
	////la fel !=, <, =<

	//if (!laptop) {
	//	cout << "Produsul nu s-a vandut" << endl;
	//}

	////operatul de cast
	//int totalVanzari = laptop;

	////operatorul de indexare
	//int vanzariFebruarie = laptop[1];
	//laptop[0] = 123; //modific vanzarile din ianuarie cu valoare 123

	////operatorul functie
	//float medieVanzariLunare = laptop(1,5) //media vanzarilor din perioada februarie - iunie

	return 0;
}