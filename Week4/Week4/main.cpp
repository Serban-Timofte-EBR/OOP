#include <iostream>
#include <string>

using namespace std;

enum TipStudent {
	LICENTA = 10,
	MASTERAT,
	DOCTORAT
};

class Student {
private:
	string nume = "Anonim";
	char universitate[100] = "ASE";
	char* facultate = nullptr;
	int varsta = 0;
	char gen = 'N';
	int* note = nullptr;
	int nrNote = 0;;
	bool hasScholarship = false;
	TipStudent tip = TipStudent::LICENTA; //am stringuri si vreau sa le validez ca int => enum

//Interfata Publica a clasei = colectia de metode publice: 
public:
	//citire
	string getNume() {
		return this->nume;
	}

	int getVarsta() {
		return this->varsta;
	}

	char* getUniversitate() {
		//1: return this->universitate; Nu returneaza doar referinta !! Nu returna pointer
		
		// 2: Nu returnam adrese de variabile locale ( sunt pe stiva functiei )
		// char copie[100];
		//strcpy_s(copie, 100, this->universitate);
		//return copie;

		char* copie = new char[strlen(this->universitate) + 1];
		strcpy_s(copie, strlen(this->universitate) + 1, this->universitate);
		return copie;
	}

	char* getFacultate() {
		//validam cand initializam nullptr
		if (this->facultate == nullptr) { return nullptr; }

		char* copie = new char[strlen(this->facultate) + 1];
		strcpy_s(copie, strlen(this->facultate) + 1, this->facultate);
		return copie;
	}

	int* getNote() {
		if (this->note == nullptr) { return nullptr; }

		int* copie = new int[nrNote];
		for (int i = 0; i < this->nrNote; i++) {
			copie[i] = this->note[i];
		}
	}

	//scriere

};

int main() {
	
	//Incapsulare -> in momentul in care definesti o clasa si o instantiezi intr-un obiect = cadoul este impachetat si pus pe masa
	Student student; //creez un obiect -> se instantiaza

	cout<<"Nume: " << student.getNume() << endl;
	cout<<"Varsta: " << student.getVarsta() << endl;
	cout << "Univesitate: " << student.getUniversitate() << endl;

	char* univ = student.getUniversitate();
	strcpy_s(univ, 100, "MK"); //transferam toti studentii la MK
	cout << "Univesitate: " << student.getUniversitate() << endl;


	return 0;
}