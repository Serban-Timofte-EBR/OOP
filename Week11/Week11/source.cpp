#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Adresa {
	string strada;
	int nr;
	string oras;
private:
	Adresa() {}
public:
	Adresa(string stada, int numar, string oras) 
		: strada(strada), nr(numar), oras(oras) {}

	friend ostream& operator<<(ostream& out, Adresa& adresa);
};

ostream& operator<<(ostream& out, Adresa& adresa) {
	out << endl << "Adresa: " << adresa.strada << " NR: " << adresa.nr << " Oras: " << adresa.oras;
	return out;
}

class Colet {
	Adresa adresa;		//One Package has an Adress - relationship 1:1
	string destinatar;
	float greutate = 0.0;
public:
	//Not optim
	//For testing commented: Colet() : adresa("", 0, "") {}
	Colet(string strada, int numar, string oras, string destinatar)
		: adresa(strada, numar, oras), destinatar(destinatar) {}

	//Optim OOP - call copy constructor
	Colet(string destinatar, Adresa adresa) 
		: adresa(adresa), destinatar(destinatar) {}

	friend ostream& operator<<(ostream& out, Colet& adresa);
};

ostream& operator<<(ostream& out, Colet& colet) {
	out << endl << "Destinatar: " << colet.destinatar << " ";
	out << colet.adresa;
	out << endl << "Greutate: " << colet.greutate;
	return out;
}

class Curier {
	string nume;
	//Unusable without default contructor
	//Colet colete[50];	//has a relationship - 1:M
	//Problem when you want to create an add_package function: Colet* colete = nullptr;
	Colet** colete = nullptr;
	int nrColete;

public:
	Curier() {}

	void adauga_colet(Colet colet) {
		//Cate obiecte se creeaza pe linie? 0 - Vector de pointeri
		Colet** coleteTemp = new Colet*[this->nrColete + 1];
		for (int i = 0; i < this->nrColete; i++) {
			coleteTemp[i] = this->colete[i];
		}
		//Less control for adress -> not good practice
		//coleteTemp[this->nrColete] = &colet;
		coleteTemp[this->nrColete] = new Colet(colet);
		
		delete[] this->colete;
		this->nrColete += 1;
		this->colete = coleteTemp;
	}

	~Curier() {
		for (int i = 0; i < this->nrColete; i++) {
			delete this->colete[i];
		}

		delete[] this->colete;
	}

	void generare_Raport(ofstream& fisier) {
		fisier << endl << "Lista livrari curier " << this->nume;
		for (int i = 0; i < this->nrColete; i++) {
			fisier << *this->colete[i];
		}
	}
};

int main() {
	Curier fan1;
	//De cate ori se apeleaza contrutorul din:
	//Curier:	1
	//Colet:	50 - se construiesc 50 de colete
	//Adresa:	50 - o adresa pentru fiecare colet

	Adresa adresaCSIE("Calea Dorobanti", 15, "Bucuresti");
	
	Colet colet1("Gigel", adresaCSIE);
	Colet colet2("Ana", adresaCSIE);

	fan1.adauga_colet(colet1);
	fan1.adauga_colet(colet2);

	ofstream raport("Raport Curier.txt", ios::ate);
	if (!raport.is_open()) {
		cout << endl << "********** Nu s-a deschis fisierul **********";
	}

	else {
		fan1.generare_Raport(raport);
		raport.close();
	}

	return 0;
}