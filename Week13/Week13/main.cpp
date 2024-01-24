#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Examen:
	//Relatie dintre clase, inheritance sau compunere
	//Fisiere ( binare si text, citire, scriere )
	//has a ( 1-1, 1-M ), is a - relatii

//Colectii:
	//Vector
	//Set ( lista cu valori unice )
	//Map ( dictionar, caut valaore dupa cheie )

//Template example
//int suma(int a, int b) { //dar vreau si pentru float si pentru double, etc
//	return a + b;
//}

template<typename T> T suma(T a, T b) { // sau suma(T a, int b) sau template<typename T, typename Z> T suma(T a, Z b)
	return a + b;
}

//specializare template pentru a nu aduna adresele a doi vectori dinamici
template<> char* suma(char* a, char* b) {
	cout << "Apel versiune specializata" << endl;
	return nullptr;
}

class Adresa {
	string strada;
	int nr;
	string oras;
};

template<typename T> class Student {
	string nume;
	//colectie de note
	vector<int> note;
	T adresa;

public:
	Student(string nume, T adresa) {
		this->nume = nume;
		this->adresa = adresa;
	}
};

int main() {
	//implementare in main
	int rezultat = suma<int>(2, 3);
	float rezultatFloat = suma<float>(2.5, 1.6);
	char* msg1 = new char[5] {"test"};
	char* msg2 = new char[6] {"test1"};

	char* mesaj = suma<char*>(msg1, msg2);
	return 0;
}